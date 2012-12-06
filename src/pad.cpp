#include "pad.h"
#include "globals.h"

#include <iostream>

CPad::CPad()
{
  caja.x = 0;

  caja.w = 0;
  caja.y = 0;
  caja.h = 0;

  yVel = 0;
  momento = 0;
}

CPad::~CPad()
{
  momento = 0;
  caja.x = 0;
  caja.w = 0;
  caja.y = 0;
  caja.h = 0;
}
/*
void CPad::setCaja(SDL_Rect& A)
{
  caja.x = A.x;
  caja.y = A.y;
  caja.w = A.w;
  caja.h = A.h;
}

void CPad::setMomento(int m)
{
  momento = m;
}

void CPad::setVel(int v)
{
  yVel = v;
}
*/
