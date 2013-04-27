/**
 * @file
 * @brief Declaraci�n de la clase CTecladoIP
 */

#ifndef TECLADONUM_H_
#define TECLADONUM_H_

#include "../../teclado.h"

/**
 * @brief Clase para introducir una direcci�n IP por el teclado y mostrarla por pantalla.
 *
 * El objeto generado a partir de esta clase gestionar� los eventos de entrada desde el teclado y los mostrar� por pantalla en
 * una posici�n determinada. A diferencia de CTeclado, CTecladoIP s�lo aceptar� "puntos" y n�meros.
 *
 */
class CTecladoIP: public CTeclado
{
  public:
    CTecladoIP(const char* fuente, uint tam, SDL_Color* color, int x, int y, uint lngt = 16);

    virtual void eventuar();
};


#endif /* TECLADONUM_H_ */
