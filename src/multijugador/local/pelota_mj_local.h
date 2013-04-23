#include "../../pelota.h"
#include "../pelota_mj.h"

#include "../../opciones/opciones.h"

#include <math.h>

#ifndef PELOTA_MJ_LOCAL_H_
#define PELOTA_MJ_LOCAL_H_

enum gamepoint_pj_t {gamepoint_pj1 = 0, gamepoint_pj2};

/*const int OUT_RANGE = 9999; // No va a tocar el pad

//const int PELOTA_ANCHO = 20;
const int PELOTA_VEL_MIN = 3;

const float VELOCIDAD_MAX = 4.5;
const float VELOCIDAD = 5;
const float VELOCIDAD_INC_MAX = 2.0;

const int MOMENTO_INC = 10;*/

//void setVel(float& yVel, float& xVel, int pos_actual, int momento);
//int getPos(SDL_Rect pelota, SDL_Rect pad);

// Más que una pelota, un cuadrado
class CPelota_MJ_Local : public CPelota_MJ
{
  protected:
    float xVel, yVel;
  public:
    CPelota_MJ_Local();
    ~CPelota_MJ_Local();

    void empezar(enum gamepoint_pj_t gamepoint_pj);

    bool getLock(){return lock;}
    bool getStop(){return stop;}

    int mover(CPad& A, CPad& B);
};

#endif /* PELOTA_H_ */
