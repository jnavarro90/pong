/**
 * @file
 * @brief Declaraci�n de CInstance_MJ_Local
 *
 */

#ifndef INSTANCIA_MJ_LOCAL_H_
#define INSTANCIA_MJ_LOCAL_H_

#include "pelota_mj_local.h"
#include "pad_mj_local.h"

#include "../marcador.h"

#include "../../instance.h"
#include "../../temporizador.h"
#include "../../warning.h"

/**
 * @brief Clase de estancia para representar el modo de juego multijugador-local.
 *
 * B�sicamente, encapsula algunos objetos (2 pads, 1 pelota y 1 marcador) para trabajar con ellos de una forma
 * m�s sencilla. El modo consiste en un sistema de pong multijugador b�sico. Por el momento el jugador 1 juega con las
 * teclas W y S, mientras que el jugador 2 usa las teclas ARRIBA y ABAJO.
 * Para m�s informaci�n sobre el funcionamiento de las estancias, vea las definiciones de los m�todos de
 * esta clase y las clases CInstance, CEngine, CMenu y CBoton.
 */
class CInstance_MJ_Local: public CInstance
{
  protected:
    CPad_MJ_Local* PJ1;
    CPad_MJ_Local* PJ2;
    CPelota_MJ_Local* pelota;
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
    CInstance_MJ_Local();
    ~CInstance_MJ_Local();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop();

    void OnRender();

#ifdef DEBUG
    void OnDebug();
#endif
};

#endif /* INSTANCIA_MJ_LOCAL_H_ */
