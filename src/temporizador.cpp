#include "temporizador.h"

CTemporizador::CTemporizador()
{
  empezadoTicks = 0;
  pausadoTicks = 0;

  pausado = false;
  empezado = false;
}

void CTemporizador::empezar()
{
  empezado = true;
  pausado = false;

  empezadoTicks = SDL_GetTicks();
}

void CTemporizador::parar()
{
  empezado = false;
  pausado = false;
}

int CTemporizador::getTicks()
{
  if(empezado)
  {
    if(pausado)
      return pausadoTicks;
    else
      return SDL_GetTicks() - empezadoTicks;
  }

  return 0;
}

void CTemporizador::pausar()
{
  if(empezado && !pausado)
  {
    pausado = true;
    pausadoTicks = SDL_GetTicks() - empezadoTicks;
  }
}

void CTemporizador::resumir()
{
  if(pausado)
  {
    pausado = false;
    empezadoTicks = SDL_GetTicks() - pausadoTicks;

    pausadoTicks = 0;
  }
}

bool CTemporizador::Pausado()
{
  return pausado;
}

bool CTemporizador::Empezado()
{
  return empezado;
}
