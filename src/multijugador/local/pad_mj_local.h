#include "../../pad.h"
//#include "../../sdl.h"

#ifndef PAD_MJ_LOCAL_H
#define PAD_MJ_LOCAL_H

class CPad_MJ_local : public CPad
{
  private:
    //bool bpad;
    SDLKey KUp, KDown;
  public:
    CPad_MJ_local(bool pad, SDLKey KU, SDLKey D);
    ~CPad_MJ_local();

    void eventuar();
    void mover();
    void mostrar();

    //CPad& getBase();
};

#endif
