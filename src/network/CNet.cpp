/**
 * @file
 * @brief Declaraci�n de todas las clases para la interfaz de red.
 *
 * Vea el fichero CNet.h para una mejor descripci�n.
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
 * Crea el mensaje reseteado todos los datos mediante la funci�n reset().
 */
CNetMessage::CNetMessage()
{
    reset();
}

/**
 * @brief Funci�n de reseteo
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
 * Si el mensaje est� en el estado READING, cambia su estado a FULL para determinar que est� lleno.
 */
void CNetMessage::finish() {
    if (state == READING)
        state = FULL;
}

/**
 * @brief Indicador de cuantos caracteres hay que cargar.
 *
 * @return Devuelve el n�mero de caracteres a cargar.
 *
 * En caso de que el mensaje est� vac�o (EMPTY), se ha de cargar completamente, con 255 caracteres. En caso contrario, no se puede
 * cargar ning�n car�cter (FULL).
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
 * @return Devuelve el n�mero de caracteres a descargar.
 *
 * En caso de que el mensaje est� lleno (FULL), se ha de descargar completamente, con el tama�o de la
 * cadena almacenada en buffer por medio de la funci�n strlen(). En caso contrario, no se puede
 * descargar ning�n car�cter (FULL).
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
 * @param n N�mero de bytes de inputbuffer a cargar
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
 * Posteriormente, se cambia el estado del mensaje a vac�o (EMPTY).
 */
void CNetMessage::UnLoadBytes(charbuf& destbuffer) {
    for (int i=0; i < this->NumToUnLoad(); i++)
        destbuffer[i] = buffer[i];
    reset();
}

/**
 * @brief Indicador de cuantos caracteres hay que cargar.
 *
 * @return Devuelve el n�mero de caracteres a cargar.
 *
 * En caso de que el mensaje est� vac�o (EMPTY), se ha de cargar completamente, con #buffer_size caracteres. En caso contrario, no se puede
 * cargar ning�n car�cter (FULL).
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
 * @return Devuelve el n�mero de caracteres a descargar.
 *
 * En caso de que el mensaje est� lleno (FULL), se ha de descargar completamente, con #buffer_size caracteres.
 * En caso contrario, no se puede descargar ning�n car�cter (EMPTY).
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
 * Posteriormente, se cambia el estado del mensaje a vac�o (EMPTY).
 */

void CNetMessageN::UnLoadNBytes(char* salida) // Retocar esta funci�n
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
 * @param port Puerto para intentar abrir una conexi�n.
 *
 * Intenta abrir una ruta hacia la direcci�n especificada por #m_Ip mediante el puerto especificado en los par�metros.
 * En caso de error, asigna valores a cero y registra un mensaje de error en la librer�a de SDL_net.
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
 * @param host Direcci�n del host para intentar abrir una conexi�n.
 * @param port Puerto para intentar abrir una conexi�n.
 *
 * Intenta abrir una ruta hacia la direcci�n especificada por #m_Ip mediante el puerto y el host especificado en los par�metros.
 * En caso de error, asigna valores a cero y registra un mensaje de error en la librer�a de SDL_net.
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
 * @return En caso de que todo haya funcionado correctament, devolver� true. Si algo ha fallado, devolver� false.
 *
 * Verifica que la creaci�n del objeto haya sido correcta.
 */
bool CIpAddress::Ok() const {
    return !(m_Ip.port == 0);
}

/**
 * @brief Asignador de direcci�n IP
 *
 * @param sdl_ip Direcci�n IP que se le asignar� a #m_Ip
 *
 * Cambia la direcci�n IP del objeto por la especificada en los par�metros (sdl_ip).
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
 * @return Devuelve una copia del valor de m_Ip.host como direcci�n IPv4
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
 * Asigna un valor nulo a la estructura #m_Socket y guarda memoria para el conjunto de sockets #set con un tama�o de 1.
 */
CTcpSocket::CTcpSocket() {
    m_Socket = NULL;
    set = SDLNet_AllocSocketSet(1);
}

