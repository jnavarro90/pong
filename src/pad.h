#ifndef PAD_H
#define PAD_H

#include "globals.h"

//const int PAD_VELOCIDAD = PAD_ALTO / 40;
// Hacer que la velocidad sea un valor de tipo float (junto con las coordenadas X e Y).
const int PAD_VELOCIDAD = 2;

class CPad
{
  //private:
  protected:
    SDL_Rect caja;
    int yVel;
    //bool pad; // lateral derecho o izquierdo
    int momento; // 0 = no, 1 = arriba, -1 = abajo
    // SDL_Key UP, DOWN;
  public:
    CPad();
    ~CPad();

    //CPad& getPad(){return *this;};

    SDL_Rect& getCaja(){return caja;};

    int getMomento(){return momento;};

    int getVel(){return yVel;};

    //void eventuar();
    //void mover();
    //void mostrar();
};

#endif /* PAD_H */

