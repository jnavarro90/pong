/**
 * @file
 * @brief Declaración de CInstance_1J_INF
 *
 */

#ifndef INSTANCE_1J_INF_H_
#define INSTANCE_1J_INF_H_

#include "pad_1j_inf.h"
#include "pelota_1j_inf.h"

#include "../turbo.h"
#include "../../instance.h"
#include "../../temporizador.h"

/**
 * @brief Clase de estancia para representar el modo de juego infinito de 1 jugador.
 *
 * Básicamente, encapsula algunos objetos (1 pad, 1 pelota) para trabajar con ellos de una forma
 * más sencilla. Este modo de juego consiste en un escenario rectangular sobre el que se juega al modo "infinito".
 * A medido que pasa el tiempo, se decrementa el tamaño del pad y de la pelota y se aumenta la velocidad del pad
 * y de la pelota. No se tienen en cuenta los valores almacenados en COpciones. Tampoco se muestra al
 * usuario su puntación.
 * Para más información sobre el funcionamiento de las estancias, vea las definiciones de los métodos de
 * esta clase y las clases CInstance, CEngine, CMenu y CBoton.
 */

class CInstance_1J_INF: public CInstance
{
  protected:
    CPad_1J_INF* PJ1;
    CPelota_1J_INF* pelota;

    CTemporizador* tMarca;
    SDL_Surface* marca;

    CTurbo* turbo;

    bool fin;
    bool incVel;
    bool decTam;
  public:
    CInstance_1J_INF();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop(int& salida);
    void OnRender();
};

#endif /* INSTANCE_1J_INF_H_ */
