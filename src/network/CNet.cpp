/**
 * @file
 * @brief Declaración de todas las clases para la interfaz de red.
 *
 * Vea el fichero CNet.h para una mejor descripción.
 */

#include "CNet.h"

//***********************
//******** NET **********
//***********************

/**
 * @brief Inicia el servicio de red de SDL_net
 */
bool CNet::Init()
{
  if (SDLNet_Init() < 0)
  {
    std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
    return false;
  }
  else
    return true;
}

/**
 * @brief Desinicializa el servicio de red de SDL_net
 */
void CNet::Quit()
{
  SDLNet_Quit();
}

//***********************
//***** NETMESSAGE ******
//***********************

/**
 * @brief Constructor por defecto
 *
 * Crea el mensaje reseteado todos los datos mediante la función reset().
 */
CNetMessage::CNetMessage()
{
    reset();
}

/**
 * @brief Función de reseteo
 *
 * Resetea el mensaje. Llena la variable buffer con ceros y cambia el estado #state a EMPTY.
 */
void CNetMessage::reset()
{
  for (int i =0; i < 256; i++)
    buffer [i] = 0;
  state = EMPTY;
}

/**
 * @brief Finaliza la lectura del mensaje
 *
 * Si el mensaje está en el estado READING, cambia su estado a FULL para determinar que está lleno.
 */
void CNetMessage::finish() {
    if (state == READING)
        state = FULL;
}

/**
 * @brief Indicador de cuantos caracteres hay que cargar.
 *
 * @return Devuelve el número de caracteres a cargar.
 *
 * En caso de que el mensaje está vacío (EMPTY), se ha de cargar completamente, con 255 caracteres. En caso contrario, no se puede
 * cargar ningún carácter (FULL).
 */
int CNetMessage::NumToLoad() {
    if (state == EMPTY)
        return 255;
    else
        return 0;
}

/**
 * @brief Indicador de cuantos caracteres hay que descargar.
 *
 * @return Devuelve el número de caracteres a descargar.
 *
 * En caso de que el mensaje esté lleno (FULL), se ha de descargar completamente, con el tamaño de la
 * cadena almacenada en buffer por medio de la función strlen(). En caso contrario, no se puede
 * descargar ningún carácter (FULL).
 */
int CNetMessage::NumToUnLoad() {
    if (state == FULL)
        return strlen(buffer) + 1;
    else
        return 0;
}

/**
 * @brief Cargador del buffer
 *
 * @param inputbuffer Buffer de entrada para cargar en #buffer
 * @param n Número de bytes de inputbuffer a cargar
 *
 * Se cargan los primeros n bytes del buffer de entrada en la variable #buffer.
 * Posteriormente, se cambia el estado del mensaje a lecutra (READING).
 */
void CNetMessage::LoadBytes(charbuf& inputbuffer, int n) {
    for (int i = 0; i < n; i++)
        buffer[i] = inputbuffer[i];
    state = READING;
}

/**
 * @brief Descargador del buffer
 *
 * @param destbuffer Buffer de salida para descargar desde #buffer
 *
 * Se descargan los byteses pecificados por NumToUnLoad() de la variable #buffer en el parametro destbuffer.
 * Posteriormente, se cambia el estado del mensaje a vacío (EMPTY).
 */
void CNetMessage::UnLoadBytes(charbuf& destbuffer) {
    for (int i=0; i < this->NumToUnLoad(); i++)
        destbuffer[i] = buffer[i];
    reset();
}

/**
 * @brief Indicador de cuantos caracteres hay que cargar.
 *
 * @return Devuelve el número de caracteres a cargar.
 *
 * En caso de que el mensaje está vacío (EMPTY), se ha de cargar completamente, con #buffer_size caracteres. En caso contrario, no se puede
 * cargar ningún carácter (FULL).
 */
int CNetMessageN::NumToLoad()
{
  if (state == EMPTY)
   return buffer_size;
  else
   return 0;
}

/**
 * @brief Indicador de cuantos caracteres hay que descargar.
 *
 * @return Devuelve el número de caracteres a descargar.
 *
 * En caso de que el mensaje está lleno (FULL), se ha de descargar completamente, con #buffer_size caracteres.
 * En caso contrario, no se puede descargar ningún carácter (EMPTY).
 */
int CNetMessageN::NumToUnLoad()
{
  if (state == FULL)
   return buffer_size;
  else
   return 0;
}

/**
 * @brief Cargador del buffer
 *
 * @param entrada Buffer de entrada para cargar en #buffer
 *
 * Se cargan los primeros #buffer_size bytes del buffer de entrada (entrada) en la variable #buffer.
 * Posteriormente, se cambia el estado del mensaje a lecutra (READING).
 */