/**
 * @brief Destructor
 *
 * Si #m_Socket no es nulo, se liberar� el espacio en memoria que ocupa la estructura.
 * Adem�s, se libera el espacio que ocupa el conjunto #set y cierra el socket m_Socket.
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
 * Si la estructura #m_Socket no es nula, liberar� el espacio que ocupa y cerrar� el puerto asignado. Acto seguido,
 * realizar� la asignaci�n de #m_Socket con el par�metro the_sdl_socket. Si algo ha fallado, SDL_net generar� un error.
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
 * @return En caso de que se haya iniciado todo correctamente, devolver� true. En caso contrario, devolver� false.
 */
bool CTcpSocket::Ok() const {
    return !(m_Socket == NULL);
}

/**
 * @brief Comprobador "Ready"
 *
 * @return Si todo est� listo y correcto para la conexi�n, devolver� true. En caso contrario, devolver� false.s
 *
 * Comprueba que todo est� correcto para la conexi�n.
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
 * @brief Funci�n a realizar cuando el socket est� listo
 *
 * No tiene ning�n uso por el momento.
 */
void CTcpSocket::OnReady() {

}

//***********************
//***** HOSTSOCKET ******
//***********************

/**
 * @brief Constructor principal
 *
 * @param the_ip_address Direcci�n ip para abrir el socket.
 *
 * Se encarga de iniciar el objeto del socket a partir de una estructura de datos CIpAddress. En caso de no poder
 * crear el socket, SDL_net generar� un error.
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
 * @param port Puerto para establecer la conexi�n.
 *
 * Se encarga de iniciar el objeto del socket a partir de un puerto dado. Se generar� una estructura de tipo
 * CIpAddress a partir del puerto. Posteriormente, se intentar� crear el socket.
 * En caso de no poder crear el socket, SDL_net generar� un error.
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
 * @return En caso de no poder aceptar ninguna conexi�n, devolver� false. Si se puede aceptar una conexi�n entrante,
 * devolver� true.
 *
 * Se intentar� entablar una conexi�n con un cliente remoto por medio de la funci�n SDLNet_TCP_Accept().
 * Si todo va bien, se entablar� la conexi�n.
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
 * @brief Funci�n a realizar cuando el socket est� listo
 *
 * No tiene ning�n uso por el momento. Funci�n virtual.
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
 * @param host Direcci�n del host como una cadena de caracteres
 * @param port Puerto para realizar la conexi�n con el host remoto.
 *
 * Primero, se crear� un objeto del tipo CIpAddress con los par�metros pasados al constructor.
 * Se intentar� conectar con el host. En caso de que haya alg�n error, se asignar� un valor nulo a #m_Socket.
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
 * @brief Intento de conexi�n
 *
 * @param the_listener_socket Socket remoto a la escucha.
 *
 * @return Devuelve siempre false.
 *
 * No tiene ning�n uso con estos par�metros de momento
 */
bool CClientSocket::Connect (CHostSocket& the_listener_socket) {
    return false;
}

/**
 * @brief Intento de conexi�n
 *
 * @param remoteip Direcci�n y puerto del host remoto
 *
 * @return Si se ha entablado la conexi�n, devolver� true. En caso contrario, devolver� false.
 *
 * Se intentar� conectar abriendo una conexi�n al host remoto. En caso de fallar, se generar� un error de SDL_net.
 * Si se genera, se crear� el socket remoto con SetSocket()
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
 * Se intentar� crear el socket. Si nada falla, se crear� el socket. Si ha fallado algo, SDL_net generar� un error.
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
 * @brief Obtener la direcci�n IP del host remoto
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
 * @return Si se ha recibido algo, devolver� true. En caso de no recibir nada, devolver� false (llamada no bloqueante).
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
 * @param sData Estructura de donde se sacar�n los datos a enviar.
 *
 * @return Si se ha podido enviar algo, devolver� true. En caso contrario, devolver� false (llamada no bloqueante).
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
 * @brief Funci�n a realizar cuando el socket est� listo
 *
 * No tiene ning�n uso por el momento. Funci�n virtual.
 */
void CClientSocket::OnReady() {}
