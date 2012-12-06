#include "globals.h"

#ifndef CPARTICULA_H
#define CPARTICULA_H

// Para que funcione correctamente el sistema de "trails", hacer que se dibuje 1 cada frame, y no "n" part�culas cada frame, con duracion de "m" frames.

/**
 * @brief Clase para un sistema de part�culas muy simple.
 *
 */

class CParticula
{
  private:
    int x,y;
    int frame;
    SDL_Surface* tipo;
    SDL_Rect* trailclip;
  public:
    CParticula(int, int);

    void mostrar();
    bool muerta();
};

#endif


