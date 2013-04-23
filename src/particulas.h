/**
 * @file
 * @brief Declaraci�n de CParticula
 *
 */

#ifndef CPARTICULA_H
#define CPARTICULA_H

#include "globals.h"

// Para que funcione correctamente el sistema de "trails", hacer que se dibuje 1 cada frame, y no "n" part�culas cada frame, con duracion de "m" frames.

/**
 * @brief Clase para un sistema de part�culas muy simple.
 *
 * Se utilizar� para dejar un rastro de un objeto en movimiento. No utilizado actualmente en el proyecto. El elemento que quiera usar
 * el sistema de part�culas, deber� tener un vector de CParticula y actualizar sus posiciones de forma conveniente, en funci�n del
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


