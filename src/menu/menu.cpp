#include "menu.h"

CMenu::CMenu(CBoton* b, int n)
{
  botones = b;
  nBotones = n;
}

CMenu::~CMenu()
{
  botones = NULL;
  nBotones = 0;
}

void CMenu::mostrar()
{
  for(int i = 0; i < nBotones; i++)
  {
    botones[i].mostrar();
  }
}

int CMenu::eventuar()
{
  if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
  {
    for(int i = 0; i < nBotones; i++)
    {
	     if(botones[i].encima())
	       return i+1;
    }
  }
  return 0;
}
