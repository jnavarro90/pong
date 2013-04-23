/**
 * @file
 * @brief Decfinición de CPad
 *
 */

#include "pad.h"
#include "globals.h"

#include <iostream>

/**
 * @brief Constructor por defecto.
 *
 * Asigna valores por defecto (0).
 */
CPad::CPad()
{
  color = opciones->PAD_COLOR;

  caja.x = 0;
  caja.w = 0;
  caja.y = 0;
  caja.h = 0;

  //yVel = 0;
  momento = 0;
}

/**
 * @brief Destructor por defecto.
 *
 * Asigna valores por defecto (0).
 */
CPad::~CPad()
{
  momento = 0;
  caja.x = 0;
  caja.w = 0;
  caja.y = 0;
  caja.h = 0;
}

/**
 * @brief Rellena un cuadrado del tamaño y en las coordenadas de CPad::caja.
 *
 * Rellena el cuadro representado por CPad::caja con el color color blanco (0x00, 0x00, 0x00)
 * en la superficie pantalla (global).
 */
void CPad::mostrar()
{
  SDL_Rect aux = getCaja();
  SDL_FillRect(pantalla, &aux, color);
}
