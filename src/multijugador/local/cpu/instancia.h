/**
 * @file
 * @brief Declaración de CInstance_MJ_CPU
 *
 */

#ifndef INSTANCIA_MJ_CPU_H_
#define INSTANCIA_MJ_CPU_H_

#include "pelota_cpu.h"
#include "pad_cpu.h"

#include "../pad_mj_local.h"

#include "../../marcador.h"

#include "../../../instance.h"
#include "../../../temporizador.h"
#include "../../../warning.h"

#include "../../../opciones/opciones.h"
#include "../../../opciones/tablero.h"

/**
 * @brief Clase de estancia para representar el modo de juego multijugador-cpu.
 *
 * Básicamente, encapsula algunos objetos (1 pad del jugador, 1 pad manejado por la máquina, 1 pelota y 1 marcador)
 * para trabajar con ellos de una forma más sencilla. El modo consiste en un sistema de pong multijugador básico.
 * Por el momento el jugador 1 juega con las teclas W y S.
 * Para más información sobre el funcionamiento de las estancias, vea las definiciones de los métodos de
 * esta clase y las clases CInstance, CEngine, CMenu y CBoton.
 */
class CInstance_MJ_CPU: public CInstance
{
  protected:
    CPad_MJ_Local* PJ1;
    CPad_MJ_CPU* PJ2;
    CPelota_MJ_CPU* pelota;
    CMarcador* marcador;

    CWarning* wrGameset;
    CWarning* wrGamepoint;

    CTemporizador gameset_timer;
    CTemporizador gamepoint_timer;

    SDL_Color color_blanco;
    SDL_Color color_rojo;

    bool gameset;
    bool gamepoint;
    int gamepoint_offset_x;

    gamepoint_pj_t gamepoint_pj;
  public:
    CInstance_MJ_CPU();
    ~CInstance_MJ_CPU();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent();
    void OnLoop();

    void OnRender();

#ifdef DEBUG
    void OnDebug();
#endif
};



#endif /* INSTANCIA_MJ_CPU_H_ */
