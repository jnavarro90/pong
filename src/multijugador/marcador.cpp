/**
 * @file
 * @brief Definición de CMarcador
 *
 */

#include "marcador.h"

const int MARCADOR_OFFSET = 20;
const int MARCADOR_Y = 20;
const int MARCADOR_OFFSET_FIX = 16;
int MARCADOR_OFFSET_J1;
int MARCADOR_OFFSET_J2;

/**
 * @brief Constructor por defecto
 *
 * @param f Fuente previamente cargada para generar el texto.
 * @param c Color con el que se cargará el texto generado.
 *
 * El constructor ajusta offsets y asigna valores iniciales a los miembros de la clase. Vea la definición del método.
 */
CMarcador::CMarcador(TTF_Font* f, SDL_Color* c)
{
  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - TEXTO_MARCADOR_ANCHO/2;
  MARCADOR_OFFSET_J2 = opciones->PANTALLA_ANCHO/2 + MARCADOR_OFFSET;

  marca1 = 0;
  marca2 = 0;

  color = c;

  srf_marca1 = NULL;
  srf_marca2 = NULL;

  ttf_fuente = f;

  stringstream ss;

  ss << marca1;
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  ss.str("");
  ss.clear();

  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;

  ss << marca2;
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}

/**
 * @brief Destructor
 *
 * Libera memoria ocupada por algunas superficies y asigna valores nulos a algunas variables.
 */
CMarcador::~CMarcador()
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
 * @brief Resetear puntuaciones
 *
 * Resetea los marcadores y redibuja los textos.
 */
void CMarcador::reset()
{
  marca1 = 0;
  marca2 = 0;

  srf_marca1 = NULL;
  srf_marca2 = NULL;

  ttf_fuente = NULL;
  color = NULL;
}

/**
 * @brief Mostrar por #pantalla
 *
 * Muestra #srf_marca1 y #srf_marca2 por #pantalla.
 */
void CMarcador::mostrar()
{
  aplicar_superficie(MARCADOR_OFFSET_J1, MARCADOR_Y, srf_marca1, pantalla);
  aplicar_superficie(MARCADOR_OFFSET_J2, MARCADOR_Y, srf_marca2, pantalla);
}

/**
 * @brief Incrementar marcador del jugador 1
 *
 * Incrementa el valor de #marca1 y redibuja la superficie #srf_marca1
 */
void CMarcador::incM1()
{
  marca1++;

  stringstream ss;

  ss << marca1;
  SDL_FreeSurface(srf_marca1);
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;
}

/**
 * @brief Incrementar marcador del jugador 2
 *
 * Incrementa el valor de #marca2 y redibuja la superficie #srf_marca2
 */
void CMarcador::incM2()
{
  marca2++;

  stringstream ss;

  ss << marca2;
  SDL_FreeSurface(srf_marca2);
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}



