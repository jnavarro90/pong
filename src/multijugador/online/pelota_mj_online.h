/**
 * @file
 * @brief Declaración de CPelota_MJ_Online y CPelota_MJ_Online_Client
 *
 */

#ifndef PELOTA_MJ_ONLINE_H_
#define PELOTA_MJ_ONLINE_H_

#include "pad_mj_online.h"
#include "network_struct.h"

#include "../pelota_mj.h"

#include "../../opciones/opciones.h"

/**
 * @brief Clase para representar la pelota del modo de juego multijugador-online desde el servidor.
 *
 * Los objetos de esta clase funcionan de forma parecida a los de la clase CPelota_MJ_Local, salvo que en esta,
 * al mover la pelota, si se debe reproducir algún sonido, se deberá notificar al usuario enviándole una notificación.
 * Véase CNetwork_Data_Server::fs
 */
class CPelota_MJ_Online: public CPelota_MJ
{
  public:
    CPelota_MJ_Online();

	   void empezar();
	   int mover(CPad& PJ1, CPad& PJ2, flags& f);
};

/**
 * @brief Clase para representar la pelota del modo de juego multijugador-online desde el cliente.
 *
 * Esta pelota es como si fuese un "zombi". En cada iteración del bucle principal del cliente deberá recibir la estructura
 * de datos del tipo CNetwork_Data_Server y copiar los datos necesarios en esta clase (en esta caso, se deben copiar
 * CNetwork_Data_Server::pelota_x y CNetwork_Data_Server::pelota_y
 */
class CPelota_MJ_Online_Client: public CPelota
{
  public:
    /** @brief Constructor vacío */
    CPelota_MJ_Online_Client(): CPelota(){};

    /** @brief Cambiar la posición de la pelota
     *  @param x,y Nuevas coordenadas de la pelota aplicadas a la estructura #caja
     *
     */
    void setXY(int x, int y);
};


#endif /* PELOTA_MJ_ONLINE_H_ */