void CNetMessageN::LoadNBytes(char* entrada)
{
  charbuf c;

  for(uint i = 0; i < buffer_size; i++)
    c[i] = entrada[i];

  LoadBytes(c, buffer_size);
  finish();
}

/**
 * @brief Descargador del buffer
 *
 * @param salida Buffer de salida para descargar desde #buffer
 *
 * Se descargan los bytes especificados por #buffer_size de la variable #buffer en el parametro salida.
 * Posteriormente, se cambia el estado del mensaje a vacío (EMPTY).
 */

void CNetMessageN::UnLoadNBytes(char* salida) // Retocar esta función
{
  charbuf c;

  UnLoadBytes(c);

  for(uint i = 0; i < buffer_size; i++)
	   salida[i] = c[i];
}

//***********************
//****** IPADRESS *******
//***********************

/**
 * @brief Constructor principal
 *
 * @param port Puerto para intentar abrir una conexión.
 *
 * Intenta abrir una ruta hacia la dirección especificada por #m_Ip mediante el puerto especificado en los parámetros.
 * En caso de error, asigna valores a cero y registra un mensaje de error en la librería de SDL_net.
 */
CIpAddress::CIpAddress (Uint16 port) {
    if (SDLNet_ResolveHost(&m_Ip, NULL, port) < 0){
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        m_Ip.host = 0;
        m_Ip.port = 0;
    }
}

/**
 * @brief Constructor principal
 *
 * @param host Dirección del host para intentar abrir una conexión.
 * @param port Puerto para intentar abrir una conexión.
 *
 * Intenta abrir una ruta hacia la dirección especificada por #m_Ip mediante el puerto y el host especificado en los parámetros.
 * En caso de error, asigna valores a cero y registra un mensaje de error en la librería de SDL_net.
 */
CIpAddress::CIpAddress (std::string host, Uint16 port) {
    if (SDLNet_ResolveHost(&m_Ip, host.c_str(), port) < 0) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        m_Ip.host = 0;
        m_Ip.port = 0;
    }
}

/**
 * @brief Constructor por defecto
 *
 * Asigna valores nulos a los miembros de la estructura #m_Ip (m_Ip.host = m_Ip.port = 0).
 */
CIpAddress::CIpAddress() {
    m_Ip.host = 0;
    m_Ip.port = 0;
}

/**
 * @brief Verificador
 *
 * @return En caso de que todo haya funcionado correctament, devolverá true. Si algo ha fallado, devolverá false.
 *
 * Verifica que la creación del objeto haya sido correcta.
 */
bool CIpAddress::Ok() const {
    return !(m_Ip.port == 0);
}

/**
 * @brief Asignador de dirección IP
 *
 * @param sdl_ip Dirección IP que se le asignará a #m_Ip
 *
 * Cambia la dirección IP del objeto por la especificada en los parámetros (sdl_ip).
 */
void CIpAddress::SetIp (IPaddress sdl_ip) { //sets a CTcpSocket object from a existing SDL socket
    m_Ip = sdl_ip;
}

/**
 * @brief Obtener la estructura #m_Ip del objeto
 *
 * @return Devuelve una copia de la estructura #m_Ip
 */
IPaddress CIpAddress::GetIpAddress() const {
    return m_Ip;
}

/**
 * @brief Obtener el valor almacenado por m_Ip.host
 *
 * @return Devuelve una copia del valor de m_Ip.host como dirección IPv4
 */
Uint32 CIpAddress::GetHost() const {
    return m_Ip.host;
}

/**
 * @brief Obtener el valor almacenado por m_Ip.port
 *
 * @return Devuelve una copia del valor de m_Ip.port
 */
Uint16 CIpAddress::GetPort() const {
    return m_Ip.port;
}

//***********************
//****** TCPSOCKET ******
//***********************

/**
 * @brief Constructor por defecto
 *
 * Asigna un valor nulo a la estructura #m_Socket y guarda memoria para el conjunto de sockets #set con un tamaño de 1.
 */
CTcpSocket::CTcpSocket() {
    m_Socket = NULL;
    set = SDLNet_AllocSocketSet(1);
}

/**
 * @brief Destructor
 *
 * Si #m_Socket no es nulo, se liberará el espacio en memoria que ocupa la estructura.
 * Además, se libera el espacio que ocupa el conjunto #set y cierra el socket m_Socket.
 */
CTcpSocket::~CTcpSocket() {
    if (!(m_Socket == NULL)) {
          SDLNet_TCP_DelSocket(set,m_Socket);
        SDLNet_FreeSocketSet(set);
        SDLNet_TCP_Close (m_Socket);
    }
}

