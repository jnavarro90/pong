/*
 * opciones_flechas.h
 *
 *  Created on: 11/04/2013
 *      Author: Dani
 */

#ifndef OPCIONES_FLECHAS_H_
#define OPCIONES_FLECHAS_H_

#include "../globals.h"

class COpciones_Flechas
{
  private:
    SDL_Surface* fondo;
    SDL_Surface* texto;
    TTF_Font* fuente;

    int val_min;
    int val_max;

    int& val_actual;
  public:
    COpciones_Flechas(TTF_Font* fuente, int val_min, int val_max, int& val_actual);
    ~COpciones_Flechas();

    void eventuar();
    void mostrar();
};


#endif /* OPCIONES_FLECHAS_H_ */
