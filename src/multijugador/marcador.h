#ifndef MARCADOR_H_
#define MARCADOR_H_

#include "local/vars.h"

extern const int MARCADOR_OFFSET;
extern const int MARCADOR_Y;
extern const int MARCADOR_OFFSET_FIX;
extern int MARCADOR_OFFSET_J1;
extern int MARCADOR_OFFSET_J2;

using namespace std;

class CMarcador
{
  private:
    int marca1, marca2;
  public:
    CMarcador();

    //void refrescar();
    void reset();
    void mostrar();

    int incM1();
    int incM2();

    int getM1(){return marca1;}
    int getM2(){return marca2;}
};

#endif /* MARCADOR_H_ */
