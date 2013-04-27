/**
 * @file
 * @brief Declaración de CInstance_MJ_Online_Client y CInstance_MJ_Online_Server
 *
 */

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

/**
 * @brief Enum para conocer los estados de la conexión
 */
enum wr_t
{
  eConectado = 0x01 /**< Conexión en estado "conectada"*/
  ,eConectando = 0x02 /**< Conexión en estado "conectando"*/
  ,eDesconectado = 0x04  /**< Conexión en estado "desconectada"*/
};

const int iTriesOut = 5; /**< Numero de intentos de conexion*/
const int iTriesTimeOut = 1; /**< Segundos entre cada intento*/
const int iTimeOut = 6; /**< Tiempo de pérdida de conexión en el juego*/

/**
 * @brief Clase de estancia para representar el modo de juego multijugador-online desde el cliente
 *
 * Básicamente, encapsula algunos objetos (1 pad, 1 pad "zombi", 1 pelota "zombi" y 1 marcador "zombi")
 * para trabajar con ellos de una forma más sencilla. El cliente, primero entrará en un menu desde el que debe conectar
 * a la dirección ip del servidor (con el puerto #NET_MJ_PORT). Una vez realizada la conexión, el usuario
 * recibirá la configuración de la partida ubicada en el servidor en COpciones, y hará las operaciones oportunas.
 * Posteriormente, el bucle de la partida en el cliente es el siguiente:
 *
 * <pre>
 * Mientras(ejecutando)
 *   Gestionar datos de entrada
 *   Enviar datos de entrada al servidor
 *   Recibir datos procesados del servidor
 *   Mostrar por pantalla
 *   Si hay que hacer salto de frames
 *     Saltar frame
 *   Si no
 *     Esperar frame
 * FinMientras
 * </pre>
 *
 * Por defecto, el pad del cliente es el derecho.
 *
 * Para más información sobre el funcionamiento de las estancias, vea las definiciones de los métodos de
 * esta clase y las clases CInstance, CEngine, CMenu y CBoton.
 */
class CInstance_MJ_Online_Client: public CInstance
{
  protected:
    bool conectado; /**< ¿Conectado? */
    bool bTeclado; /**< ¿Introduciendo dirección IP? */

    SDL_Color color_negro;
    SDL_Color color_blanco;
    SDL_Color color_rojo;

    SDL_Surface* fondo_menu; /**< Fondo a mostrar en el menú*/

    // Red
    CNet network;
    CClientSocket* tcpclient;
    CIpAddress* remoteip;

    CNetwork_Data_Server* datos_server; /**< Estructura de datos del servidor*/
    CNetwork_Data_Client* datos_cliente; /**< Estructura de datos del cliente*/

    CNetMessageN* msgC;
    CNetMessageN* msgS;

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
    CTemporizador* timeFrameSkip;
    bool frameSkip;
  public:
    CInstance_MJ_Online_Client();
    ~CInstance_MJ_Online_Client();

    bool Init();
      bool LoadFiles();
      bool LoadMenu();
    void LoadObjects();

    void Close();
      void UnLoadFiles();
      void UnLoadMenu();
    void UnLoadObjects();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop(int& salida);
    void OnRender();

    void OnEventMenu(int& salida);
    void OnLoopMenu(flags& F);
    void OnRenderMenu(flags& F);
};


/**
 * @brief Clase de estancia para representar el modo de juego multijugador-online desde el servidor
 *
 * Básicamente, encapsula algunos objetos (2 pads, 1 pelota y 1 marcador)
 * para trabajar con ellos de una forma más sencilla. El cservidor, primero entrará en un menu desde el que debe esperar
 * la conexión de algún cliente (con el puerto #NET_MJ_PORT). Una vez realizada la conexión, el usuario
 * enviará la configuración de la partida, ubicada en COpciones. Posteriormente, el bucle de la partida en el servidor
 * es el siguiente:
 *
 * <pre>
 * Mientras(ejecutando)
 *   Gestionar datos de entrada
 *   Recibir datos de entradadel cliente
 *   Procesar datos de entrada
 *   Enviar datos procesados al cliente
 *   Mostrar por pantalla
 * FinMientras
 * </pre>
 *
 * Por defecto, el pad del servidor es el izquierdo.
 *
 * Para más información sobre el funcionamiento de las estancias, vea las definiciones de los métodos de
 * esta clase y las clases CInstance, CEngine, CMenu y CBoton.
 */
class CInstance_MJ_Online_Server: public CInstance
{
  protected:
    bool conectado;

    SDL_Color color_negro;
    SDL_Color color_blanco;
    SDL_Color color_rojo;

    SDL_Surface* fondo_menu; /**< Fondo a mostrar en el menú*/
    // Red
    CNet network;
    CClientSocket* tcpclient;
    CHostSocket* tcplistener;

    CNetwork_Data_Server* datos_server; /**< Estructura de datos del servidor*/
    CNetwork_Data_Client* datos_cliente; /**< Estructura de datos del cliente*/

    CNetMessageN* msgC;
    CNetMessageN* msgS;

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
    CTemporizador* timeFrameSkip;
  public:
    CInstance_MJ_Online_Server();
    ~CInstance_MJ_Online_Server();

    bool Init();
      bool LoadFiles();
      void LoadObjects();

    void Close();
      void UnLoadFiles();
      void UnLoadObjects();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop(int& frame); // chapuza
    void OnRender();

    void OnEventMenu(int& salida);
    void OnLoopMenu(flags& F);
    void OnRenderMenu(flags& F);
};

#endif /* INSTANCIA_MJ_ONLINE_H_ */
