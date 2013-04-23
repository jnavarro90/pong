/**
 * @file
 * @brief Declaración y definición de CEntidad
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_

#include "globals.h"

/**
 * @brief Clase principal de objeto del juego.
 *
 * Esta clase abstracta se usará para derivar otras clases con caracterísitcas comunes (alto, ancho, pos. x, pos. y ).
 * Se emplea en las clases CPad y CPelota. Para entender el sistema de coordenadas, se debe tener en cuenta que la
 * representación de los ejes en SDL es la siguiente:
 *
 * <pre>
 *   ________ X
 *  |
 *  |
 *  |
 *  |
 *  Y
 * </pre>
 */

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
