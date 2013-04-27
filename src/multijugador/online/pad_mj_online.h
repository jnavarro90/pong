/**
 * @file
 * @brief Declaraci�n de CPad_MJ_Online, CPad_MJ_Online_Zombi, CPad_MJ_Online_Client y CPad_MJ_Online_Client_Zombi
 *
 */

#ifndef PAD_MJ_ONLINE_H_
#define PAD_MJ_ONLINE_H_

#include "../pad_mj.h"

/**
 * @brief Saber en que lado est� el pad
 */
enum lado_t
{
  izq = 0 /**< Lado izquierdo*/
  ,der /**< Lado derecho*/
};

/**
 * @brief Saber el movimiento de un pad
 */
enum mov
{
  abajo = -1 /**< Movimiento hacia abajo*/
  ,quieto = 0 /**< Sin movimiento*/
  ,arriba = 1 /**< Movimiento hacia arriba*/
};

/**
 * @brief Clase para representar el pad del servidor en el modo multijugador-online en la estancia del servidor
 *
 * Funciona de la misma forma que CPad_MJ_Local. Se deben extraer los datos principales (posici�n vertical) para envi�rselos
 * al cliente.
 */
class CPad_MJ_Online: public CPad_MJ
{
  protected:
	   SDLKey KUp, KDown;
  public:
   	CPad_MJ_Online(enum lado_t lado, SDLKey U, SDLKey D);
   	~CPad_MJ_Online();

    void eventuar();
    void mover();
};

/**
 * @brief Clase para representar el pad del cliente en el modo multijugador-online en la estancia del servidor
 *
 * Simplemente ser� un pad sin movimiento, ni teclas, ni nada por el estilo. Recibir� la entrada del cliente y
 * se mover� en funci�n de esa entrada. Vea la funci�n mover() y la enumeraci�n #mov
 */
class CPad_MJ_Online_Zombi: public CPad_MJ
{
  // Casi mejor trabajar con una funcion eventuar o algo...
  public:
   	CPad_MJ_Online_Zombi(enum lado_t lado);
   	~CPad_MJ_Online_Zombi();

    //void setY(int y);
    void mover(int8 mov);
};

/**
 * @brief Clase para representar el pad del servidor en el modo multijugador-online en la estancia del cliente
 *
 * Esta clase gestionar� los datos de entrada del cliente, que deben ser enviados al servidor. No realiza movimientos
 * sobre el pad, sino que manda la entrada del teclado al servidor para saber que hacer. En esta caso, manda un valor
 * contenido en la enumeraci�n #mov. Para calcular la posici�n del pad, el cliente la recibir� del servidor y la asignar�
 * con setY().
 */
// En estas clases sobran los miembros yVel y momento derivados de clases superires. Arreglar esta chapuza.
class CPad_MJ_Online_Client: public CPad_MJ
{
  protected:
	   SDLKey KUp, KDown;
  public:
	   CPad_MJ_Online_Client(enum lado_t lado, SDLKey U, SDLKey D);

	 void eventuar(int8& mov);
	 void setY(int y);
};

/**
 * @brief Clase para representar el pad del cliente en el modo multijugador-online en la estancia del cliente
 *
 * Esta clase no gestiona los datos de entrada, pues representa un pad remoto. Simplemente, el cliente
 * recibir� los datos del servidor y asignar� los del pad del servidor a un objeto de esta clase con la
 * funci�n setY().
 */
class CPad_MJ_Online_Client_Zombi: public CPad_MJ
{
  public:
	   CPad_MJ_Online_Client_Zombi(enum lado_t lado);

	   void setY(int y);
};

#endif /* PAD_MJ_ONLINE_H_ */
