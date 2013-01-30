#include "instance.h"

bool CInstance::Init()
{
  return true;
}

bool CInstance::LoadFiles()
{
  return true;
}


int CInstance::OnExecute()
{
  if(!Init())
    return I_SALIDA;

  int salida = 0;

  while(i_running)
  {
    while(SDL_PollEvent(&event))
    {
      OnEvent();
    }
    OnLoop();
    OnRender();
  }

  Close();
  return salida;
}

