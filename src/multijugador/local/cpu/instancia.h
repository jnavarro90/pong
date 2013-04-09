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
