#ifndef BOTON_H_
#define BOTON_H_

#include "../globals.h"
#include <string>

void cambiarNegro(SDL_Color& color);
void cambiarBlanco(SDL_Color& color);

using namespace std;

class CBoton
{
  private:
    SDL_Rect caja;
    string texto;
  public:
    CBoton(int x, int y, int w, int h, char* t);
    ~CBoton();

    void mostrar();
    //void set;
    //void eventuar();

    bool encima(){return true;};
};

#endif /* BOTON_H_ */
