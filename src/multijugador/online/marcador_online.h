#ifndef MARCADOR_ONLINE_H_
#define MARCADOR_ONLINE_H_

#include "../marcador.h"

class CMarcador_Online: public CMarcador
{
  public:
    CMarcador_Online(TTF_Font* f, SDL_Color* c);
    ~CMarcador_Online();

    void setM1(int n);
    void setM2(int n);
};


#endif /* MARCADOR_ONLINE_H_ */
