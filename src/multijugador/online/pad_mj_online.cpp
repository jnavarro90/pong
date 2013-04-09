#include "pad_mj_online.h"
#include "../../globals.h"

CPad_MJ_Online::CPad_MJ_Online(enum lado lado, SDLKey U, SDLKey D): CPad_MJ()
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;

  KUp = U;
  KDown = D;

  if(SDL_GetKeyState(NULL)[KUp])
  {
    yVel -= opciones->PAD_VEL;
  }
  if(SDL_GetKeyState(NULL)[KDown])
  {
    yVel += opciones->PAD_VEL;
  }
}

CPad_MJ_Online::~CPad_MJ_Online()
{

  caja.x = caja.y = caja.h = caja.w = 0;
  yVel = momento = 0;
}

void CPad_MJ_Online::eventuar()
{
  if(event.type == SDL_KEYDOWN)
  {
	if(event.key.keysym.sym == KUp)
	{
	  yVel -= opciones->PAD_VEL;
	}
	else if(event.key.keysym.sym == KDown)
	{
	  yVel += opciones->PAD_VEL;
	}
  }
  if(event.type == SDL_KEYUP)
  {
	if(event.key.keysym.sym == KUp)
	{
	  yVel += opciones->PAD_VEL;
	}
	else if(event.key.keysym.sym == KDown)
	{
	  yVel -= opciones->PAD_VEL;
	}
  }
}

void CPad_MJ_Online::mover()
{
  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
	caja.y -= yVel;
  }
}

CPad_MJ_Online_Zombi::CPad_MJ_Online_Zombi(enum lado lado):CPad_MJ()
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL  - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;
}

CPad_MJ_Online_Zombi::~CPad_MJ_Online_Zombi()
{
  caja.x = caja.y = caja.w = caja.h = 0;
}

void CPad_MJ_Online_Zombi::mover(int8 mov)
{
  if(mov == arriba)
  {
    yVel = -opciones->PAD_VEL;
    momento = arriba;
  }
  else if(mov == abajo)
  {
	yVel = opciones->PAD_VEL;
	momento = abajo;
  }
  else if(mov == quieto)
  {
	yVel = 0;
	momento = 0;
  }

  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_INFERIOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    caja.y -= yVel;
  }
}

CPad_MJ_Online_Client::CPad_MJ_Online_Client(enum lado lado, SDLKey U, SDLKey D)
{
  // esto funciona (de momento). Cuidado con yVel y momento
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL  - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;
  KUp = U;
  KDown = D;

  yVel = 0;
  momento = 0;
}

void CPad_MJ_Online_Client::eventuar(int8& mov)
{
  if(event.type == SDL_KEYDOWN)
  {
	if(event.key.keysym.sym == KUp)
	{
	  mov += 1;
	}
	else if(event.key.keysym.sym == KDown)
	{
	  mov -= 1;
	}
  }
  else if(event.type == SDL_KEYUP)
  {
	if(event.key.keysym.sym == KUp)
	{
	  mov -= 1;
	}
	else if(event.key.keysym.sym == KDown)
	{
	  mov += 1;
	}
  }
}

void CPad_MJ_Online_Client::setY(int y)
{
  caja.y = y;
}


CPad_MJ_Online_Client_Zombi::CPad_MJ_Online_Client_Zombi(enum lado lado)
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL  - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;
}


void CPad_MJ_Online_Client_Zombi::setY(int y)
{
  caja.y = y;
}


