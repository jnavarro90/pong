#include "pad_mj_local.h"

int PAD_OFFSETJ1_MJ_LOCAL;
int PAD_OFFSETJ2_MJ_LOCAL;

CPad_MJ_Local::CPad_MJ_Local(bool pad, SDLKey U, SDLKey D): CPad_MJ()
{
  //bpad = p;
  KUp = U;
  KDown = D;

  PAD_OFFSETJ1_MJ_LOCAL = PANTALLA_MARGEN_LATERAL;
  PAD_OFFSETJ2_MJ_LOCAL = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - opciones->PAD_ANCHO;

  if(SDL_GetKeyState(NULL)[KUp])
  {
    yVel -= opciones->PAD_VEL;
  }
  if(SDL_GetKeyState(NULL)[KDown])
  {
    yVel += opciones->PAD_VEL;
  }

  if(!pad) // j1 (__)_)
	   caja.x = PAD_OFFSETJ1_MJ_LOCAL;
  else // j2
	   caja.x = PAD_OFFSETJ2_MJ_LOCAL;

  caja.w = opciones->PAD_ANCHO;
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
}

CPad_MJ_Local::~CPad_MJ_Local()
{
  caja.x = 0;
  caja.w = 0;
  caja.y = 0;
  caja.h = 0;

  yVel = 0;
  momento = 0;
}

void CPad_MJ_Local::eventuar()
{
  // Ajustar y pensar hacerlo con if-else if, y asociar al pad unas teclas predefinidas.
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == KUp)
      yVel -= opciones->PAD_VEL;
    else if(event.key.keysym.sym == KDown)
      yVel += opciones->PAD_VEL;
  }
  else if(event.type == SDL_KEYUP)
  {
	   if(event.key.keysym.sym == KUp)
	     yVel += opciones->PAD_VEL;
	   else if(event.key.keysym.sym == KDown)
	     yVel -= opciones->PAD_VEL;
  }
}

void CPad_MJ_Local::mover()
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
  if(caja.y < PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR)
  {
    caja.y -= yVel;
    momento = 0;
  }
}
