#include "pad_mj.h"
#include "../globals.h"

CPad_MJ::CPad_MJ()
{
  caja.x = caja.y = caja.w = caja.h = 0;
  yVel = momento = 0;
}

CPad_MJ::~CPad_MJ()
{
}

/*void CPad_MJ::mostrar()
{
  SDL_Rect aux = getCaja();
  SDL_FillRect(pantalla, &aux, color_blanco);
}*/
