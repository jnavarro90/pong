/**
 * @file
 * @brief Definición de CInstance_MJ_Online_Client
 *
 */

#include "instancia.h"

#include "../../temporizador.h"
#include "../../frame.h"

#include "../../opciones/tablero.h"

using namespace std;

const int FRAMES_PER_SECOND = 70;

CInstance_MJ_Online_Client::CInstance_MJ_Online_Client()
{
  i_running = false;
  conectado = false;

  fondo_menu = NULL;

  tcpclient = NULL;
  remoteip = NULL;

  datos_server = NULL;
  datos_cliente = NULL;

  msgC = NULL;
  msgS = NULL;

  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;
}

CInstance_MJ_Online_Client::~CInstance_MJ_Online_Client()
{
  i_running = false;
  conectado = false;

  fondo_menu = NULL;

  tcpclient = NULL;
  remoteip = NULL;

  datos_server = NULL;
  datos_cliente = NULL;

  msgC = NULL;
  msgS = NULL;

  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;
}

bool CInstance_MJ_Online_Client::Init()
{
  if(!LoadFiles())
    return false;

  if(!network.Init())
  {
    cerr << ERROR_STR_NET << " MJ_ONLINE_CLIENT" << endl;
    return I_SALIDA;
  }

  i_running = true;
  conectado = false;

  color_negro.r = color_negro.g = color_negro.b = 0x00;
  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;
  color_rojo.r = 0xFF;
  color_rojo.g = color_rojo.b = 0x00;

  bTeclado = true;

  /*PJ1 = new CPad_MJ_Online_Client(der, SDLK_w, SDLK_s);
  PJ2 = new CPad_MJ_Online_Client_Zombi(izq);
  pelota = new CPelota_MJ_Online_Client;
  marcador = new CMarcador_Online(ttf_bitM, &color_blanco);*/

  tcpclient = new CClientSocket();

  datos_server = new CNetwork_Data_Server;
  datos_cliente = new CNetwork_Data_Client;

  msgC = new CNetMessageN(NET_MJ_CLIENTDATA_SIZE);
  msgS = new CNetMessageN(NET_MJ_SERVERDATA_SIZE);

  SDL_Rect cajas = {100, 200, 180, 25};

  botones = NULL;
  CBoton* botones = new CBoton[4];
  botones[0] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Conectar"); cajas.y += 30;
  botones[1] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Atras");
  menu = new CMenu(botones, 2);

  entradaTeclado = new CTecladoIP("media/ttf/consolab.ttf", 30, &color_blanco, 95, 135);

  // Warnings
  wrConectando = new CWarning(ttf_consolas, "Conectando...", &color_blanco);
  wrConectado = new CWarning(ttf_consolas, "Conectando!", &color_blanco);
  wrDesconectado = new CWarning(ttf_consolas, "Desconectado", &color_rojo);

  // Temporizador
  timeOut = new CTemporizador;
  timeFrameSkip = new CTemporizador;
  frameSkip = false;

  return true;
}

