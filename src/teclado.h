#include <string>
#include "globals.h"

using namespace std;

#ifndef TECADO_H_
#define TECADO_H_

class CTeclado
{
  protected:
	   string str;
	   SDL_Surface* img_texto;
    TTF_Font* ttf_fuente;
    SDL_Color color_texto;
	   // offset
	   int x, y;
	   // tamaño del texto
	   uint tam;
	   // tamaño de la cadena
	   uint length;

  public:
	   CTeclado(){};
	   CTeclado(const char* fuente, uint tam, SDL_Color* color, int x, int y, uint lngt = 16);
   	virtual ~CTeclado();

   	virtual void eventuar();
 	  virtual void mostrar();

 	  string getStr() {return str;}
};


#endif /* TECADO_H_ */
