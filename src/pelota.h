//#include "globals.h"

#ifndef PELOTA_H_
#define PELOTA_H_

#include "pad.h"
#include "globals.h"
#include <math.h>

//const int OUT_RANGE = 9999; // No va a tocar el pad

const int PELOTA_ANCHO = 15;
//const int PELOTA_VEL_MIN = 3;

//const float VELOCIDAD_MAX = 4.5;
//const float VELOCIDAD = 5;
//const float VELOCIDAD_INC_MAX = 2.0;

//const int MOMENTO_INC = 10;

// Más que una pelota, un cuadrado
class CPelota
{
  protected:
    Rect_Float caja;
    float xVel, yVel;
  public:
    CPelota();
    ~CPelota();

    SDL_Rect getCaja();
};

#endif /* PELOTA_H_ */
