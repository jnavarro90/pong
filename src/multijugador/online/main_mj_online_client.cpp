#include "vars.h"
#include "network_struct.h"
#include "pad_mj_online.h"
#include "pelota_mj_online.h"
#include "main_mj_online.h"
#include "tecladoIP.h"
#include "marcador_online.h"

#include "../../temporizador.h"
#include "../../network/CNet.h"
#include "../../menu/menu.h"
#include "../../warning.h"
#include "../../teclado.h"

#include <iostream>
#include <string.h>

using namespace std;

const int FRAMES_PER_SECOND = 100;

bool cargar_mj_online_client()
{
  img_fondo_mj_online = cargar_img("media/img/fondo_mj.png");
  img_fondo_mj_online_menu_client = cargar_img("media/img/fondo_menu_client.png");

  if(img_fondo_mj_online == NULL || img_fondo_mj_online_menu_client == NULL)
    return false;

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);
  ttf_bitM = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);

  if(ttf_consolas == NULL || ttf_bitM == NULL)
    return false;

  return true;
}

void limpiar_mj_online_client()
{
  SDL_FreeSurface(img_fondo_mj_online);
  SDL_FreeSurface(img_fondo_mj_online_menu_client);

  TTF_CloseFont(ttf_consolas);
  TTF_CloseFont(ttf_bitM);
}

