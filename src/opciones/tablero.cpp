/*
 * tablero.cpp
 *
 *  Created on: 05/04/2013
 *      Author: Dani
 */

#include "tablero.h"

CTablero* tablero_mp = NULL;

CTablero::CTablero()
{
  tablero = NULL;
}

CTablero::~CTablero()
{
  SDL_FreeSurface(tablero);
}

void CTablero::construir(int16 ancho, int16 alto, int16 bpp)
{
  if(tablero != NULL)
    SDL_FreeSurface(tablero);
    // Generar fondo negro
  tablero = SDL_CreateRGBSurface(SDL_SWSURFACE, ancho, alto, bpp, 0, 0, 0, 0);

    // Construir bordes
  SDL_Rect caja;
  // Borde superior
  caja.x = PANTALLA_MARGEN_LATERAL;
  caja.y = PANTALLA_MARGEN_SUPERIOR;
  caja.w = ancho - PANTALLA_MARGEN_LATERAL*2;// + TABLERO_LINEAS_GROSOR;
  caja.h = TABLERO_LINEAS_GROSOR;
  SDL_FillRect(tablero, &caja, SDL_MapRGB(tablero->format, 0xFF, 0xFF, 0xFF));

  // Borde inferior
  caja.x = PANTALLA_MARGEN_LATERAL;
  caja.y = alto - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR;
  caja.w = ancho - PANTALLA_MARGEN_LATERAL*2;// + TABLERO_LINEAS_GROSOR;
  caja.h = TABLERO_LINEAS_GROSOR;
  SDL_FillRect(tablero, &caja, SDL_MapRGB(tablero->format, 0xFF, 0xFF, 0xFF));

  /*// Borde izquierda
  caja.x = PANTALLA_MARGEN_LATERAL;
  caja.y = PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR;
  caja.w = TABLERO_LINEAS_GROSOR;
  caja.h = alto - PANTALLA_MARGEN_SUPERIOR - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR*2;
  SDL_FillRect(tablero, &caja, SDL_MapRGB(tablero->format, 0xFF, 0x00, 0x00));

  // Borde derecha
  caja.x = ancho - PANTALLA_MARGEN_LATERAL;
  caja.y = PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR;
  caja.w = TABLERO_LINEAS_GROSOR;
  caja.h = alto - PANTALLA_MARGEN_SUPERIOR - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR*2;
  SDL_FillRect(tablero, &caja, SDL_MapRGB(tablero->format, 0xFF, 0x00, 0x00));*/

    // Lineas discontinuas del medio
  caja.h = 20;
  caja.w = TABLERO_LINEAS_GROSOR;
  caja.x = ancho/2 - TABLERO_LINEAS_GROSOR/2;
  for(int i = PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR; i <= alto - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR; i += 40)
  {
    caja.y = i;
    SDL_FillRect(tablero, &caja, SDL_MapRGB(tablero->format, 0xFF, 0xFF, 0xFF));
  }
}

void CTablero::mostrar()
{
  aplicar_superficie(0, 0, tablero, pantalla);
}