/**
 * @brief Asignador de la estructura m_Socket
 *
 * @param the_sdl_socket Copia de una estructura TCPsocket para realizar la copia.
 *
 * Si la estructura #m_Socket no es nula, liberará el espacio que ocupa y cerrará el puerto asignado. Acto seguido,
 * realizará la asignación de #m_Socket con el parámetro the_sdl_socket. Si algo ha fallado, SDL_net generará un error.
 */
void CTcpSocket::SetSocket (TCPsocket the_sdl_socket) {
    if (!(m_Socket == NULL)) {
          SDLNet_TCP_DelSocket(set,m_Socket);
          SDLNet_TCP_Close (m_Socket);
      }
    m_Socket = the_sdl_socket;
    if(SDLNet_TCP_AddSocket(set,m_Socket)==-1) {
        std::cerr << "SDLNet_TCP_AddSocket: " << SDLNet_GetError() << std::endl;
        m_Socket = NULL;
    }
}

/**
 * @brief Verificador
 *
 * @return En caso de que se haya iniciado todo correctamente, devolverá true. En caso contrario, devolverá false.
 */
bool CTcpSocket::Ok() const {
    return !(m_Socket == NULL);
}

/**
 * @brief Comprobador "Ready"
 *
 * @return Si todo está listo y correcto para la conexión, devolverá true. En caso contrario, devolverá false.s
 *
 * Comprueba que todo esté correcto para la conexión.
 */
bool CTcpSocket::Ready() const {
    bool rd = false;
    int numready = SDLNet_CheckSockets(set, 0);
    if (numready == -1)
            std::cerr << "SDLNet_CheckSockets: " << SDLNet_GetError() << std:: endl;
      else
            if (numready)
                rd = SDLNet_SocketReady (m_Socket);
      return rd;
}

/**
 * @brief Función a realizar cuando el socket esté listo
 *
 * No tiene ningún uso por el momento.
 */
void CTcpSocket::OnReady() {

}

//***********************
//***** HOSTSOCKET ******
//***********************

/**
 * @brief Constructor principal
 *
 * @param the_ip_address Dirección ip para abrir el socket.
 *
 * Se encarga de iniciar el objeto del socket a partir de una estructura de datos CIpAddress. En caso de no poder
 * crear el socket, SDL_net generará un error.
 */
CHostSocket::CHostSocket(CIpAddress& the_ip_address)
{
  CTcpSocket();
  IPaddress iph = the_ip_address.GetIpAddress();
  if(!(m_Socket = SDLNet_TCP_Open(&iph)))
  {
    SDLNet_FreeSocketSet(set);
    std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
  }
}

/**
 * @brief Constructor principal
 *
 * @param port Puerto para establecer la conexión.
 *
 * Se encarga de iniciar el objeto del socket a partir de un puerto dado. Se generará una estructura de tipo
 * CIpAddress a partir del puerto. Posteriormente, se intentará crear el socket.
 * En caso de no poder crear el socket, SDL_net generará un error.
 */
CHostSocket::CHostSocket (Uint16 port) {
    CIpAddress iplistener (port);
    if (!iplistener.Ok()) {
        m_Socket = NULL;
    }
    else {
        CTcpSocket();
        IPaddress iph = iplistener.GetIpAddress();
        if (!(m_Socket = SDLNet_TCP_Open(&iph))) {
            SDLNet_FreeSocketSet(set);
            std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        }
    }
}

/**
 * @brief Acepta conexiones entrantes
 *
 * @return En caso de no poder aceptar ninguna conexión, devolverá false. Si se puede aceptar una conexión entrante,
 * devolverá true.
 *
 * Se intentará entablar una conexión con un cliente remoto por medio de la función SDLNet_TCP_Accept().
 * Si todo va bien, se entablará la conexión.
 */
bool CHostSocket::Accept (CClientSocket& the_client_socket) {
    TCPsocket cs;
    if ((cs = SDLNet_TCP_Accept(m_Socket))) {
        the_client_socket.SetSocket(cs);
        return true;
    }
    else
        return false;
}

/**
 * @brief Función a realizar cuando el socket esté listo
 *
 * No tiene ningún uso por el momento. Función virtual.
 */
void CHostSocket::OnReady() {}

//***********************
//***** CLIENTSOCKET ****
//***********************

/**
 * @brief Constructor por defecto
 *
 * Llama al constructor de la clase base (CTcpSocket) y asigna valores por defecto.
 */
CClientSocket::CClientSocket() {
    CTcpSocket();
}

/**
 * @brief Constructor principal
 *
 * @param host Dirección del host como una cadena de caracteres
 * @param port Puerto para realizar la conexión con el host remoto.
 *
 * Primero, se creará un objeto del tipo CIpAddress con los parámetros pasados al constructor.
 * Se intentará conectar con el host. En caso de que haya algún error, se asignará un valor nulo a #m_Socket.
 */