int main_mj_online_client()
{
  if(!cargar_mj_online_client())
  {
	   return -1;
  }

  CNet network;

  if(!network.Init())
  {
	   cerr << "Error iniciando red" << endl;
	   return -1;
  }

  bool salir = false;
  int salida = 0;

  CTemporizador fps;
  int frame;

  bool bTeclado = false;

  CNetMessage1 msgC;
  CNetMessage_NET_BYTES_ msgS;
  CClientSocket* tcpclient = new CClientSocket();
  CIpAddress* remoteip = NULL;

  network_data_client_t datos_client = {0};
  network_data_server_t datos_server = {0, 0, 0, 0, 0, 0, 0, 0};

  char buffer[12] = {0, 0, 0, 0, 0, 0, 0, 0};

  bool conectado = false;
  CTemporizador timeOut;
  const int iTimeOut = 5;

  SDL_Color color_negro = {0, 0, 0};
  SDL_Color color_blanco = {255, 255, 255};
  SDL_Color color_rojo = {255, 0, 0 };

  SDL_Rect cajas = {248, 250, 150, 25};

  CTecladoIP entradaTeclado("media/ttf/consolab.ttf", 30, &color_blanco, 254, 185, 16);

  CBoton* botones = new CBoton[4];
  botones[0] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Conectar"); cajas.x += 160;
  botones[1] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Atras");

  CMenu menu(botones, 2);
  int caso = 0;

  CWarning wrConectando(ttf_consolas, "Conectando...", &color_rojo);
  CWarning wrConectado(ttf_consolas, "Conectando!", &color_rojo);
  CWarning wrDesconectado(ttf_consolas, "Desconectado", &color_rojo);

  while(!conectado && !salir)
  {
    // Entrada del teclado
    while(!bTeclado && !salir)
    {
      while(SDL_PollEvent(&event))
      {
        entradaTeclado.eventuar();
        caso = menu.eventuar();

        if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) || caso == 1)
        {
          bTeclado = true;
        }
        if(event.type == SDL_QUIT)
        {
          salir = true;
          salida = -1;

          bTeclado = true;
        }
      }
      if(caso == 2)
      {
        salir = true;
        salida = 0;
      }

      aplicar_superficie(0, 0, img_fondo_mj_online_menu_client, pantalla);
      entradaTeclado.mostrar();
      menu.mostrar();

      if(SDL_Flip(pantalla) == -1)
        return -1;
    }
    // Intento de conexión
    if(!salir)
    {
      //tcpclient = new CClientSocket();
      cout << entradaTeclado.getStr() << " " << PORT_MJ << endl;
      remoteip = new CIpAddress(entradaTeclado.getStr().c_str(), PORT_MJ);

      wrConectando.mostrar_ch(300);
      if(SDL_Flip(pantalla) == -1)
        return -1;

      timeOut.empezar();
      while(timeOut.getTicks()/1000.f < iTimeOut && !conectado && !salir)
      {
        while(SDL_PollEvent(&event))
        {
          if(event.type == SDL_QUIT)
          {
            salir = true;
            salida = -1;
          }
        }
        if(tcpclient->Connect(*remoteip) && remoteip->GetHost() > 0)
        {
          if(tcpclient->Ok())
          {
#ifdef DEBUG
            cout << "Conectado" << endl;
#endif
            conectado = true;

            aplicar_superficie(0, 0, img_fondo_mj_online, pantalla);
            wrConectado.mostrar_ch(300);
            if(SDL_Flip(pantalla) == -1)
              return -1;

            SDL_Delay(1000);
          }
        }
        SDL_Delay(250);
      }
      if(!conectado)
      {
        bTeclado = false;

        delete remoteip;
      }
    }
  }

  CPad_MJ_Online_Client PJ1(der, SDLK_w, SDLK_s);
  CPad_MJ_Online_Client_Zombi PJ2(izq);
  CPelota_MJ_Online_Client pelota;
  CMarcador_Online marcador(ttf_bitM, &color_blanco);

  while(!salir)
  {
  	 fps.empezar();

  	 if(conectado)
  	 {
  	   timeOut.empezar();
  	 }
  	 // Si pasa mas de timeOut segundos sin estar conectado...
  	 if(timeOut.getTicks()/1000.f > iTimeOut)
  	 {
      salir = true;
      salida = 0;
  	 }

	    // Eventos

	   while(SDL_PollEvent(&event))
	   {
	     PJ1.eventuar(datos_client.evento);
	     if(event.type == SDL_QUIT)
	     {
		      salida = -1;
	       salir = true;
	     }
	   }

    	// Enviar datos al servidor

	   if (!conectado)
	   {
      #ifdef DEBUG
	     cout << "Desconectado." << endl;
      #endif
      if (tcpclient->Connect(*remoteip))
      {
        #ifdef DEBUG
        cout << "Conectando..." << endl;
        #endif
        if (tcpclient->Ok())
        {
          #ifdef DEBUG
          cout << "Conectado!" << endl;
          #endif
          conectado = true;
        }
      }
	   }

    if(conectado && datos_client.evento && !salir)
    {
      msgC.LoadByte(datos_client.evento);
      if(!tcpclient->Send(msgC))
      {
        #ifdef DEBUG
     	  cout << "Error enviando mensaje." << endl;
        #endif
      }
    }

    	// Recibir datos

      if(conectado && !salir)
      {
        if (tcpclient->Ready())
        {
          if(tcpclient->Receive(msgS))
          {
            msgS.UnLoad_NET_BYTES_Bytes(buffer);
            charToSdata((unsigned char*)buffer, &datos_server);

#ifdef DEBUG
            cout << "buffer: ";
            for(int i = 0; i < 8; i++)
         	    cout << buffer[i];
            cout << endl;

            cout << "buffer_int: ";
            for(int i = 0; i < 4; i++)
       	      cout << buffer_int[i] << " ";
            cout << endl;
#endif

              // Gestionar datos (dentro de "recibir").

            PJ1.setY(datos_server.pad2_y);
            PJ2.setY(datos_server.pad1_y);
            pelota.setXY(datos_server.pelota_x, datos_server.pelota_y);

            marcador.setM1(datos_server.marcador1);
            marcador.setM2(datos_server.marcador2);

            if(datos_server.fs & fsnd_pong)
            {
              Mix_PlayChannel( -1, snd_pong, 0 );
            }
            if(datos_server.fs & fsnd_pung)
            {
              Mix_PlayChannel( -1, snd_pung, 0 );
              cerr << "pung" << endl;
            }
          }
          else
          {
            #ifdef DEBUG
            cout << "Desconectado." << endl;
            #endif
            conectado = false;
          }
        }
	     }
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
  delete remoteip;

  delete botones;
  botones = NULL;

  network.Quit();
  limpiar_mj_online_client();

  return salida;
}
