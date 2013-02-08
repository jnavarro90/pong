#ifndef INSTANCIA_MJ_CPU_H_
#define INSTANCIA_MJ_CPU_H_

#include "pelota_cpu.h"
#include "pad_cpu.h"

#include "../pad_mj_local.h"

#include "../../marcador.h"

#include "../../../instance.h"

class CInstance_MJ_CPU: public CInstance
{
  protected:
    CPad_MJ_Local* PJ1;
    CPad_CPU* PJ2;
    CPelota_CPU* pelota;
    CMarcador* marcador;

    SDL_Color color_blanco;
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
};



#endif /* INSTANCIA_MJ_CPU_H_ */