CClientSocket::CClientSocket (std::string host, Uint16 port) {
    CIpAddress remoteip (host.c_str(), port);
    if (!remoteip.Ok()) {
        m_Socket = NULL;
    }
    else {
        CTcpSocket();
        Connect(remoteip);
    }
}

/**
 * @brief Intento de conexión
 *
 * @param the_listener_socket Socket remoto a la escucha.
 *
 * @return Devuelve siempre false.
 *
 * No tiene ningún uso con estos parámetros de momento
 */
bool CClientSocket::Connect (CHostSocket& the_listener_socket) {
    return false;
}

/**
 * @brief Intento de conexión
 *
 * @param remoteip Dirección y puerto del host remoto
 *
 * @return Si se ha entablado la conexión, devolverá true. En caso contrario, devolverá false.
 *
 * Se intentará conectar abriendo una conexión al host remoto. En caso de fallar, se generará un error de SDL_net.
 * Si se genera, se creará el socket remoto con SetSocket()
 *
 */
bool CClientSocket::Connect (CIpAddress& remoteip) {
    TCPsocket cs;
    IPaddress ip = remoteip.GetIpAddress();
    if ((cs = SDLNet_TCP_Open(&ip)))
    {
        SetSocket(cs);
        return true;
    }
    else {
        std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        return false;
    }
}

/**
 * @brief Inicia un socket
 *
 * @param the_sdl_socket Socket del cliente a crear.
 *
 * Se intentará crear el socket. Si nada falla, se creará el socket. Si ha fallado algo, SDL_net generará un error.
 */
void CClientSocket::SetSocket (TCPsocket the_sdl_socket) {
    CTcpSocket::SetSocket (the_sdl_socket);
    IPaddress* ips;
    if ((ips = SDLNet_TCP_GetPeerAddress(m_Socket))) {
    /* Print the address, converting it onto the host format */
        m_RemoteIp.SetIp(*ips);
        Uint32 hbo = m_RemoteIp.GetHost();
        Uint16 pbo = m_RemoteIp.GetPort();
        std::cout << "Client connected: " << SDLNet_Read32(&hbo) << ' '
            << SDLNet_Read16 (&pbo) << std::endl;
    }
    else
        std::cerr << "SDLNet_TCP_GetPeerAddress: " << SDLNet_GetError() << std::endl;
}

/**
 * @brief Obtener la dirección IP del host remoto
 *
 * @return Devuelve una copia del objeto m_RemoteIp
 */
CIpAddress CClientSocket::getIpAddress () const {
    return m_RemoteIp;
}

/**
 * @brief Recibir un paquete encapsulado en un objeto del tipo CNetMessage
 *
 * @param rData Estructura donde se van a almacenar los datos recibidos.
 *
 * @return Si se ha recibido algo, devolverá true. En caso de no recibir nada, devolverá false (llamada no bloqueante).
 *
 * Una vez recibido el mensaje, se cambia su estado a FULL.
 */
bool CClientSocket::Receive(CNetMessage& rData) {
//Firstly, check if there is a socket
    if (m_Socket == NULL)
        return false;
    charbuf buf;

//Check if the instance can receive bytes, if it can, load the number of bytes specified by NumToLoad() virtual function
    while (rData.NumToLoad() > 0) {
        if (SDLNet_TCP_Recv(m_Socket, buf, rData.NumToLoad()) > 0) {
            rData.LoadBytes (buf, rData.NumToLoad());
        }
        else {
            return false;
        }
    }
    rData.finish();
    return true;
}

/**
 * @brief Enviar un paquete encapsulado en un objeto del tipo CNetMessage
 *
 * @param sData Estructura de donde se sacarán los datos a enviar.
 *
 * @return Si se ha podido enviar algo, devolverá true. En caso contrario, devolverá false (llamada no bloqueante).
 */
bool CClientSocket::Send (CNetMessage& sData) {
//check if there is a socket
    if (m_Socket == NULL)
        return false;
    charbuf buf;
    int len;

//Check if the instance can send bytes, if it can, unload the number of bytes specified by NumToLoad() virtual function
    while ((len = sData.NumToUnLoad()) > 0) {
        sData.UnLoadBytes (buf);
        if (SDLNet_TCP_Send(m_Socket, (void *)buf, len) < len) {
            std::cerr << "SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
            return false;
        }
    }
    return true;
}

/**
 * @brief Función a realizar cuando el socket esté listo
 *
 * No tiene ningún uso por el momento. Función virtual.
 */
void CClientSocket::OnReady() {}
