/**
 * @file
 * @brief Declaraci�n de CPad_MJ_CPU
 *
 */

#include "../../pad_mj.h"
#include "pelota_cpu.h"

#ifndef PAD_CPU_H_
#define PAD_CPU_H_

/**
 * @brief Calcular la pendiente de una recta entre 2 puntos
 *
 * @return Devolver el valor de la pendiente (m)
 *
 * @param x,y Coordenadas del primer punto de la recta
 * @param Vx,Vy Coordenadas del segundo punto de la recta
 *
 * La funci�n hace un c�lculo sencillo para saber la pendiente de la recta dada por los 2 puntos pasados como par�metros.
 */
float pendiente(float x, float y, float Vx, float Vy);

/**
 * @brief Dada una recta, obtener el valor en el eje Y
 *
 * @return Devuelve el valor del eje y para un determinado x
 *
 * @param m Pendiente de la recta
 * @param x0,y0 Valores de la funci�n de la recta
 * @param x Variabe a modificar
 *
 * La funci�n computar� y devolver� y = m*(x - x0) + y0
 */
int calcPos(float m, float x, float x0, float y0);

/**
 * @brief Clase general para definir el pad de multijugador-cpu
 *
 * El funcionamiento de esta clase es muy simple. Puede ver los m�todos de la clase en s� y de la clase base
 * CPad_MJ y CPad para entender el correcto funcionamiento de esta.
 *
 */
class CPad_MJ_CPU : public CPad_MJ
{
  private:
    bool calcular; /**< �Debe el pad calcular la posici�n de la pelota?*/
  public:
	   CPad_MJ_CPU();
    ~CPad_MJ_CPU();

    /**
     * @brief Avisar al pad de que debe calcular la posici�n futura de la pelota.
     *
     * @param b Nuevo valor del miembro #calcular
     */
    void setCalcular(bool b = true) {calcular = b;}

    void mover(CPelota_MJ_CPU& pelota);
};

#endif
