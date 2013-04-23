/**
 * @file
 * @brief Declaración de CParticula
 *
 */

#ifndef CPARTICULA_H
#define CPARTICULA_H

#include "globals.h"

// Para que funcione correctamente el sistema de "trails", hacer que se dibuje 1 cada frame, y no "n" partículas cada frame, con duracion de "m" frames.

/**
 * @brief Clase para un sistema de partículas muy simple.
 *
 * Se utilizará para dejar un rastro de un objeto en movimiento. No utilizado actualmente en el proyecto. El elemento que quiera usar
 * el sistema de partículas, deberá tener un vector de CParticula y actualizar sus posiciones de forma conveniente, en función del
 * movimiento deseado.
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


