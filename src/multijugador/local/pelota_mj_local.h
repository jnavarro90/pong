/**
 * @file
 * @brief Declaración de CPelota_MJ_Local
 *
 */


#include "../../pelota.h"
#include "../pelota_mj.h"

#include "../../opciones/opciones.h"

#include <math.h>

#ifndef PELOTA_MJ_LOCAL_H_
#define PELOTA_MJ_LOCAL_H_

/**
 * @brief Identificador de quién fue el último en marcar un punto.
 */
enum gamepoint_pj_t {gamepoint_pj1 = 0, gamepoint_pj2};


/**
 * @brief Clase general para definir la pelota de multijugador-local.
 *
 * El funcionamiento de esta clase es muy simple. Puede ver los métodos de la clase en sí y de la clase base
 * CPelota_MJ y CPelota para entender el correcto funcionamiento de esta.
 *
 */
class CPelota_MJ_Local : public CPelota_MJ
{
  protected:
    float xVel; /**< Velocidad horizontal de la pelota en píxeles por frame */
    float yVel; /**< Velocidad vertical de la pelota en píxeles por frame */
  public:
    CPelota_MJ_Local();
    ~CPelota_MJ_Local();

    void empezar(enum gamepoint_pj_t gamepoint_pj);

    bool getLock(){return lock;}
    bool getStop(){return stop;}

    int mover(CPad& A, CPad& B);
};

#endif /* PELOTA_H_ */
