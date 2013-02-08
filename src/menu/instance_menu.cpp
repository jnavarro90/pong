#include "instance_menu.h"

CInstance_Menu_Main::CInstance_Menu_Main()
{
  color_negro.r = color_negro.g = color_negro.b = 0x00;
  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;

  botones = NULL;
  menu = NULL;
}

bool CInstance_Menu_Main::Init()
{
  if(!LoadFiles())
    return false;

  SDL_Rect cajas = {100, 200, 150, 25};

  botones = new CBoton[4];
  botones[0] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Un Jugador"); cajas.y += 30;
  botones[1] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Multijugador"); cajas.y += 30;
  botones[2] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Opciones"); cajas.y += 30;
  botones[3] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Salir");

  menu = new CMenu(botones, 4);

  i_running = true;
  botones = new CBoton[4];

  return true;
}

bool CInstance_Menu_Main::LoadFiles()
{
  fondo = cargar_img("media/img/fondo_menu.png", false);

  if(fondo == NULL)
  {
    cerr << ERROR_STR_FILE << "media/img/fondo_menu.png" << endl;
    return false;
  }

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);

  if(ttf_consolas == NULL)
  {
    cerr << ERROR_STR_FILE << "media/ttf/consolab.ttf" << endl;
    return false;
  }

  return true;
}

void CInstance_Menu_Main::Close()
{
  UnLoadFiles();

  delete []botones;
  delete menu;

}

void CInstance_Menu_Main::UnLoadFiles()
{
  SDL_FreeSurface(fondo);
  TTF_CloseFont(ttf_consolas);
}



int CInstance_Menu_Main::OnExecute()
{
  if(!Init())
  {
    cerr << ERROR_STR_INIT << " MENU_MAIN" << endl;
    return ERROR_CODE_GENERAL;
  }

  int frame = 0;
  CTemporizador fps;

  int salida = I_SALIDA;

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent(salida);
    }
    OnLoop(salida);
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  Close();

  return salida;
}

void CInstance_Menu_Main::OnEvent(int& caso)
{
  caso = menu->eventuar();
  if(event.type == SDL_QUIT)
  {
    caso = I_SALIDA;
    i_running = false;
  }
}

void CInstance_Menu_Main::OnLoop(int& caso)
{
  switch(caso)
  {
    case 1:
      //caso = I_MENU_1J;
      caso = I_1J_INF;
      i_running = false;
    break;
    case 2:
      caso = I_MENU_MJ;
      i_running = false;
    break;
    case 3:
      caso = I_MENU_OPCIONES;
      i_running = false;
    break;
    case 4:
      caso = I_SALIDA;
      i_running = false;
    break;
    default: break;
  }
}

void CInstance_Menu_Main::OnRender()
{
  aplicar_superficie(0, 0, fondo, pantalla);
  menu->mostrar();

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}