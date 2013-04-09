/*
 * tablero.h
 *
 *  Created on: 05/04/2013
 *      Author: Dani
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "../globals.h"

class CTablero
{
  private:
    SDL_Surface* tablero;
  public:
    CTablero();
    ~CTablero();

    void construir(int16 ancho, int16 alto, int16 bpp);
    void mostrar();
};

extern CTablero* tablero_mp;


#endif /* TABLERO_H_ */
