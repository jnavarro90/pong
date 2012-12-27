#ifndef WARNING_H_
#define WARNING_H_

#include "globals.h"

using namespace std;

class CWarning
{
  private:
    SDL_Surface* srf_texto;
    TTF_Font* ttf_fuente;
    SDL_Color color1;
    string str;
  public:
    CWarning(TTF_Font* fuente, const char* txt, SDL_Color* color);
    ~CWarning();

    void mostrar();
    void mostrar(int x, int y);
    void mostrar_ch(int y);
    void mostrar_cv(int x);
};


#endif /* WARNING_H_ */
