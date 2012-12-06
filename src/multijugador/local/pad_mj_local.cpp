#include "pad_mj_local.h"
#include "vars.h"

CPad_MJ_local::CPad_MJ_local(bool pad, SDLKey U, SDLKey D)
{
  //bpad = p;
  KUp = U;
  KDown = D;

  if(!pad) // j1 (__)_)
	caja.x = PAD_OFFSETJ1;
  else // j2
	caja.x = PAD_OFFSETJ2;

  caja.w = PAD_ANCHO;
  caja.y = PANTALLA_ALTO/2 - PAD_ALTO/2;
  caja.h = PAD_ALTO;

  yVel = 0;
  momento = 0;
}

CPad_MJ_local::~CPad_MJ_local()
{
  //bpad = false;

  caja.x = 0;
  caja.w = 0;
  caja.y = 0;
  caja.h = 0;

  yVel = 0;
  momento = 0;
}

void CPad_MJ_local::eventuar()
{
  // Ajustar y pensar hacerlo con if-else if, y asociar al pad unas teclas predefinidas.
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == KUp)
      yVel -= PAD_VELOCIDAD;
    else if(event.key.keysym.sym == KDown)
      yVel += PAD_VELOCIDAD;
  }
  else if(event.type == SDL_KEYUP)
  {
	if(event.key.keysym.sym == KUp)
	  yVel += PAD_VELOCIDAD;
	else if(event.key.keysym.sym == KDown)
	  yVel -= PAD_VELOCIDAD;
  }
}

// MEJORAR ESTA FUNCION.
/*
void CPad_MJ_local::eventuar()
{
  // Ajustar y pensar hacerlo con if-else if, y asociar al pad unas teclas predefinidas.
  if(event.type == SDL_KEYDOWN)
  {
    if(bpad)
    {
      switch(event.key.keysym.sym)
      {
        case SDLK_UP: yVel -= PAD_VELOCIDAD; break;
        case SDLK_DOWN: yVel += PAD_VELOCIDAD; break;
        default: break;
      }
    }
    else if(!bpad)
    {
      switch(event.key.keysym.sym)
      {
        case SDLK_w: yVel -= PAD_VELOCIDAD; break;
        case SDLK_s: yVel += PAD_VELOCIDAD; break;
        default: break;
      }
    }
  }
  else if(event.type == SDL_KEYUP)
  {
    if(bpad)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_UP: yVel += PAD_VELOCIDAD; break;
      case SDLK_DOWN: yVel -= PAD_VELOCIDAD; break;
        default: break;
      }
    }
    else if(!bpad)
    {
      switch(event.key.keysym.sym)
      {
      case SDLK_w: yVel += PAD_VELOCIDAD; break;
      case SDLK_s: yVel -= PAD_VELOCIDAD; break;
        default: break;
      }
    }
  }
}*/

void CPad_MJ_local::mover()
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
    momento = 0;
  }
}

void CPad_MJ_local::mostrar()
{
  aplicar_superficie(caja.x, caja.y, img_Pad, pantalla);
}

/*
CPad& CPad_MJ_local::getBase()
{
  return getPad();
}*/
