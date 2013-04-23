/**
 * @file
 * @brief Declaración de CPad
 *
 */

#ifndef PAD_H
#define PAD_H

#include "globals.h"
#include "entidad.h"

#include "opciones/opciones.h"

// Hacer que la velocidad sea un valor de tipo float (junto con las coordenadas X e Y).
const int PAD_VELOCIDAD = 2;

/**
 * @brief Clase general para definir los diversos pads
 *
 * Funciona como clase abstracta para definir las diversas clases pertenecientes a varias estancias
 *
 */
class CPad: public CEntidad
{
  protected:
    int momento; /**< Momento cinético: 0 = no, 1 = arriba, -1 = abajo */
    Uint32 color; /**< Color del pad, ubicado en COpciones::PAD_COLOR */
  public:
    CPad();
    virtual ~CPad();

    int getMomento(){return momento;};

    virtual void mostrar();
    virtual void setCalcular(bool b = true){};
};

#endif /* PAD_H */

