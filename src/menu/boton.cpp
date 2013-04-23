/**
 * @file
 * @brief Definición de la clase CBoton
 */

#include "boton.h"

/**
 * @brief Constructor principal
 *
 * @param f Puntero a fuente previamente cargada para generar el texto en #ttf_fuente
 * @param c1 Color del texto cuando el ratón esté encima del texto en #color1
 * @param c2 Color del texto cuando el ratón no esté encima del texto en #color2
 * @param cuadro Tamaño y posición del marco del botón en #caja
 * @param t Texto a mostrar en el botón en #texto
 * @param algn Alineación del texto en #align
 *
 * Se deberán hacer todas las asignaciones de los parámetros a los miembros de la clase.
 */
CBoton::CBoton(TTF_Font* f, SDL_Color* c1, SDL_Color* c2, SDL_Rect* cuadro, const char* t, enum align_t algn)
{
  ttf_fuente = f;

  color1 = c1;
  color2 = c2;

  caja.x = cuadro->x;
  caja.y = cuadro->y;
  caja.w = cuadro->w;
  caja.h = cuadro->h;

  texto = t;

  align = algn;
}

/**
 * @brief Destructor
 *
 * Asigna valores a 0 y NULL
 */
CBoton::~CBoton()
{
  ttf_fuente = 0;

  color1 = color2 = NULL;

  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;

  texto = "";
}

/**
 * @brief Mostrar por pantalla
 *
 * Calcula el offset del texto con respecto al marco del botón en función de la alineación. Posteriormente, comprueba
 * si el ratón está encima del botón con la función encima(). Si está encima, dibuja el texto con el #color1. Si no,
 * lo dibuja con el color #color2. Finalmente, combina el texto generado en #srf_texto con la superficie
 * #pantalla y liberá el contenido de #srf_texto.
 */
void CBoton::mostrar()
{
  // Calcular la posición relativa en la que irá el texto
  int offx = 0;
  int offy = 5;
  switch(align)
  {
    case align_izquierda:
      offx = 5;
    break;
    case align_centro:
      offx = (caja.w - srf_texto->w)/2;
    break;
    case align_derecha:
      offx = caja.w - srf_texto->w - 5;
    break;
  }

  if(encima())
  {
    offx += 10;
    //srf_texto = TTF_RenderText_Solid(ttf_fuente, texto.c_str(), *color1);
    srf_texto = TTF_RenderText_Blended(ttf_fuente, texto.c_str(), *color1);
    Uint32 color_back = SDL_MapRGB(pantalla->format, color2->r, color2->g, color2->b);
	   SDL_FillRect(pantalla, &caja, color_back);
  }
  else
  {
    //srf_texto = TTF_RenderText_Solid(ttf_fuente, texto.c_str(), *color2);
    srf_texto = TTF_RenderText_Blended(ttf_fuente, texto.c_str(), *color2);
  }

  // Renderizar el texto en una superficie
  //ttf_txt_menu = TTF_RenderText_Solid(ttf_consolas, texto.c_str(), ttf_color_txt_menu);
  //srf_texto = TTF_RenderText_Solid(ttf_consolas, texto.c_str(), ttf_color_txt_menu);


  // Aplicar la superficie y liberar para usar en los otros botones
  aplicar_superficie(caja.x + offx, caja.y + offy, srf_texto, pantalla);
  SDL_FreeSurface(srf_texto);

}

/**
 * @brief Comprueba si el ratón está encima del marco del botón
 *
 * @return Devuelve true si está encima. Si no, devuelve false.
 *
 * La función obtiene los datos de la posición del ratón a partir de la estructura global #event.
 */
bool CBoton::encima()
{
  int x, y;
  // Buscamos la posicion del ratón (x,y)
  x = event.motion.x;
  y = event.motion.y;

  // Y comprobamos si está en el rango del botón
  if( (x > caja.x ) && (x < caja.x + caja.w ) && ( y > caja.y ) && (y < caja.y + caja.h ))
  {
    return true;
  }
  return false;
}

void cambiarNegro(SDL_Color* color)
{
  color->r = color->g = color->b = 0;
}

void cambiarBlanco(SDL_Color* color)
{
  color->r = color->g = color->b = 255;
}



