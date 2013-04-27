/**
 * @file
 * @brief Declaración de CPad_MJ_Online, CPad_MJ_Online_Zombi, CPad_MJ_Online_Client y CPad_MJ_Online_Client_Zombi
 *
 */

#ifndef PAD_MJ_ONLINE_H_
#define PAD_MJ_ONLINE_H_

#include "../pad_mj.h"

/**
 * @brief Saber en que lado está el pad
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
 * Funciona de la misma forma que CPad_MJ_Local. Se deben extraer los datos principales (posición vertical) para enviárselos
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
 * Simplemente será un pad sin movimiento, ni teclas, ni nada por el estilo. Recibirá la entrada del cliente y
 * se moverá en función de esa entrada. Vea la función mover() y la enumeración #mov
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
 * Esta clase gestionará los datos de entrada del cliente, que deben ser enviados al servidor. No realiza movimientos
 * sobre el pad, sino que manda la entrada del teclado al servidor para saber que hacer. En esta caso, manda un valor
 * contenido en la enumeración #mov. Para calcular la posición del pad, el cliente la recibirá del servidor y la asignará
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
 * recibirá los datos del servidor y asignará los del pad del servidor a un objeto de esta clase con la
 * función setY().
 */
class CPad_MJ_Online_Client_Zombi: public CPad_MJ
{
  public:
	   CPad_MJ_Online_Client_Zombi(enum lado_t lado);

	   void setY(int y);
};

#endif /* PAD_MJ_ONLINE_H_ */
