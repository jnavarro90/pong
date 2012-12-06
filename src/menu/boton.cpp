#include "boton.h"
#include "vars.h"

CBoton::CBoton(int x, int y, int w, int h, char* t)
{
  caja.x = x;
  caja.y = y;
  caja.w = w;
  caja.h = h;

  texto = t;
}

CBoton::~CBoton()
{
  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;

  texto = "";
}

void CBoton::mostrar()
{
  if(encima())
  {
	cambiarNegro(ttf_color_txt_menu);
	SDL_FillRect(pantalla, &caja, color);
  }
  else
  {
	cambiarBlanco(ttf_color_txt_menu);
  }

  // Mostrar el texto en color.


}


void cambiarNegro(SDL_Color& color)
{
  color.r = color.g = color.b = 0;
}

void cambiarBlanco(SDL_Color& color)
{
  color.r = color.g = color.b = 255;
}



