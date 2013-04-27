/**
 * @file
 * @brief Sin implementar
 */

#include "opciones_flechas.h"

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

