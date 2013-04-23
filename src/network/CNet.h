/**
 * @file
 * @brief Declaración de todas las clases para la interfaz de red.
 *
 * Todas estas clases son un extraco de http://www.sdltutorials.com/sdl-net-part-1-user-tutorial Un ejemplo de comunicación entre cliente y servidor por medio de las clases declaradas en este archivo puede ser
 * la siguiente:
 *
 * @image html net_1.png
 *
 * Para mayor información sobre las estructuras que encapsulan las clases declaradas en esta cabecera, visite
 * http://www.libsdl.org/projects/SDL_net/docs/
 */

#ifndef CNET_H_
#define CNET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstring>
#include <SDL/SDL_net.h>

#include "../globals.h"

typedef char charbuf [256]; /**< Definición de tipo charbuff como char[256] */

//***********************
//******* CNET **********
//***********************

/**
 * @brief Clase base de red
 *
 * Se encarga de inicializar y desinicializar las librerías de SDL_net para su uso en el programa.
 * Vea el archivo CNet.h para mayor información de todas las clases de red.
 */
class CNet{
  public:
    static bool Init(); //Initialize SDL_net
    static void Quit(); //Exit SDL_net
};

//***********************
//***** CNETMESSAGE *****
//***********************

/**
 * @brief Clase base de mensaje de red
 *
 * Se utiliza como contenedor para mandar datos en red. Por defecto, sirve para cargar y descargar cadenas de caracteres.
 * Vea el archivo CNet.h para mayor información de todas las clases de red.
 */
class CNetMessage
{
  protected:
    charbuf buffer; /**< Mensaje almacenado en un buffer de tipo charbuf, limitado a 256 caracteres. */
    enum bufstates { EMPTY, READING, WRITING, FULL }; /**< Distintos estados del mensaje. */
    bufstates state; /**< El estado del mensaje.*/
    void reset();
  public:
    CNetMessage(); //constructor
    //Virtual member function that indicates how many bytes may have to be loaded into the instance. By default, it works with strings that have a maximum
    //of 255 characters.
    virtual int NumToLoad();

    //Virtual member function that indicates how many bytes may have to be downloaded from the instance.
    virtual int NumToUnLoad();

    void LoadBytes(charbuf& inputbuffer, int n); //Load a char set into the message buffer
    //void UnLoadBytes(charbuf& destbuffer); //Unload a char set from the buffer
    void UnLoadBytes(charbuf& destbuffer);
    void finish(); //set the state object to full. No more data to be loaded
};

/**
 * @brief Clase para mensajes de red de N bytes
 *
 * Se utiliza como contenedor para mandar datos en red. Sirve para mandar paquetes codificados en un conjunto de caracteres
 * que simbolizan una secuencia de bytes. La cantidad de bytes no debe sobrepasar los 256 bytes.
 * Vea el archivo CNet.h para mayor información de todas las clases de red.
 */
class CNetMessageN : public CNetMessage
{
  private:
    uint buffer_size; /**< Numero de bytes a cargar y descargar. No sirven funciones convencionales como strlen()*/
//Virtual function that indicates how many bytes may have to be loaded onto the object. Overrides the parent class function member to work with only a byte
    virtual int NumToLoad();
//Virtual function that indicates how many bytes may have to be downloaded from the object. Overrides the parent class function member to work with only a byte
    virtual int NumToUnLoad();
  public:
    /**
     * @brief Constructor principal
     *
     * @param n Numero de bytes a guardar en #buffer_size.
     */
    CNetMessageN(uint n): CNetMessage(), buffer_size(n) {reset();};
//Function simpler than LoadBytes(), inherited from the parent class, as it only works with one byte
    void LoadNBytes(char* in);
//Function simpler than UnLoadBytes(), inherited from the parent class, as it only works with one byte
    void UnLoadNBytes(char* out);
};

//***********************
//***** CIPADRESS *******
//***********************

/**
 * @brief Clase para encapsular una variable de tipo m_Ip
 *
 * Vea el archivo CNet.h para mayor información de todas las clases de red.
 */
class CIpAddress
{
  private:
    IPaddress m_Ip; /**< Estructura Ipaddress que contiene una dirección IPv4 y un puerto, ambos para el destino */
  public:
    CIpAddress(); //constructor
    CIpAddress (Uint16 port); //create and associate a port to the instance
    CIpAddress (std::string host, Uint16 port); //create and associate a port and a host to the instance
    void SetIp (IPaddress sdl_ip); //set a CIpAddress object from an existing SDL IPaddress
    bool Ok() const; //True if the object have a port and a host associated to it
    IPaddress GetIpAddress() const; //return a SDL_net IPaddress structure
    Uint32 GetHost() const; //return the host
    Uint16 GetPort() const; //return the port
};

/**
 * @brief Clase para encapsular la estructura TCPsocket
 *
 * Cada objeto de esta clase representa un socket o buzón en nuestro programa. La gestión de los mismos vienen
 * dadas por el sistema operativo y por las librerías de SDL_net.
 */
class CTcpSocket {
  protected:
    TCPsocket m_Socket; /**< La estructura TCPsocket de un socket TCP. */
    SDLNet_SocketSet set; /**< Un conjunto de sockets. Usado para comprobar la existencia de paquetes.*/
  public:
    CTcpSocket();
    virtual ~CTcpSocket();
    virtual void SetSocket (TCPsocket  the_sdl_socket); //set a CTcpSocket object from a existing SDL socket
    bool Ok() const; //indicate if theres is a TCPsocket associated to the instance
    bool Ready() const; //True if there are bytes ready to be read
    virtual void OnReady(); //pure virtual
};

//***********************
//***** HOSTSOCKET ******
//***********************

class CClientSocket;
/**
 * @brief Clase que representa el socket remoto de la conexión
 *
 * Se usará para aceptar paquetes y conexiones entrantes al programa.
 */
class CHostSocket : public CTcpSocket {
  public:
    CHostSocket (CIpAddress& the_ip_address); //create and open a new socket, with an existing CIpAddress object
    CHostSocket (Uint16 port); //create and open a new socket with the desired port

    bool Accept (CClientSocket&); //set a client CTcpSocket object after listening to the port
    virtual void OnReady(); //pure virtual
};

//***********************
//**** CLIENTSOCKET *****
//***********************

/**
 * @brief Clase que representa el socket cliente (local) de la conexión
 *
 * Se usará para enviar y recibir paquetes y conexiones del programa.
 */
class CClientSocket : public CTcpSocket {
  private:
    CIpAddress m_RemoteIp; /**< Objeto CIpAddress correspondiente al host remoto */
  public:
    CClientSocket(); //constructor
    CClientSocket (std::string host, Uint16 port); //Create the object and connect to a host, in a given port
    bool Connect (CIpAddress& remoteip); //make a connection to communicate with a remote host
    bool Connect (CHostSocket& the_listener_socket); //make a connection to communicate with a client
    void SetSocket (TCPsocket  the_sdl_socket); //set a CTcpSocket object from an existing SDL_net socket
    CIpAddress getIpAddress () const; //return a CIpAddress object associated to the remote host
    virtual void OnReady(); //pure virtual
    bool Receive(CNetMessage& rData); //receive data and load it into a CNetMessage object
    bool Send (CNetMessage& sData); //send data from a CNetMessage object
};


#endif /* CNET_H_ */
