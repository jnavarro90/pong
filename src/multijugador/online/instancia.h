#ifndef INSTANCIA_MJ_ONLINE_H_
#define INSTANCIA_MJ_ONLINE_H_

#include "pelota_mj_online.h"
#include "pad_mj_online.h"
#include "tecladoIP.h"
#include "network_struct.h"

#include "marcador_online.h"

#include "../../instance.h"
#include "../../temporizador.h"
#include "../../warning.h"
#include "../../menu/menu.h"

#include "../../network/CNet.h"

enum wr_t { eConectado = 0x01, eConectando = 0x02, eDesconectado = 0x04};

const int iTriesOut = 5; // Numero de intentos de conexion
const int iTriesTimeOut = 1; // Segundos ente cada intento
const int iTimeOut = 6; // Tiempo de pérdida de conexión en el juego

class CInstance_MJ_Online_Client: public CInstance
{
  protected:
    bool conectado;
    //bool conectando;

    bool bTeclado;
    //bool bMenu;

    SDL_Color color_negro;
    SDL_Color color_blanco;
    SDL_Color color_rojo;

    SDL_Surface* fondo_menu;

    // Red
    CNet network;
    CClientSocket* tcpclient;
    CIpAddress* remoteip;

    CNetwork_Data_Server* datos_server;
    CNetwork_Data_Client* datos_cliente;

    CNetMessage1* msgC;
    CNetMessage_NET_BYTES_* msgS;

    // Menu
    CBoton* botones;
    CMenu* menu;

    CTecladoIP* entradaTeclado;

    // Warnings
    CWarning* wrConectando;
    CWarning* wrConectado;
    CWarning* wrDesconectado;

    // Jugabilidad
    CPad_MJ_Online_Client* PJ1;
    CPad_MJ_Online_Client_Zombi* PJ2;
    CPelota_MJ_Online_Client* pelota;
    CMarcador_Online* marcador;

    // Temporizadores
    CTemporizador* timeOut;
  public:
    CInstance_MJ_Online_Client();
    ~CInstance_MJ_Online_Client();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop(int& salida);
    void OnRender();

    void OnEventMenu(int& salida);
    void OnLoopMenu(flags& F);
    void OnRenderMenu(flags& F);
};

class CInstance_MJ_Online_Server: public CInstance
{
  protected:
    bool conectado;

    SDL_Color color_negro;
    SDL_Color color_blanco;
    SDL_Color color_rojo;

    SDL_Surface* fondo_menu;

    // Red
    CNet network;
    CClientSocket* tcpclient;
    CHostSocket* tcplistener;

    CNetwork_Data_Server* datos_server;
    CNetwork_Data_Client* datos_cliente;

    CNetMessage1* msgC;
    CNetMessage_NET_BYTES_* msgS;

    // Menu
    CBoton* botones;
    CMenu* menu;

    // Warnings
    CWarning* wrConectado;
    CWarning* wrDesconectado;

    // Jugabilidad
    CPad_MJ_Online* PJ1;
    CPad_MJ_Online_Zombi* PJ2;
    CPelota_MJ_Online* pelota;
    CMarcador* marcador;

    // Temporizadores
    CTemporizador* timeOut;
  public:
    CInstance_MJ_Online_Server();
    ~CInstance_MJ_Online_Server();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop(int& frame); // chapuza
    void OnRender();

    void OnEventMenu(int& salida);
    void OnLoopMenu(flags& F);
    void OnRenderMenu(flags& F);
};

#endif /* INSTANCIA_MJ_ONLINE_H_ */
