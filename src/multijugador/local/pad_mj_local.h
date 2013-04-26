/**
 * @file
 * @brief Declaración de CPad_MJ_Local
 *
 */

#include "../pad_mj.h"
//#include "../../sdl.h"

#include "../../opciones/opciones.h"

#ifndef PAD_MJ_LOCAL_H
#define PAD_MJ_LOCAL_H

/**
 * @brief Clase general para definir el pad de multijugador-local
 *
 * El funcionamiento de esta clase es muy simple. Puede ver los métodos de la clase en sí y de la clase base
 * CPad_MJ y CPad para entender el correcto funcionamiento de esta.
 *
 */
class CPad_MJ_Local : public CPad_MJ
{
  private:
    SDLKey KUp; /**< Tecla para mover el pad hacia arriba*/
    SDLKey KDown; /**< Tecla para mover el pad hacia abajo*/
  public:
    CPad_MJ_Local(bool pad, SDLKey KU, SDLKey D);
    ~CPad_MJ_Local();

    void eventuar();
    void mover();
};

#endif
