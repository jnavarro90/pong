#include "../pad_mj.h"
//#include "../../sdl.h"

#include "../../opciones/opciones.h"

#ifndef PAD_MJ_LOCAL_H
#define PAD_MJ_LOCAL_H

class CPad_MJ_Local : public CPad_MJ
{
  private:
    //bool bpad;
    SDLKey KUp, KDown;
  public:
    CPad_MJ_Local(bool pad, SDLKey KU, SDLKey D);
    ~CPad_MJ_Local();

    void eventuar();
    void mover();
    //void mostrar();

    //CPad& getBase();
};

#endif
