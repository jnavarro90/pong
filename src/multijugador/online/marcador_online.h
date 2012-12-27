#ifndef MARCADOR_ONLINE_H_
#define MARCADOR_ONLINE_H_

#include "../marcador.h"

class CMarcador_Online: public CMarcador
{
  public:
    CMarcador_Online(TTF_Font* f, SDL_Color* c);

    void setM1(int n){marca1 = n;}
    void setM2(int n){marca2 = n;}
};


#endif /* MARCADOR_ONLINE_H_ */
