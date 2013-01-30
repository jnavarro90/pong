#include "marcador_online.h"

CMarcador_Online::CMarcador_Online(TTF_Font* f, SDL_Color* c)
{
  marca1 = marca2 = 0;

  ttf_fuente = f;
  color = c;

  stringstream ss;

  ss << marca1;
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  ss.str("");
  ss.clear();

  MARCADOR_OFFSET_J1 = PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;

  ss << marca2;
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}

CMarcador_Online::~CMarcador_Online()
{
  SDL_FreeSurface(srf_marca1);
  SDL_FreeSurface(srf_marca2);

  marca1 = 0;
  marca2 = 0;

  color = NULL;

  srf_marca1 = NULL;
  srf_marca2 = NULL;

  ttf_fuente = NULL;
}

void CMarcador_Online::setM1(int n)
{
  marca1 = n;

  stringstream ss;

  ss << marca1;
  SDL_FreeSurface(srf_marca1); // liberamos para evitar lagunas de memoria
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  MARCADOR_OFFSET_J1 = PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;
}

void CMarcador_Online::setM2(int n)
{
  marca2 = n;

  stringstream ss;

  ss << marca2;
  SDL_FreeSurface(srf_marca2);
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}
