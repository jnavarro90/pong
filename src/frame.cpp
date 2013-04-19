/**
 * @file
 * @brief Define la clase CFrame
 */

#include "frame.h"

/**
 * @brief Constructor por defecto
 *
 * @param width Ancho del marco.
 * @param heigth Alto del marco.
 * @param grosor Grosor del marco.
 * @param color_marco Color del marco.
 * @param color_fondo Color de fondo. Fondo transparente no implementado.
 *
 * Genera una superficie con un marco en función de los parámetros facilitados al constructor. Guarda la superficie generada en #srf_frame.
 * El marco es de la siguiente forma:
 * \verbatim
  =============
  |           |
  |           |
  =============
  \endverbatim
 */

CFrame::CFrame(int width, int heigth, int grosor, Uint32 color_marco, Uint32 color_fondo)
{
  srf_frame = SDL_CreateRGBSurface(SDL_SWSURFACE, width, heigth, 32, 0, 0, 0, 0);

  SDL_Rect aux = {0, 0, width, heigth};
  SDL_FillRect(srf_frame, &aux, color_fondo);

  // Dibujar bordes del marco
    // Borde superior
  aux.x = 0;
  aux.y = 0;
  aux.w = width;
  aux.h = grosor;
  SDL_FillRect(srf_frame, &aux, color_marco);
    // Borde inferior
  aux.x = 0;
  aux.y = heigth - grosor;
  aux.w = width;
  aux.h = grosor;
  SDL_FillRect(srf_frame, &aux, color_marco);
    // Borde izquierdo
  aux.x = 0;
  aux.y = 0 + grosor;
  aux.w = grosor;
  aux.h = heigth - grosor;
  SDL_FillRect(srf_frame, &aux, color_marco);
    // Borde derecho
  aux.x = 0 + width - grosor;
  aux.y = 0 + grosor;
  aux.w = grosor;
  aux.h = heigth - grosor;
  SDL_FillRect(srf_frame, &aux, color_marco);
}

/**
 * @brief Destructor
 *
 * Libera la superficie generada por el constructor, ubicada en #srf_frame.
 */

CFrame::~CFrame()
{
  SDL_FreeSurface(srf_frame);
}

/**
 * @brief Combina #srf_frame con salida
 *
 * @param x,y Coordenadas relativas a la superficie de salida.
 * @param salida Superficie donde se colocará #srf_frame.
 *
 * Combina #srf_frame con una superficie de salida, por si queremos generar una superficie estática.
 */

void CFrame::combinar(int x, int y, SDL_Surface* salida)
{
  aplicar_superficie(x, y, srf_frame, salida);
}

/**
 * @brief Muestra por pantalla
 *
 * @param x,y Coordenadas relativas a la superficie #pantalla.
 *
 * Muestra el contenido de #srf_frame por #pantalla (combinándolo con #pantalla).
 */

void CFrame::mostrar(int x, int y)
{
  aplicar_superficie(x, y, srf_frame, pantalla);
}
