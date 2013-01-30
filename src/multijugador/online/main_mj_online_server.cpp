#include "vars.h"
#include "network_struct.h"
#include "pad_mj_online.h"
#include "pelota_mj_online.h"
#include "main_mj_online.h"
#include "../marcador.h"
#include "../../temporizador.h"
#include "../../warning.h"
#include "../../network/CNet.h"
#include "../../menu/menu.h"

#include <iostream>
#include <string.h>

using namespace std;

const int FRAMES_PER_SECOND = 100;

bool cargar_mj_online_server()
{
  img_fondo_mj_online = cargar_img("media/img/fondo_mj.png");
  img_fondo_mj_online_menu_server = cargar_img("media/img/fondo_menu_server.png");

  if(img_fondo_mj_online == NULL || img_fondo_mj_online_menu_server == NULL)
    return false;

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);
  ttf_bitM = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);

  if(ttf_consolas == NULL || ttf_bitM == NULL)
    return false;

  return true;
}

void limpiar_mj_online_server()
{
  SDL_FreeSurface(img_fondo_mj_online);
  SDL_FreeSurface(img_fondo_mj_online_menu_server);

  TTF_CloseFont(ttf_consolas);
  TTF_CloseFont(ttf_bitM);
}

int main_mj_online_server()
{
  if(!cargar_mj_online_server())
  {
	   return -1;
  }

  CNet network;
  if(!network.Init())
  {
	   cerr << "Error iniciando red" << endl;
	   return -1;
  }

  CTemporizador fps;
  int frame = 0;

  CTemporizador timeOut;
  const int iTimeOut = 5;

  SDL_Color color_rojo = {255, 0, 0};
  SDL_Color color_blanco = {255, 255, 255};
  SDL_Color color_negro = {0, 0, 0};

  CWarning wrDesconectado(ttf_consolas, "Desconectado", &color_rojo);
  CWarning wrConectado(ttf_consolas, "Conectado!", &color_rojo);
  CWarning wrEspera(ttf_consolas, "Esperando cliente", &color_blanco);

  SDL_Rect caja = {PANTALLA_ANCHO/2 - 150/2, 300, 150, 25};

  CBoton botonAtras(ttf_consolas, &color_negro, &color_blanco, &caja, "Volver");
  CMenu menu(&botonAtras, 1);

  CNetMessage1 msgC;
  CNetMessage_NET_BYTES_ msgS;
  CClientSocket* tcpclient = new CClientSocket;
  CHostSocket* tcplistener = new CHostSocket(PORT_MJ);

  if(!tcplistener->Ok())
  {
	    return -1;
  }

  bool salir = false;
  bool conectado = false;

  int salida = 0;
  int caso = 0;

  // Hay una fuga de memoria en este bucle... ¡Arreglado! el fallo estaba en la clase CWarning
  while(!conectado && !salir)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      caso = menu.eventuar();
      if(event.type == SDL_QUIT)
      {
        salir = true;
        salida = -1;
      }
      if(caso == 1)
      {
        salir = true;
        salida = 0;
      }
    }

    if(!salir && !conectado)
    {
      // Conectando con cliente...
      if(tcplistener->Accept(*tcpclient))
      {
        conectado = true;
        // esperar recibir mensaje de cliente

      }
      aplicar_superficie(0, 0, img_fondo_mj_online_menu_server, pantalla);
      menu.mostrar();

      if(!conectado)
      {
        wrEspera.mostrar();
      }
      else
      {
        wrConectado.mostrar();
      }

      if(SDL_Flip(pantalla) == -1)
        return -1;

      if(conectado)
        SDL_Delay(1000);

      frame++;
      if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
        SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
    }
  }

  CPad_MJ_Online PJ1(izq, SDLK_w, SDLK_s);
  CPad_MJ_Online_Zombi PJ2(der);
  CPelota_MJ_Online pelota;
  CMarcador marcador(ttf_bitM, &color_blanco);
  // Para el cliente, CPelota_MJ_Online_Zombi

  //network_data_client_t datos_cliente = {0};
  //network_data_server_t datos_server = {0, 0, 0, 0, 0, 0, 0, 0};

  CNetwork_Data_Server datos_server;
  CNetwork_Data_Client datos_cliente;

  //char buffer[12] = {0, 0, 0, 0, 0, 0, 0, 0};

  frame = 0;
  pelota.empezar();

  while(!salir)
  {
	   fps.empezar();

	    // Eventos

	   while(SDL_PollEvent(&event))
	   {
	     PJ1.eventuar();
	     if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	     {
	      	pelota.empezar();
	     }
	     if(event.type == SDL_QUIT)
	     {
	      	salida = -1;
	       salir = true;
	     }
	   }

    if(conectado)
    {
      timeOut.empezar();
    }
    if(timeOut.getTicks()/1000.f > iTimeOut)
    {
      salir = true;
      salida = 0;
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
    	   if(tcpclient->Receive(msgC))
    	   {
    	  // Recibir datos del client (estructura network_struct_client_t)
          #ifdef DEBUG
    	     cout << "Mensaje recibido" << endl;
          #endif
    	     //datos_cliente.evento = msgC.UnLoadByte();
    	     datos_cliente.readBuffer(msgC.UnLoadByte());
    	   }
    	   else
    	   {
    	     conectado = false;
    	   }
      }
    }

    	// Gestionar datos (servidor y cliente)(setpost, etc...)

    PJ1.mover();
    PJ2.mover(datos_cliente.evento);
    int partido = pelota.mover(PJ1, PJ2, datos_server.fs);

    if(partido == 1)
    {
      marcador.incM1();
    }
    else if(partido == 2)
    {
      marcador.incM2();
    }

    	// Mandar datos (servidor -> cliente)

    datos_server.pelota_x = pelota.getCaja().x;
    datos_server.pelota_y = pelota.getCaja().y;

    datos_server.pad1_y = PJ1.getCaja().y;
    datos_server.pad2_y = PJ2.getCaja().y;

    datos_server.marcador1 = marcador.getM1();
    datos_server.marcador2 = marcador.getM2();

    //SdataToChar(&datos_server, (unsigned char*)buffer);
    datos_server.makeBuffer();

#ifdef DEBUG
    cout << "Buffer_int: ";
    for(int i = 0; i < 4; i++)
      cout << buffer_int[i] << " ";
    cout << endl;

    cout << "Buffer: ";
    for(int i = 0; i < 8; i++)
      cout << buffer[i] << " ";
    cout << endl;
#endif

    // Para evitar colapsos, mando los datos cada 2 frames
    if(conectado && frame % 2 == 0)
    {
      //msgS.Load_NET_BYTES_Bytes(buffer);
      msgS.Load_NET_BYTES_Bytes(datos_server.getBuffer());
      cerr << "buffer_server: " << datos_server.getBuffer() << endl;
      if(!tcpclient->Send(msgS))
      {
        #ifdef DEBUG
    	   cout << "Error enviando datos." << endl;
        #endif
      }
      datos_server.fs = 0x0;
    }
    datos_cliente.evento = 0;

    	// Mostrar por pantalla

    aplicar_superficie(0, 0, img_fondo_mj_online, pantalla);

    PJ1.mostrar();
    PJ2.mostrar();
    pelota.mostrar();
    marcador.mostrar();

    if(!conectado)
    {
      wrDesconectado.mostrar();
    }

    if(SDL_Flip(pantalla) == -1)
        return -1;

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  delete tcpclient;
  delete tcplistener;

  network.Quit();

  limpiar_mj_online_server();

  return salida;
}
