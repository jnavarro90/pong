/** @file
 * @brief Declaraci�n de la clase CTemporizador
 * */

#ifndef TEMPORIZADOR_H_
#define TEMPORIZADOR_H_

#include "globals.h"

/**
 * @brief Clase para medir tiempos en milisegundos
 *
 * Esta clase se utiliza para medir tiempos de forma sencilla. Es usado principalmente como medido para limitar los fotogramas
 * por segundo, o para contar el timeout en clases relacionadas con la modalidad de red.
 *
 */
class CTemporizador
{
  private:
    int empezadoTicks; /**< Ticks d�nde se empez� el temporizador. */
    int pausadoTicks; /**< Ticks d�nde se pauso el temporizador por �ltima vez. */

    bool pausado;  /**< Indica si el temporizador est� pausado. */
    bool empezado;  /**< Indica si el temporizador ha empezado. */
  public:
    CTemporizador();

    void empezar();
    void parar();
    void pausar();
    void resumir();

    int getTicks();

    bool Pausado();
    bool Empezado();
};

#endif /* TEMPORIZADOR_H_ */
