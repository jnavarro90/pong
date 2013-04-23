/**
 * @file
 * @brief Definici�n de la clase CBoton
 */

#include "boton.h"

/**
 * @brief Constructor principal
 *
 * @param f Puntero a fuente previamente cargada para generar el texto en #ttf_fuente
 * @param c1 Color del texto cuando el rat�n est� encima del texto en #color1
 * @param c2 Color del texto cuando el rat�n no est� encima del texto en #color2
 * @param cuadro Tama�o y posici�n del marco del bot�n en #caja
 * @param t Texto a mostrar en el bot�n en #texto
 * @param algn Alineaci�n del texto en #align
 *
 * Se deber�n hacer todas las asignaciones de los par�metros a los miembros de la clase.
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
 * Calcula el offset del texto con respecto al marco del bot�n en funci�n de la alineaci�n. Posteriormente, comprueba
 * si el rat�n est� encima del bot�n con la funci�n encima(). Si est� encima, dibuja el texto con el #color1. Si no,
 * lo dibuja con el color #color2. Finalmente, combina el texto generado en #srf_texto con la superficie
 * #pantalla y liber� el contenido de #srf_texto.
 */
void CBoton::mostrar()
{
  // Calcular la posici�n relativa en la que ir� el texto
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
 * @brief Comprueba si el rat�n est� encima del marco del bot�n
 *
 * @return Devuelve true si est� encima. Si no, devuelve false.
 *
 * La funci�n obtiene los datos de la posici�n del rat�n a partir de la estructura global #event.
 */
bool CBoton::encima()
{
  int x, y;
  // Buscamos la posicion del rat�n (x,y)
  x = event.motion.x;
  y = event.motion.y;

  // Y comprobamos si est� en el rango del bot�n
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



