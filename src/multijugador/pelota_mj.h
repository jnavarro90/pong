/**
 * @file
 * @brief Declaración de CPelota_MJ
 *
 */

#ifndef PELOTA_MJ_H_
#define PELOTA_MJ_H_

#include "../pelota.h"

/**
 * @brief Clase abstracta para clases CPelota a nivel de multijugador
 *
 * Se usará simplemente como clase base para generar clases de multijugador que comparten la velocidad vertical y horizontal,
 * además de otros miembros.
 */
class CPelota_MJ: public CPelota
{
  protected:
	   bool stop; /**< ¿La pelota está parada? */
	   bool lock; /**< ¿La pelota está bloqueada? */
	   float xVel; /**< Velocidad horizontal */
	   float yVel; /**< Velocidad vertical */
  public:
	   /** @brief Constructor por defecto */
	   CPelota_MJ(): stop(false), lock(false) {};
	   /** @brief Destructor */
	   virtual ~CPelota_MJ() {};

	   /**
	    * @brief Mover la pelota
	    * @param PJ1 CPad del jugador 1
	    * @param PJ2 CPad del jugador 2
	    *
	    * @return Devuelve un identificador para saber que realizar.
	    *
	    * Se debe comprobar si el objeto rebota contra las paredes superiores o contra los pads.
	    * Además, en función del ángulo de rebote se deben recalcular las velocidades de la pelota por medio
	    * de la función getVel(). Vea la definición del método para entender su funcionamiento.
	    */
    virtual int mover(CPad PJ1, CPad PJ2);
};

#endif /* PELOTA_MJ_H_ */
