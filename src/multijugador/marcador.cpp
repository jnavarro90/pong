#include "marcador.h"

const int MARCADOR_OFFSET = 20;
const int MARCADOR_Y = 20;
const int MARCADOR_OFFSET_FIX = 16;
int MARCADOR_OFFSET_J1;
int MARCADOR_OFFSET_J2;
/*int MARCADOR_OFFSET_J1 = PANTALLA_ANCHO/2 - MARCADOR_OFFSET - TEXTO_MARCADOR_ANCHO/2;
int MARCADOR_OFFSET_J2 = PANTALLA_ANCHO/2 + MARCADOR_OFFSET;*/

CMarcador::CMarcador(TTF_Font* f, SDL_Color* c)
{
  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - TEXTO_MARCADOR_ANCHO/2;
  MARCADOR_OFFSET_J2 = opciones->PANTALLA_ANCHO/2 + MARCADOR_OFFSET;

  marca1 = 0;
  marca2 = 0;

  color = c;

  srf_marca1 = NULL;
  srf_marca2 = NULL;

  ttf_fuente = f;

  stringstream ss;

  ss << marca1;
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  ss.str("");
  ss.clear();

  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;

  ss << marca2;
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}

CMarcador::~CMarcador()
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

void CMarcador::reset()
{
  marca1 = 0;
  marca2 = 0;

  srf_marca1 = NULL;
  srf_marca2 = NULL;

  ttf_fuente = NULL;
  color = NULL;
}

/*
void CMarcador::mostrar()
{
  // El string stream nos sirve para transformar rapidamente un número en una cadena de caractéres
  stringstream ss;

  ss << marca1;
  cout << ttf_fuente << " " << color->r << " " << color->g << " " << color->b << endl;
  srf_marca = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
  MARCADOR_OFFSET_J1 = PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca->w + MARCADOR_OFFSET_FIX;
  aplicar_superficie(MARCADOR_OFFSET_J1, MARCADOR_Y, srf_marca, pantalla);
  SDL_FreeSurface(srf_marca);

  ss.str("");
  ss.clear();

  ss << marca2;
  srf_marca = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
  aplicar_superficie(MARCADOR_OFFSET_J2, MARCADOR_Y, srf_marca, pantalla);
  SDL_FreeSurface(srf_marca);
}*/

void CMarcador::mostrar()
{
  aplicar_superficie(MARCADOR_OFFSET_J1, MARCADOR_Y, srf_marca1, pantalla);
  aplicar_superficie(MARCADOR_OFFSET_J2, MARCADOR_Y, srf_marca2, pantalla);
}

void CMarcador::incM1()
{
  marca1++;

  stringstream ss;

  ss << marca1;
  SDL_FreeSurface(srf_marca1);
  srf_marca1 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);

  MARCADOR_OFFSET_J1 = opciones->PANTALLA_ANCHO/2 - MARCADOR_OFFSET - srf_marca1->w + MARCADOR_OFFSET_FIX;
}

void CMarcador::incM2()
{
  marca2++;

  stringstream ss;

  ss << marca2;
  SDL_FreeSurface(srf_marca2);
  srf_marca2 = TTF_RenderText_Solid(ttf_fuente, ss.str().c_str(), *color);
}



