/**
 * @file
 * @brief Definici�n de la clase abstracta CPelota y funciones relacionadas.
 */

#include "pelota.h"
#include <iostream>

int PELOTA_VEL_MIN = 3;

float VELOCIDAD_MAX = 4.5;
float VELOCIDAD = 5;
float VELOCIDAD_INC_MAX = 2.0;

int MOMENTO_INC = 10;

using namespace std;

/**
 * @brief Constructor por defecto
 *
 * Asigna los valores del objeto #opciones estanciado desde la clase COpciones. Inicialmente, coloca la pelota en la posici�n (0,0).
 *
 */

CPelota::CPelota()
{
  color = opciones->PELOTA_COLOR;
  caja.x = 0;
  caja.y = 0;
  caja.w = opciones->PELOTA_ANCHO;
  caja.h = opciones->PELOTA_ANCHO;
}

/** Destructor
 *
 * Asigna el valor 0 a todos los miembros.
 *
 */

CPelota::~CPelota()
{
  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;
}

/**
 * @brief Mostrar por pantalla
 *
 * Colorea en la superficie #pantalla un cuadrado con las dimensiones y la ubicaci�n especificada en #caja
 *
 */

void CPelota::mostrar()
{
  SDL_Rect aux = getCaja();
  SDL_FillRect(pantalla, &aux, color);
}

/**
 * @brief Calcular velocidad posterior al rebote
 *
 * @param yVel,xVel Referencia a las velocidades de la pelota a modificar.
 * @param pos_actual Posici�n actual de la pelota devuelto por getPos().
 * @param momento Especifica si hay momento cin�tico en el pad. momento = {0 (no), 1 (arriba), -1 (abajo) }.
 *
 * Una vez que la pelota rebota contra un pad, se deben calcular la velocidad vertical y horizontal de la pelota. Para ello, se
 * usa esta funci�n. Primero, se obtiene la posici�n relativa de la pelota frente al pad, en el rango [- PAD_ALTO/2, PAD_ALTO/2].
*  Se tiene en cuenta si el pad tiene momento cin�tico (se mueve o no). El momento a�ade una cierta distancia a la posicion actual.
*  Se puede apreciar en el siguiente diagrama como se calculas las velocidades
*
*  \verbatim
  ___  _ _ _ A�adir m�xima velocidad incremental al rebotar
 |   |
 |   | _ _ _ A�adir una cierta velocidad al rebotar
 |___| _ _ _ No a�adir velocidad al rebote
 |   |
 |   |
 |___| _ _ _ A�adir m�xima velocidad (-) incremental al rebotar

 \endverbatim

* En la siguiente imagen se puede ver c�mo se realizan los cambios de velocidad de una forma sencilla:
*
* @image html pelota_1.png
*/

void setVel(float& yVel, float& xVel, int pos_actual, int momento) //
{
 if(momento > 0) // momento == 1 (abajo)
 {
   pos_actual += MOMENTO_INC;
 }
 if(momento < 0) // momento == -1 (abajo)
 {
   pos_actual -= MOMENTO_INC;
 }

 float equivVel = -pos_actual*VELOCIDAD_INC_MAX/opciones->PAD_ALTO/2;

 yVel = yVel + equivVel;

 if(yVel > VELOCIDAD_MAX)
 {
   yVel = VELOCIDAD_MAX;
 }
 else if(yVel < -VELOCIDAD_MAX)
 {
   yVel = -VELOCIDAD_MAX;
 }

 float vel = sqrt(opciones->PELOTA_VEL*opciones->PELOTA_VEL - yVel*yVel);

 if(xVel > 0)
 {
   xVel = -vel;
 }
 else
 {
   xVel = vel;
 }
}

/** @brief Devuelve la posici�n relativa
 *
 * @param pelota Posici�n actual de la pelota (x,y). Se ignoran SDL_Rect.w y SDL_Rect.h.
 * @param pad Posici�n actual del pad (x,y). Se ignoran SDL_Rect.w y SDL_Rect.h.
 *
 * @return Devuelve la posici�n relativa de la pelota frente al pad. La funci�n devolvera un valor entre [- PAD_ALTO/2, PAD_ALTO/2]
 * en caso de estar a rango. En caso contrario, devolver� #OUT_RANGE.
 *
 * La funci�n computa la posici�n relativa del pad con respecto a la pelota.
 * \verbatim
         NO RANGO
 MAX ___  _ _ _ _ _
    |   |
    |   |
  0 |___| EN RANGO
    |   |
    |   |
    |___| _ _ _ _ _
 MIN
       NO RANGO
 \endverbatim
*/

int getPos(SDL_Rect pelota, SDL_Rect pad)
{
 // Esta comprobaci�n se realiza cuando la pelota "atraviesa" por una esquina el pad, antes de reajustas posiciones.
 // Si no esta en el rango del pad, devuelve un valor "nulo"
 if(pelota.y +  pelota.h <= pad.y || pelota.y >= pad.y + pad.h)
   return OUT_RANGE;
 // Si entra en el rango del PAD, devolvemos la posici�n relativa.
 else if(pelota.y + pelota.h > pad.y && pelota.y < pad.y + pad.h)
   return (int)(pad.y + pad.h/2 - (pelota.y + pelota.h/2 ));
 return 0;
}

