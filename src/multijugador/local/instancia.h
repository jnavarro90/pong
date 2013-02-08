#ifndef INSTANCIA_MJ_LOCAL_H_
#define INSTANCIA_MJ_LOCAL_H_

#include "pelota_mj_local.h"
#include "pad_mj_local.h"

#include "../marcador.h"

#include "../../instance.h"

class CInstance_MJ_Local: public CInstance
{
  protected:
    CPad_MJ_Local* PJ1;
    CPad_MJ_Local* PJ2;
    CPelota_MJ_Local* pelota;
    CMarcador* marcador;
  public:
    CInstance_MJ_Local();
    ~CInstance_MJ_Local();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent();
    void OnLoop();

    void OnRender();
};

#endif /* INSTANCIA_MJ_LOCAL_H_ */
