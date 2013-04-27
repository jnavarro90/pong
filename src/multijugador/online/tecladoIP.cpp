/**
 * @file
 * @brief Definición de la clase CTecladoIP
 */

#include "tecladoIP.h"

CTecladoIP::CTecladoIP(const char* fuente, uint tam, SDL_Color* color, int ax, int ay, uint l):CTeclado(fuente, tam, color, ax, ay, l)
{

}

/**
 * @brief Gestionar evventos de entrada
 *
 * Saca los datos de entrada del teclado desde la estructura #event y sólo acepta y guarda en #str los números y los puntos '.'.
 * El tamaño máximo especificado de la cadena está puesto por #length.
 */
void CTecladoIP::eventuar()
{
  if(event.type == SDL_KEYDOWN)
  {
    string temp = str;

    if(str.length() <= length)
    {
      // Si es un punto
      if(event.key.keysym.unicode == (Uint16)'.')
      {
        str += (char)event.key.keysym.unicode;
      }
      // Si es un numero
      else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
      {
        str += (char)event.key.keysym.unicode;
      }
    }
    // Si queremos borrar y la cadena no es vacia
    if((event.key.keysym.sym == SDLK_BACKSPACE) && (str.length() != 0 ))
    {
      // Borrar el ultimo caracter
      str.erase( str.length() - 1 );
    }
    if(str != temp)
    {
      SDL_FreeSurface(img_texto);

      img_texto = TTF_RenderText_Solid(ttf_fuente, str.c_str(), color_texto);
    }
  }
}
