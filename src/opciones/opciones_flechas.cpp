/*
 * opciones_flechas.cpp
 *
 *  Created on: 11/04/2013
 *      Author: Dani
 */

#include "opciones_flechas.h"

/*class COpciones_Flechas
{
  private:
    SDL_Surface* fondo;
    SDL_Surface* texto;

    int val_min;
    int val_max;

    int& val_actual;
  public:
    COpciones_Flechas(int val_min, int val_max, int& val_actual);
    ~COpciones_Flechas();

    void eventuar();
    void mostrar();
};*/

COpciones_Flechas::COpciones_Flechas(TTF_Font* f, int v_min, int v_max, int& v_actual):
   fuente(f), val_min(v_min), val_max(v_max), val_actual(v_actual)
{
  fondo = NULL;
  texto = NULL;
}

COpciones_Flechas::~COpciones_Flechas()
{
  SDL_FreeSurface(fondo);
  SDL_FreeSurface(texto);
}

