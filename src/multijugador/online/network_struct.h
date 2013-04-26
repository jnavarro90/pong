/**
 * @file
 * @brief Declaraci�n de CNetwork_Data_Client, CNetwork_Data_Server y CNetwork_Data_Settings
 *
 * Usado en el modo de juego multijugador-online. Vea CInstance_MJ_Online_Client y CInstance_MJ_Online_Server
 *
 */

#ifndef NETWORK_STRUCT_H_
#define NETWORK_STRUCT_H_

#include "../../globals.h"

// Por simplicidad, vamos a suponer que un jugador hace de servidor, y otro, de cliente

/**
 * @enum fSnd_pelota Estados de los flags para enviar al cliente que sonido ejecutar.
 */
enum fSnd_pelota
{
  fsnd_empty = 0x00 /**< Sonido "vac�o". No reproducir nada.*/
  ,fsnd_pong = 0x01 /**< Sonido "pong" para indicar rebote */
  ,fsnd_pung = 0x02 /**< Sonido "pung" para indicar un punto de partido */
};

/**
 * @brief Estructura de datos a mandar desde el cliente al servidor
 *
 * Desde el cliente se mandar�n s�lo los eventos del usuario (si mueve hacia arriba o hacia abajo)
 * y los ticks del temporizador de la estancia del cliente, que posteriormente se comprobar�n
 * con los del servidor para realizar ajustes.
 */

class CNetwork_Data_Client
{
  private:
    char buffer[NET_MJ_CLIENTDATA_SIZE]; /**< Buffer de caracteres (bytes) de tama�o #NET_MJ_CLIENTDATA_SIZE para enviar al servidor*/
  public:
    int8 evento; /**< Evento del cliente (jugador 2). 1 = se mueve hacia arriba, -1 = se mueve hacia abajo, 0 = no se mueve*/ // 1 byte
    Uint32 ticks; /**< N�mero de ticks del temporizador del cliente. El servidor lo verificar� para saber si debe recibir datos del cliente*/ // 4 bytes
    int8 unused; /**< Sin usar, para conseguir un n�mero par de bytes*/// 1 byte
    // Total: 6 bytes
  public:
    CNetwork_Data_Client(); /**< @brief Constructor por defecto */

    void makeBuffer();
    char* getBuffer();

    void readBuffer(char* b);
};

/**
 * @brief Estructura de datos a mandar desde el servidor al cliente
 *
 * Todos los datos ser�n procesados en el ordenador. El servidor recibir� llos eventos del cliente, har� los c�lculos
 * necesarios (movimientos de los pads y la pelota) y mandar� los datos procesados al cliente para que se muestren.
 */
class CNetwork_Data_Server
{
  private:
    char buffer[NET_MJ_SERVERDATA_SIZE];/**< Buffer de caracteres (bytes) de tama�o #NET_MJ_SERVERDATA_SIZE para enviar al cliente*/
  public:
    int16 pelota_x; /**< Posici�n horizontal de la pelota*/ // 2 bytes
    int16 pelota_y; /**< Posici�n vertical de la pelota*/  // 2 bytes
    int16 pad1_y;  /**< Posici�n vertical del pad del jugador 1(servidor)*/ // 2 bytes
    int16 pad2_y;  /**< Posici�n vertical del pad del jugador 2(cliente)*/  // 2 bytes
    flags fs;  /**< Flags de sonido para que el cliente sepa cuando emitirlos*/ // 1 byte
    uint8 marcador1; /**< Puntuaci�n del jugador 1(servidor)*/ // 1 byte
    uint8 marcador2; /**< Puntuaci�n del jugador 2(cliente)*/  // 1 byte
    uint8 sinUso; /**< Sin usar, para conseguir un n�mero par de bytes*/ // 1 byte
    // ticks usado  para tratar retardos y saltar frames
    Uint32 ticks; /**< N�mero de ticks del temporizador del servidor. El cliente lo utilizar� para saber si debe recibir o enviar datos al servidor*/ // 4 bytes
    // Total: 16 bytes
  public:
    CNetwork_Data_Server(); /**< @brief Constructor por defecto */

    void makeBuffer();
    char* getBuffer();

    void readBuffer(uchar* b);
};


/**
 * @brief Estructura de datos a mandar desde el servidor al cliente al principio, que contendr� las opciones del juego
 *
 * Al principio de la conexi�n, el servidor deber� mandar la configuraci�n de la partida, que contendr�
 * datos como tama�o de los pads, de la pelota, de la pantalla o el n�mero de puntos para acabar la partida (no implementado).
 */
class CNetwork_Data_Settings
{
  private:
    char buffer[NET_MJ_SETTINGS_SIZE]; /**< Buffer de caracteres (bytes) de tama�o #NET_MJ_SETTINGS_SIZE para enviar al cliente*/
  public:
    int16 PANTALLA_ANCHO;/**< Ancho de la pantalla extra�do de COpciones::PANTALLA_ANCHO del servidor*/ // 2 bytes
    int16 PANTALLA_ALTO;/**< Alto de la pantalla extra�do de COpciones::PANTALLA_ALTO del servidor*/  // 2 bytes

    int16 PAD_ALTO; /**< Alto del pad extra�do de COpciones::PAD_ALTO del servidor*/ // 2 bytes
    int16 PAD_ANCHO; /**< Ancho del pad extra�do de COpciones::PAD_ANCHO del servidor*/ // 2 bytes

    int16 PELOTA_ALTO;  /**< Alto de la pelota extra�do de COpciones::PELOTA_ALTO del servidor, equivalente a COpciones::PELOTA_ANCHO*/ // 2 bytes
    int16 unused; /**< Sin usar, para conseguir un n�mero par de bytes*/ // 2 bytes
    // Total: 12 bytes
  public:
    CNetwork_Data_Settings(); /**< @brief Constructor por defecto */

    void makeBuffer();
    char* getBuffer();

    void readBuffer(uchar* b);
};

#endif /* NETWORK_STRUCT_H_ */
