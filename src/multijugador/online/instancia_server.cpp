#include "instancia.h"

#include "../../temporizador.h"
#include "../../opciones/tablero.h"

using namespace std;

const int FRAMES_PER_SECOND = 60;

CInstance_MJ_Online_Server::CInstance_MJ_Online_Server()
{
  i_running = false;
  conectado = false;

  fondo_menu = NULL;

  tcpclient = NULL;
  tcplistener = NULL;

  datos_server = NULL;
  datos_cliente = NULL;

  msgC = NULL;
  msgS = NULL;

  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;
}

CInstance_MJ_Online_Server::~CInstance_MJ_Online_Server()
{
  i_running = false;
  conectado = false;

  fondo_menu = NULL;

  tcpclient = NULL;
  tcplistener = NULL;

  datos_server = NULL;
  datos_cliente = NULL;

  msgC = NULL;
  msgS = NULL;

  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;
}

bool CInstance_MJ_Online_Server::Init()
{
  if(!LoadFiles())
    return false;

  if(!network.Init())
  {
    cerr << ERROR_STR_NET << endl;
    return I_SALIDA;
  }

  i_running = true;
  conectado = false;

  color_negro.r = color_negro.g = color_negro.b = 0x00;
  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;
  color_rojo.r = 0xFF;
  color_rojo.g = color_rojo.b = 0x00;

  /*PJ1 = new CPad_MJ_Online (izq, SDLK_w, SDLK_s);
  PJ2 = new CPad_MJ_Online_Zombi(der);
  pelota = new CPelota_MJ_Online;
  marcador = new CMarcador(ttf_bitM, &color_blanco);*/

  tcpclient = new CClientSocket;
  tcplistener = new CHostSocket(NET_MJ_PORT);

  datos_server = new CNetwork_Data_Server;
  datos_cliente = new CNetwork_Data_Client;

  msgC = new CNetMessage1;
  msgS = new CNetMessage12;

  SDL_Rect caja = {opciones->PANTALLA_ANCHO/2 - 150/2, 300, 150, 25};

  botones = NULL;
  botones = new CBoton(ttf_consolas, &color_negro, &color_blanco, &caja, "Volver");
  menu = new CMenu(botones, 1);

  // Warnings
  wrConectado = new CWarning(ttf_consolas, "Conectando!", &color_blanco);
  wrDesconectado = new CWarning(ttf_consolas, "Desconectado", &color_rojo);

  // Temporizador
  timeOut = new CTemporizador;

  return true;
}

bool CInstance_MJ_Online_Server::LoadFiles()
{
  /*fondo = cargar_img("media/img/fondo_mj.png", false);
  if(fondo == NULL)
  {
    cerr << ERROR_STR_FILE << "media/img/fondo_mj_local.png" << endl;
    return false;
  }*/

  fondo_menu = cargar_img("media/img/fondo_menu_server.png");
  if(fondo_menu == NULL)
  {
    cerr << ERROR_STR_FILE << "media/img/fondo_menu_server.png" << endl;
    return false;
  }

  ttf_bitM = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);
  if(ttf_bitM == NULL)
  {
    cerr << ERROR_STR_FILE << "media/ttf/bit.ttf" << endl;
    return false;
  }

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);
  if(ttf_consolas == NULL)
  {
    cerr << ERROR_STR_FILE << "media/ttf/consolab.ttf" << endl;
    return false;
  }

  return true;
}

void CInstance_MJ_Online_Server::LoadObjects()
{
  PJ1 = new CPad_MJ_Online (izq, SDLK_w, SDLK_s);
  PJ2 = new CPad_MJ_Online_Zombi(der);
  pelota = new CPelota_MJ_Online;
  marcador = new CMarcador(ttf_bitM, &color_blanco);
}

void CInstance_MJ_Online_Server::Close()
{
  UnLoadFiles();

  i_running = false;
  fondo = fondo_menu = NULL;

  /*delete PJ1;
  delete PJ2;
  delete pelota;
  delete marcador;*/

  delete tcpclient;
  delete tcplistener;

  delete msgC;
  delete msgS;

  delete datos_server;
  delete datos_cliente;

  // Menu
  delete botones;
  delete menu;

  // Warnings
  delete wrConectado;
  delete wrDesconectado;

  // Temp
  delete timeOut;
}


void CInstance_MJ_Online_Server::UnLoadFiles()
{
  //SDL_FreeSurface(fondo);
  SDL_FreeSurface(fondo_menu);

  TTF_CloseFont(ttf_consolas);
  TTF_CloseFont(ttf_bitM);
}

void CInstance_MJ_Online_Server::UnLoadObjects()
{
  delete PJ1;
  delete PJ2;
  delete pelota;
  delete marcador;
}

