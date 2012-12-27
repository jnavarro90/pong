#include "warning.h"

CWarning::CWarning(TTF_Font* fuente, const char* txt, SDL_Color* color)
{
  ttf_fuente = fuente;
  str = txt;

  color1.r = color->r;
  color1.g = color->g;
  color1.b = color->b;
  srf_texto = TTF_RenderText_Solid(ttf_fuente, str.c_str(), color1);
}

CWarning::~CWarning()
{
  SDL_FreeSurface(srf_texto);
  srf_texto = NULL;

  str="";
  ttf_fuente = NULL;

  color1.r = color1.g = color1.b = 0;
}

void CWarning::mostrar()
{
  aplicar_superficie(PANTALLA_ANCHO/2 - srf_texto->w/2, PANTALLA_ALTO/2 - srf_texto->h/2, srf_texto, pantalla);
}

void CWarning::mostrar(int x, int y)
{
  aplicar_superficie(x, y, srf_texto, pantalla);
}

void CWarning::mostrar_ch(int y)
{
  aplicar_superficie(PANTALLA_ANCHO/2 - srf_texto->w/2, y, srf_texto, pantalla);
}

void CWarning::mostrar_cv(int x)
{
  aplicar_superficie(x, PANTALLA_ALTO/2 - srf_texto->h/2, srf_texto, pantalla);
}
