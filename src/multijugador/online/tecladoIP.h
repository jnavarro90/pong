#ifndef TECLADONUM_H_
#define TECLADONUM_H_

#include "../../teclado.h"

class CTecladoIP: public CTeclado
{
  public:
    CTecladoIP(const char* fuente, uint tam, SDL_Color* color, int x, int y, uint lngt);

    virtual void eventuar();
    //virtual void mostrar();
};


#endif /* TECLADONUM_H_ */
