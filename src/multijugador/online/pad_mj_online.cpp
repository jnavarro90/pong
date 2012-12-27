#include "pad_mj_online.h"
#include "../../globals.h"

CPad_MJ_Online::CPad_MJ_Online(enum lado lado, SDLKey U, SDLKey D)
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL;
  }
  caja.y = PANTALLA_ALTO/2 - PAD_ALTO/2;
  caja.h = PAD_ALTO;
  caja.w = PAD_ANCHO;

  KUp = U;
  KDown = D;

  yVel = 0;
  momento = 0;
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
	  yVel -= PAD_VELOCIDAD;
	}
	else if(event.key.keysym.sym == KDown)
	{
	  yVel += PAD_VELOCIDAD;
	}
  }
  if(event.type == SDL_KEYUP)
  {
	if(event.key.keysym.sym == KUp)
	{
	  yVel += PAD_VELOCIDAD;
	}
	else if(event.key.keysym.sym == KDown)
	{
	  yVel -= PAD_VELOCIDAD;
	}
  }
}

void CPad_MJ_Online::mover()
{
  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
	caja.y -= yVel;
  }
}

CPad_MJ_Online_Zombi::CPad_MJ_Online_Zombi(enum lado lado)
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL;
  }
  caja.y = PANTALLA_ALTO/2 - PAD_ALTO/2;
  caja.h = PAD_ALTO;
  caja.w = PAD_ANCHO;
}

CPad_MJ_Online_Zombi::~CPad_MJ_Online_Zombi()
{
  caja.x = caja.y = caja.w = caja.h = 0;
}

void CPad_MJ_Online_Zombi::mover(int8 mov)
{
  if(mov == arriba)
  {
    yVel = -PAD_VELOCIDAD;
    momento = arriba;
  }
  else if(mov == abajo)
  {
	yVel = PAD_VELOCIDAD;
	momento = abajo;
  }
  else if(mov == quieto)
  {
	yVel = 0;
	momento = 0;
  }

  caja.y += yVel;
  cout << "Caja.y: " << caja.y << " yVel: " << yVel << endl;
  if(caja.y < PANTALLA_MARGEN_INFERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
	cout << "limite" << endl;
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
    caja.x = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL;
  }
  caja.y = PANTALLA_ALTO/2 - PAD_ALTO/2;
  caja.h = PAD_ALTO;
  caja.w = PAD_ANCHO;
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
    caja.x = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL;
  }
  caja.y = PANTALLA_ALTO/2 - PAD_ALTO/2;
  caja.h = PAD_ALTO;
  caja.w = PAD_ANCHO;
}


void CPad_MJ_Online_Client_Zombi::setY(int y)
{
  caja.y = y;
}


