/**
 * @file
 * @brief Declaraci�n de CPelota_MJ_CPU
 *
 */

#ifndef PELOTA_CPU_H_
#define PELOTA_CPU_H_

#include "../pelota_mj_local.h"

/**
 * @brief Clase general para definir la pelota de multijugador-cpu.
 *
 * El funcionamiento de esta clase es muy simple. Puede ver los m�todos de la clase en s� y de la clase base
 * CPelota_MJ_Local y CPelota para entender el correcto funcionamiento de esta.
 *
 */
class CPelota_MJ_CPU : public CPelota_MJ_Local
{
  public:
    CPelota_MJ_CPU():CPelota_MJ_Local(){};

	   int getX(){return caja.x;} /**< @brief Obtener posici�n del eje x*/
   	int getY(){return caja.y;} /**< @brief Obtener posici�n del eje y*/

   	float getxVel();
   	float getyVel();

	   int mover(CPad& A, CPad& B);

	   //void empezar(enum gamepoint_pj_t);
};


#endif
