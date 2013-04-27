/**
 * @file
 * @brief Declaración de la clase CTecladoIP
 */

#ifndef TECLADONUM_H_
#define TECLADONUM_H_

#include "../../teclado.h"

/**
 * @brief Clase para introducir una dirección IP por el teclado y mostrarla por pantalla.
 *
 * El objeto generado a partir de esta clase gestionará los eventos de entrada desde el teclado y los mostrará por pantalla en
 * una posición determinada. A diferencia de CTeclado, CTecladoIP sólo aceptará "puntos" y números.
 *
 */
class CTecladoIP: public CTeclado
{
  public:
    CTecladoIP(const char* fuente, uint tam, SDL_Color* color, int x, int y, uint lngt = 16);

    virtual void eventuar();
};


#endif /* TECLADONUM_H_ */
