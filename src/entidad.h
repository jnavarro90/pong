/*
 * entidad.h
 *
 *  Created on: 05/04/2013
 *      Author: Dani
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include "globals.h"

class CEntidad
{
  protected:
    Rect_Float caja; /**< Ancho, alto, posición x, posición y */
  public:
    /**
     * @brief Devuelve una struct del tipo SDL_Rect con la altura, el ancho y las coordenadas
     *
     * Se encarga de transformar la struct de tipo Rect_Float en SDL_Rect.
     *
     * @return Atributo caja transformado al tipo SDL_Rect.
     */
    SDL_Rect getCaja()
    {
      SDL_Rect aux;
      aux.x = (int)caja.x;
      aux.y = (int)caja.y;
      aux.w = caja.w;
      aux.h = caja.h;

      return aux;
    }
};



#endif /* ENTIDAD_H_ */
