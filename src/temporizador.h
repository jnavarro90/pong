#include "globals.h"

#ifndef TEMPORIZADOR_H_
#define TEMPORIZADOR_H_

class CTemporizador
{
  private:
    int empezadoTicks;
    int pausadoTicks;

    bool pausado;
    bool empezado;
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
