//#include "globals.h"
#include "pelota.h"
#include <iostream>
#include "multijugador/local/vars.h"

using namespace std;

CPelota::CPelota()
{
  caja.x = 0;
  caja.y = 0;
  caja.w = PELOTA_ANCHO;
  caja.h = PELOTA_ANCHO;

  xVel = 0;
  yVel = 0;
}

CPelota::~CPelota()
{
  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;

  xVel = 0;
  yVel = 0;
}

SDL_Rect CPelota::getCaja()
{
  SDL_Rect aux;
  aux.x = (int)caja.x;
  aux.y = (int)caja.y;
  aux.w = caja.w;
  aux.h = caja.h;

  return aux;
}