void CInstance_MJ_Online_Server::OnEventMenu(int& s)
{
  int caso = menu->eventuar();

  if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || caso == 1)
  {
    i_running = false;
  }
  else if(event.type == SDL_QUIT)
  {
    i_running = false;
    s = I_SALIDA;
  }
}

void CInstance_MJ_Online_Server::OnLoopMenu(flags& F)
{
  // A la espera de una conexión entrante
  if(i_running && !conectado)
  {
    // Conectando con cliente...
    if(tcplistener->Accept(*tcpclient))
    {
      // Enviar la configuración al cliente
      CNetMessage12 msg_settings;
      CNetwork_Data_Settings network_data_settings;
      network_data_settings.makeBuffer();
      msg_settings.Load12Bytes(network_data_settings.getBuffer());

      if(tcpclient->Send(msg_settings))
      {
        conectado = true;
        F = 0x00;
        F |= eConectado;
      }
    }
  }
}

//enum wr_t { eConectado = 0, eConectando = 1, eDesconectado };

void CInstance_MJ_Online_Server::OnRenderMenu(flags& F)
{
  aplicar_superficie(0, 0, fondo_menu, pantalla);
  menu->mostrar();

#define OFFSET 300

  if(F & eConectado)
    wrConectado->mostrar_ch(OFFSET);

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}

int CInstance_MJ_Online_Server::OnExecute()
{
  if(!Init())
  {
    cerr << ERROR_STR_INIT << " MJ_ONLINR_SERVER" << endl;
    return I_SALIDA;
  }

  int frame = 0;
  CTemporizador fps;

  int salida = I_MJ_ONLINE;

  flags F = 0x00;

  while(!conectado && i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEventMenu(salida);
    }

    OnLoopMenu(F);
    OnRenderMenu(F);

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }
  LoadObjects();

  pelota->empezar();

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent(salida);
    }

    OnLoop(frame);
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  UnLoadObjects();
  Close();

  return salida;
}

void CInstance_MJ_Online_Server::OnEvent(int& salida)
{
  PJ1->eventuar();

  if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
  {
    pelota->empezar();
  }
  else if(event.type == SDL_QUIT)
  {
    salida = I_SALIDA;
    conectado = false;
    i_running = false;
  }
}

void CInstance_MJ_Online_Server::OnLoop(int& frame)
{
  if(conectado)
  {
    timeOut->empezar();
  }
  if(timeOut->getTicks()/1000.f >= iTimeOut)
  {
    i_running = false;
  }
  // Recibir datos del cliente remoto
  if(!conectado)
  {
    if(tcplistener->Accept(*tcpclient))
    {
      conectado = true;
    }
  }
  else
  {
    if(tcpclient->Ready())
    {
      if(tcpclient->Receive(*msgC))
      {
        // Recibir datos del client (estructura network_struct_client_t)
        #ifdef DEBUG
        cout << "Mensaje recibido" << endl;
        #endif
        datos_cliente->readBuffer(msgC->UnLoadByte());
      }
      else
      {
        conectado = false;
      }
    }
  }
    // Gestionar datos (servidor y cliente)(setpost, etc...)
  PJ1->mover();
  PJ2->mover(datos_cliente->evento);
  int partido = pelota->mover(*PJ1, *PJ2, datos_server->fs);

  if(partido == 1)
  {
    marcador->incM1();
  }
  else if(partido == 2)
  {
    marcador->incM2();
  }

   // Mandar datos (servidor -> cliente)
  datos_server->pelota_x = pelota->getCaja().x;
  datos_server->pelota_y = pelota->getCaja().y;

  datos_server->pad1_y = PJ1->getCaja().y;
  datos_server->pad2_y = PJ2->getCaja().y;

  datos_server->marcador1 = marcador->getM1();
  datos_server->marcador2 = marcador->getM2();

  //SdataToChar(&datos_server, (unsigned char*)buffer);
  datos_server->makeBuffer();

  // Para evitar colapsos, mando los datos cada 2 frames
  if(conectado && frame % 2 == 0)
  {
    msgS->Load12Bytes(datos_server->getBuffer());
    if(!tcpclient->Send(*msgS))
    {
      #ifdef DEBUG
      cout << "Error enviando datos." << endl;
      #endif
    }
    datos_server->fs = 0x0;
  }
  datos_cliente->evento = 0;
}

void CInstance_MJ_Online_Server::OnRender()
{
  //aplicar_superficie(0, 0, fondo, pantalla);
  tablero_mp->mostrar();

  PJ1->mostrar();
  PJ2->mostrar();
  pelota->mostrar();
  marcador->mostrar();

  if(!conectado)
  {
    wrDesconectado->mostrar();
  }

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}
