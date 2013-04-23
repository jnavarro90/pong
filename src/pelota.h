/**
 * @file
 * @brief Declaración de la clase abstracta CPelota y funciones relacionadas.
 */

#ifndef PELOTA_H_
#define PELOTA_H_

#include <math.h>

#include "pad.h"
#include "globals.h"
#include "entidad.h"

#include "opciones/opciones.h"

//const int OUT_RANGE = 9999; // No va a tocar el pad

const int PELOTA_ANCHO = 15;

const int OUT_RANGE = 9999; // No va a tocar el pad

//const int PELOTA_ANCHO = 20;
extern int PELOTA_VEL_MIN;

extern float VELOCIDAD_MAX;
extern float VELOCIDAD;
extern float VELOCIDAD_INC_MAX;

extern int MOMENTO_INC;

void setVel(float& yVel, float& xVel, int pos_actual, int momento);
int getPos(SDL_Rect pelota, SDL_Rect pad);

/**
 * @brief Clase abstracta para definir la pelota de cualquier modo de juego
 *
 * Funciona como clase abstracta para definir las diversas clases pertenecientes a varias estancias, por lo general,
 * una única pelota por estancia. La velocidad está definida en #COpciones::PELOTA_VEL, el tamaño en #COpciones::PELOTA_ALTO y
 * el color en #COpciones::PELOTA_COLOR
 *
 */
class CPelota: public CEntidad
{
  protected:
    Uint32 color; /**< Color de la pelota definido en #COpciones::PELOTA_COLOR*/
  public:
    CPelota();
    virtual ~CPelota();

    virtual void mostrar();
};

#endif /* PELOTA_H_ */
