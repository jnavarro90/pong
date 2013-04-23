/**
 * @file
 * @brief Definición de la clase CTablero.
 */

#include "tablero.h"

CTablero* tablero_mp = NULL;

/**
 * @brief Constructir por defecto
 *
 * Asigna un valor nulo a la variable #tablero
 */
CTablero::CTablero()
{
  tablero = NULL;
}

/**
 * @brief Destructor por defecto
 *
 * Libera de memoria el contenido guardado en #tablero
 */
CTablero::~CTablero()
{
  SDL_FreeSurface(tablero);
}

/**
 * @brief Constructir de la imagen de fondo guardada en #pantalla
 *
 * @param ancho Ancho de la superficie. Por lo general, se usará el valor COpciones::PANTALLA_ANCHO
 * @param alto Alto de la superficie. Por lo general, se usará el valor COpciones::PANTALLA_ALTO
 * @param bpp Número bits por pixeles.
 * @param menu Dar un estilo distinto al menu. No usado actualmente.
 *
 * Crea una superficie de color negro y sobre ella dibuja una serie de lineas y formas para crear un tablero.
 * Depende enormente de las variables almacenadas en COpiones (más concretamente, COpciones::PANTALLA_ALTO,
 * COpciones::PANTALLA_ANCHO y COpciones::PANTALLA_BPP).
 *
 * En la siguiente imagen se puede apreciar como se debe construir la imagen del tablero:
 *
 * @image html tablero_1.png
 */
void CTablero::construir(int16 ancho, int16 alto, int16 bpp, bool menu)
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

  // Borde derechas
  caja.x = ancho - PANTALLA_MARGEN_LATERAL;
  caja.y = PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR;
  caja.w = TABLERO_LINEAS_GROSOR;
  caja.h = alto - PANTALLA_MARGEN_SUPERIOR - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR*2;
  SDL_FillRect(tablero, &caja, SDL_MapRGB(tablero->format, 0xFF, 0x00, 0x00));*/

  if(menu) // Si estamos dibujando un menu, ignoramos las lineas discontinuas del medio
    return; // ¿O TAL VEZ NO?

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

/**
 * @brief Muestra el tablero por pantalla
 *
 * Combina la superficie #tablero en la superficie #pantalla
 */
void CTablero::mostrar()
{
  aplicar_superficie(0, 0, tablero, pantalla);
}


