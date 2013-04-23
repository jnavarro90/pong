/** @file
 * @brief Definición de la clase CWarning
 *
 */

#include "warning.h"
#include "opciones/opciones.h"


/**
 * @brief Constructor principal
 *
 * @param fuente Fuente para generar el texto en  la superficie #srf_texto
 * @param txt Texto a generar para mostrar como aviso.
 * @param color Color del texto a generar
 *
 * Asigna los valores pasados como parámetros y llama a la función SDL_EnableUNICODE()
 */
CWarning::CWarning(TTF_Font* fuente, const char* txt, SDL_Color* color)
{
  ttf_fuente = fuente;
  str = txt;

  color1.r = color->r;
  color1.g = color->g;
  color1.b = color->b;
  srf_texto = TTF_RenderText_Solid(ttf_fuente, str.c_str(), color1);
}

/**
 * @brief Destructor
 *
 * Desinicializa valores y libera la memoria almacenada por la superficie #srf_texto
 */
CWarning::~CWarning()
{
  SDL_FreeSurface(srf_texto);
  srf_texto = NULL;

  str="";
  ttf_fuente = NULL;

  color1.r = color1.g = color1.b = 0;
}

/**
 * @brief Mostrar por pantalla de forma centrada
 *
 * Muestra en la superficie #pantalla la superficie #srf_texto de forma que el texto quede justo en el centro.
 */
void CWarning::mostrar()
{
  aplicar_superficie(opciones->PANTALLA_ANCHO/2 - srf_texto->w/2, opciones->PANTALLA_ALTO/2 - srf_texto->h/2, srf_texto, pantalla);
}

/**
 * @brief Mostrar por pantalla sin centrar
 *
 * @param x,y Coordenadas relativas para combinar #srf_texto con #pantalla
 *
 * Muestra en la superficie #pantalla la superficie #srf_texto en las coordenadas x,y
 */
void CWarning::mostrar(int x, int y)
{
  aplicar_superficie(x, y, srf_texto, pantalla);
}

/**
 * @brief Mostrar por pantalla con centrado horizontal
 *
 * @param y Coordenada relativa para combinar #srf_texto con #pantalla
 *
 * Muestra en la superficie #pantalla la superficie #srf_texto centrado horizontalmente, en el eje Y con el valor y
 */
void CWarning::mostrar_ch(int y)
{
  aplicar_superficie(opciones->PANTALLA_ANCHO/2 - srf_texto->w/2, y, srf_texto, pantalla);
}

/**
 * @brief Mostrar por pantalla con centrado vertical
 *
 * @param x Coordenada relativa para combinar #srf_texto con #pantalla
 *
 * Muestra en la superficie #pantalla la superficie #srf_texto centrado verticalmente, en el eje X con el valor x
 */
void CWarning::mostrar_cv(int x)
{
  aplicar_superficie(x, opciones->PANTALLA_ALTO/2 - srf_texto->h/2, srf_texto, pantalla);
}
