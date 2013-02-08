#include "pad_1j_inf.h"
#include "vars.h"
#include "../../globals.h"

float PAD_1J_INF_VELOCIDAD = PAD_VELOCIDAD;
int PAD_1J_INF_ALTO = PAD_ALTO;
int PAD_1J_INF_MEDIO = PAD_ALTO/2;

CPad_1J_INF::CPad_1J_INF()
{
  KUp = SDLK_w;
  KDown = SDLK_s;

  yVel = 0;
  if(SDL_GetKeyState(NULL)[KUp])
  {
    yVel -= PAD_1J_INF_VELOCIDAD;
  }
  if(SDL_GetKeyState(NULL)[KDown])
  {
    yVel += PAD_1J_INF_VELOCIDAD;
  }


  caja.w = PAD_ANCHO;
  caja.h = PAD_ALTO;

  caja.y = PANTALLA_ALTO/2 + caja.h/2;
  caja.x = PANTALLA_MARGEN_LATERAL;

  //yVel = PAD_VELOCIDAD;
  //yVel = 0;
  momento = 0;
}

CPad_1J_INF::~CPad_1J_INF()
{
  caja.w = 0;
  caja.h = 0;

  caja.y = 0;
  caja.x = 0;

  yVel = 0;
  momento = 0;
}

void CPad_1J_INF::mover()
{
  if(yVel < 0)
  {
    momento = 1;
  }
  else if(yVel > 0)
  {
	   momento = -1;
  }
  else if(yVel == 0)
  {
	   momento = 0;
  }

  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    caja.y -= yVel;
  }
}

void CPad_1J_INF::incVel(float n)
{
  /*if(yVel > PAD_1J_INF_MIN_VEL)
  {
    PAD_1J_INF_VELOCIDAD -= n;
    // Por si el pad se esta moviendo, decrementamos su velocidad actual
    if(yVel < 0)
    {
      yVel += n;
    }
    if(yVel > 0)
    {
      yVel += n;
    }
  }*/
  PAD_1J_INF_VELOCIDAD += n;
  // Por si el pad se esta moviendo, decrementamos su velocidad actual
  if(yVel < 0)
  {
    yVel -= n;
  }
  if(yVel > 0)
  {
    yVel += n;
  }
}

void CPad_1J_INF::decTam(int n)
{
  if(/*n < 0 || */caja.h > PAD_1J_INF_MIN_ALTO)
  {
    // Decrementa el tamaño con respecto al centro.
    caja.y += n/2;
    caja.h -= n;
    PAD_1J_INF_ALTO -= 2*n;
    PAD_1J_INF_MEDIO -= n;
  }
}

void CPad_1J_INF::eventuar()
{
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == KUp)
      yVel -= PAD_1J_INF_VELOCIDAD;
    else if(event.key.keysym.sym == KDown)
      yVel += PAD_1J_INF_VELOCIDAD;
  }
  else if(event.type == SDL_KEYUP)
  {
	if(event.key.keysym.sym == KUp)
	  yVel += PAD_1J_INF_VELOCIDAD;
	else if(event.key.keysym.sym == KDown)
	  yVel -= PAD_1J_INF_VELOCIDAD;
  }
}
