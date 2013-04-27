/**
 * @file
 * @brief Definici�n de CMarcador_Online
 *
 */

#include "marcador_online.h"

/**
 * @brief Constructor principal
 *
 * @param f Fuente de entrada peviamente cargada con la que se generar� los textos por #pantalla
 * @param c Color de entrada con el que se generar�n los textos por #pantalla
 *
 * Inicialmente, carga las im�genes con los valores iniciales (0,0).
 */
CMarcador_Online::CMarcador_Online(TTF_Font* f, SDL_Color* c)
{
  marca1 = marca2 = 0;

  ttf_fuente = f;
  color = c;

  stringstream ss;

  ss << marca1;
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  ss.str("");
  ss.clear();

  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;
  MARCADOR_OFFSET_J2 = opciones->PANTALLA_ANCHO/2 + MARCADOR_OFFSET;

  ss << marca2;
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}

/**
 * @brief Destructor
 *
 * Librera las superficies #srf_marca1 y #srf_marca2 y asigna valores nulos a los miembros.
 */
CMarcador_Online::~CMarcador_Online()
{
  SDL_FreeSurface(srf_marca1);
  SDL_FreeSurface(srf_marca2);

  marca1 = 0;
  marca2 = 0;

  color = NULL;

  srf_marca1 = NULL;
  srf_marca2 = NULL;

  ttf_fuente = NULL;
}

/**
 * @brief Asignar un valor al marcador del jugador 1 (izquierdo)
 *
 * @param n Valor a asignar a #marca1
 *
 * Se asignar� el valor pasado como par�metro a #marca1 y se generar� la superficie
 * generada con el texto en #srf_marca1. Como la alineaci�n es hacia la derecha,
 * en funci�n del ancho, se recalcular� el offset del texto.
 */
void CMarcador_Online::setM1(int n)
{
  marca1 = n;

  stringstream ss;

  ss << marca1;
  SDL_FreeSurface(srf_marca1); // liberamos para evitar lagunas de memoria
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;
}

/**
 * @brief Asignar un valor al marcador del jugador 2 (derecha)
 *
 * @param n Valor a asignar a #marca2
 *
 * Se asignar� el valor pasado como par�metro a #marca2 y se generar� la superficie
 * generada con el texto en #srf_marca2. Como la alineaci�n es a la izquierda, no debe usarse offset.
 */
void CMarcador_Online::setM2(int n)
{
  marca2 = n;

  stringstream ss;

  ss << marca2;
  SDL_FreeSurface(srf_marca2);
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}
