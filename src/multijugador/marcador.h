#ifndef MARCADOR_H_
#define MARCADOR_H_

#include "../globals.h"
#include "../opciones/opciones.h"

extern const int MARCADOR_OFFSET;
extern const int MARCADOR_Y;
extern const int MARCADOR_OFFSET_FIX;
extern int MARCADOR_OFFSET_J1;
extern int MARCADOR_OFFSET_J2;

using namespace std;

class CMarcador
{
  protected:
    int marca1, marca2;
    SDL_Surface* srf_marca1;
    SDL_Surface* srf_marca2;
    TTF_Font* ttf_fuente;
    SDL_Color* color;

  public:
    CMarcador(TTF_Font* fuente, SDL_Color* c);
    CMarcador(){};
    ~CMarcador();

    //void refrescar();
    void reset();
    void mostrar();

    void incM1();
    void incM2();

    int getM1(){return marca1;}
    int getM2(){return marca2;}
};

#endif /* MARCADOR_H_ */