bool CInstance_MJ_Online_Client::LoadFiles()
{
  fondo_menu = SDL_CreateRGBSurface(SDL_SWSURFACE, opciones->PANTALLA_ANCHO, opciones->PANTALLA_ALTO, opciones->PANTALLA_BPP, 0x00, 0x00, 0x00, 0x00);
  if(fondo_menu == NULL)
  {
    cout << ERROR_STR_SURFACE << "MENU_MJ_ONLINE_CLIENT -> fondo" << endl;
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

  SDL_Rect caja = {80, 200, 8, 115};
  SDL_FillRect(fondo_menu, &caja, SDL_MapRGB(pantalla->format, 0xFF, 0xFF, 0xFF) );
  CFrame caja_IP(320, 60, 8, SDL_MapRGB(pantalla->format, 0xFF, 0xFF, 0xFF), SDL_MapRGB(pantalla->format, 0x00, 0x00, 0x00));
  caja_IP.combinar(80, 120, fondo_menu);

  SDL_Color texto_color = {255, 255, 255, 0};
  SDL_Surface* texto_connect = TTF_RenderText_Blended(ttf_consolas, "Dirección IP", texto_color);
  aplicar_superficie(80, 100, texto_connect, fondo_menu);
  SDL_FreeSurface(texto_connect);

  return true;
}


bool CInstance_MJ_Online_Client::LoadMenu()
{
  return true;
}

void CInstance_MJ_Online_Client::LoadObjects()
{
  PJ1 = new CPad_MJ_Online_Client(der, SDLK_w, SDLK_s);
  PJ2 = new CPad_MJ_Online_Client_Zombi(izq);
  pelota = new CPelota_MJ_Online_Client;
  marcador = new CMarcador_Online(ttf_bitM, &color_blanco);
}

void CInstance_MJ_Online_Client::Close()
{
  UnLoadFiles();

  i_running = false;
  fondo = fondo_menu = NULL;

  /*delete PJ1;
  delete PJ2;
  delete pelota;
  delete marcador;*/

  delete tcpclient;
  if(remoteip != NULL)
  {
    delete remoteip;
    remoteip = NULL;
  }

  delete msgC;
  delete msgS;

  delete datos_server;
  delete datos_cliente;

  // Menu
  delete []botones;
  delete menu;

  delete entradaTeclado;

  // Warnings
  delete wrConectando;
  delete wrConectado;
  delete wrDesconectado;

  // Temp
  delete timeOut;
  delete timeFrameSkip;
}


void CInstance_MJ_Online_Client::UnLoadFiles()
{
  //SDL_FreeSurface(fondo);
  SDL_FreeSurface(fondo_menu);

  TTF_CloseFont(ttf_consolas);
  TTF_CloseFont(ttf_bitM);
}

void CInstance_MJ_Online_Client::UnLoadObjects()
{
  delete PJ1;
  delete PJ2;
  delete pelota;
  delete marcador;
}

void CInstance_MJ_Online_Client::OnEventMenu(int& s)
{
  if(bTeclado)
  {
    entradaTeclado->eventuar();
  }
  int caso = menu->eventuar();

  if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) || caso == 1)
  {
    bTeclado = false;
  }
  else if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || caso == 2)
  {
    i_running = false;
    //caso = I_MJ_ONLINE;
  }
  else if(event.type == SDL_QUIT)
  {
    i_running = false;
    bTeclado = false;
    s = I_SALIDA;
  }
}

void CInstance_MJ_Online_Client::OnLoopMenu(flags& F)
{
  // Intento de conexión
  if(!bTeclado && i_running)
  {
    remoteip = new CIpAddress(entradaTeclado->getStr().c_str(), NET_MJ_PORT);
    F = 0x00;
    F = F | eConectando;

    if(timeOut->getTicks()/1000.f < iTimeOut && !conectado)
    {

    #ifdef DEBUG
      cout << "Intentando conectar..." << endl;
    #endif
      if(tcpclient->Connect(*remoteip) && remoteip->GetHost() > 0)
      {
        if(tcpclient->Ok())
        {
          CNetMessageN msg_settings(NET_MJ_SETTINGS_SIZE);
          if(tcpclient->Receive(msg_settings) )
          {
          #ifdef DEBUG
            cout << "Conectado" << endl;
          #endif
            CNetwork_Data_Settings network_data_settings;
            char buffer_settings[NET_MJ_SETTINGS_SIZE];

            msg_settings.UnLoadNBytes(buffer_settings);
            network_data_settings.readBuffer((uchar*)buffer_settings);

            opciones->PANTALLA_ALTO = network_data_settings.PANTALLA_ALTO;
            opciones->PANTALLA_ANCHO = network_data_settings.PANTALLA_ANCHO;
            opciones->PAD_ALTO = network_data_settings.PAD_ALTO;
            opciones->PAD_ANCHO = network_data_settings.PAD_ANCHO;
            opciones->PELOTA_ALTO = network_data_settings.PELOTA_ALTO;

            initPantalla(); // ignorar salida??
            tablero_mp->construir(opciones->PANTALLA_ANCHO, opciones->PANTALLA_ALTO, opciones->PANTALLA_BPP);

            conectado = true;
            F = 0x00;
            F |= eConectado;
            SDL_Delay(2000);
          }
        }
      }
    }
    else if(timeOut->getTicks()/1000.f >= iTimeOut  && !conectado)
    {
      F = 0x00;
      F |= eDesconectado;
      bTeclado = true;
      delete remoteip;
    }
  }
  else if(bTeclado && i_running)
  {
    timeOut->empezar();
  }
}

