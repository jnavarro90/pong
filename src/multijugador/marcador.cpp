#include "marcador.h"

const int MARCADOR_OFFSET = 20;
const int MARCADOR_Y = 20;
const int MARCADOR_OFFSET_FIX = 16;
int MARCADOR_OFFSET_J1 = PANTALLA_ANCHO/2 - MARCADOR_OFFSET - TEXTO_MARCADOR_ANCHO/2;
int MARCADOR_OFFSET_J2 = PANTALLA_ANCHO/2 + MARCADOR_OFFSET;

CMarcador::CMarcador()
{
  marca1 = 0;
  marca2 = 0;
}

void CMarcador::reset()
{
  marca1 = 0;
  marca2 = 0;
}

void CMarcador::mostrar()
{
  stringstream ss;

  ss << marca1;
  ttf_txtMarcador = TTF_RenderText_Solid(ttf_fuente_marcador, ss.str().c_str(), ttf_colorTexto);
  MARCADOR_OFFSET_J1 = PANTALLA_ANCHO/2 - MARCADOR_OFFSET - ttf_txtMarcador->w + MARCADOR_OFFSET_FIX;
  aplicar_superficie(MARCADOR_OFFSET_J1, MARCADOR_Y, ttf_txtMarcador, pantalla);
  SDL_FreeSurface(ttf_txtMarcador);

  ss.str("");
  ss.clear();

  ss << marca2;
  ttf_txtMarcador = TTF_RenderText_Solid(ttf_fuente_marcador, ss.str().c_str(), ttf_colorTexto);
  aplicar_superficie(MARCADOR_OFFSET_J2, MARCADOR_Y, ttf_txtMarcador, pantalla);
  SDL_FreeSurface(ttf_txtMarcador);

}

int CMarcador::incM1()
{
  return ++marca1;
}

int CMarcador::incM2()
{
  return ++marca2;
}