//enum wr_t { eConectado = 0, eConectando = 1, eDesconectado };

void CInstance_MJ_Online_Client::OnRenderMenu(flags& F)
{
  aplicar_superficie(0, 0, fondo_menu, pantalla);
  entradaTeclado->mostrar();
  menu->mostrar();

#define OFFSET 300

  if(F & eConectado)
    wrConectado->mostrar_ch(OFFSET);
  else if(F & eConectando)
    wrConectando->mostrar_ch(OFFSET);
  else if(F & eDesconectado)
    wrDesconectado->mostrar_ch(OFFSET);

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}

int CInstance_MJ_Online_Client::OnExecute()
{
  if(!Init())
  {
    cerr << ERROR_STR_INIT << endl;
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
  timeFrameSkip->empezar();

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent(salida);
      if(event.type == SDL_QUIT)
      {
        i_running = false;
        salida = I_SALIDA;
      }
    }
    OnLoop(salida);
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)) && !frameSkip)
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
    if(frameSkip)
    {
      cout << "Frame saltado en " << frame << endl;
    }
  }
  UnLoadObjects();
  Close();

  return salida;
}

void CInstance_MJ_Online_Client::OnEvent(int& salida)
{
  if(frameSkip)
    return;

  PJ1->eventuar(datos_cliente->evento);

  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == SDLK_ESCAPE)
    {
      i_running = false;
    }
  }
  else if(event.type == SDL_QUIT)
  {
    i_running = false;
    conectado = false;
    salida = I_SALIDA;
  }
}

void CInstance_MJ_Online_Client::OnLoop(int& salida)
{
  if (!conectado) // Establecer conexión
  {
    if (tcpclient->Connect(*remoteip))
    {
      if (tcpclient->Ok())
      {
        conectado = true;
      }
    }
  }
  //else if(conectado)
  if(conectado)
  {
    timeOut->empezar();
    // Enviar datos si el usuario ha realizado un movimiento y si no hay frameSkip

    if(datos_cliente->evento && !frameSkip)
    {
      datos_cliente->ticks = timeFrameSkip->getTicks();

      datos_cliente->makeBuffer();
      msgC->LoadNBytes(datos_cliente->getBuffer());

      if(!tcpclient->Send(*msgC))
      {
        #ifdef DEBUG
        cout << "Error enviando mensaje." << endl;
        #endif
      }
    }
    if (tcpclient->Ready())
    {
      if(tcpclient->Receive(*msgS))
      {
        char buffer[NET_MJ_SERVERDATA_SIZE];
        //msgS->UnLoad12Bytes(buffer);
        msgS->UnLoadNBytes(buffer);

        datos_server->readBuffer((uchar*)buffer);

        // Gestionar datos
        PJ1->setY(datos_server->pad2_y);
        PJ2->setY(datos_server->pad1_y);
        pelota->setXY(datos_server->pelota_x, datos_server->pelota_y);

        marcador->setM1(datos_server->marcador1);
        marcador->setM2(datos_server->marcador2);

        if(datos_server->ticks >= (Uint32)timeFrameSkip->getTicks())
          frameSkip = true;
        else
          frameSkip = false;

        if(datos_server->fs & fsnd_pong)
        {
          Mix_PlayChannel( -1, snd_pong, 0 );
        }
        if(datos_server->fs & fsnd_pung)
        {
          Mix_PlayChannel( -1, snd_pung, 0 );
        }
      }
      else
      {
        conectado = false;
      }
    }
  }
  if(timeOut->getTicks()/1000.f > iTimeOut)
  {
    i_running = false;
    salida = I_MJ_ONLINE;
  }
}

void CInstance_MJ_Online_Client::OnRender()
{
  tablero_mp->mostrar();

  marcador->mostrar();
  PJ1->mostrar();
  PJ2->mostrar();
  pelota->mostrar();

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
