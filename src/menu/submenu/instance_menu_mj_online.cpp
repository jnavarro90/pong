/**
 * @file
 * @brief Definición de las clas CInstance_Menu_MJ_Online
 */

#include "instance_menu_mj.h"

const int FRAMES_PER_SECOND = 60;

CInstance_Menu_MJ_Online::CInstance_Menu_MJ_Online()
{
  color_negro.r = color_negro.g = color_negro.b = 0x00;
  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;

  botones = NULL;
  menu = NULL;
}

bool CInstance_Menu_MJ_Online::Init()
{
  if(!LoadFiles())
    return false;

  SDL_Rect cajas = {100, 200, 180, 25};

  botones = new CBoton[3];
  botones[0] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Crear Partida");cajas.y += 30;
  botones[1] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Unirse a Partida");cajas.y += 30;
  botones[2] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Volver");

  menu = new CMenu(botones, 3);

  i_running = true;
  botones = new CBoton[4];

  return true;
}

bool CInstance_Menu_MJ_Online::LoadFiles()
{
  //fondo = cargar_img("media/img/fondo_menu.png", false);
  fondo = SDL_CreateRGBSurface(SDL_SWSURFACE, opciones->PANTALLA_ANCHO, opciones->PANTALLA_ALTO, opciones->PANTALLA_BPP, 0x00, 0x00, 0x00, 0x00);
  if(fondo == NULL)
  {
    cout << ERROR_STR_SURFACE << "MENU_1J -> fondo" << endl;
    return false;
  }

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);

  if(ttf_consolas == NULL)
  {
    cout << ERROR_STR_FILE << "media/ttf/consolab.ttf" << endl;
    return false;
  }

  // Linea blanca para dar un estilo minimalista
  SDL_Rect caja = {80, 200, 8, 115};
  SDL_FillRect(fondo, &caja, SDL_MapRGB(pantalla->format, 0xFF, 0xFF, 0xFF) );

  return true;
}

void CInstance_Menu_MJ_Online::Close()
{
  UnLoadFiles();

  delete []botones;
  delete menu;

}

void CInstance_Menu_MJ_Online::UnLoadFiles()
{
  SDL_FreeSurface(fondo);
  TTF_CloseFont(ttf_consolas);
}



int CInstance_Menu_MJ_Online::OnExecute()
{
  if(!Init())
  {
    cout << ERROR_STR_INIT << " MENU_MJ_ONLINE" << endl;
    return ERROR_CODE_GENERAL;
  }

  int frame = 0;
  CTemporizador fps;

  //int caso = 0;
  int salida = I_MENU_MJ;

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent(salida);
    }
    //OnLoop(salida);
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  Close();

  return salida;
}

void CInstance_Menu_MJ_Online::OnEvent(int& caso)
{
  caso = menu->eventuar();
  switch(caso)
  {
    case 1: // servidor
      caso = I_MJ_ONLINE_SERVER;
      i_running = false;
    break;
    case 2: // cliente
      caso = I_MJ_ONLINE_CLIENT;
      i_running = false;
    break;
    case 3: // volver
      caso = I_MENU_MJ;
      i_running = false;
    break;
    default: break;
  }

  if(event.type == SDL_QUIT)
  {
    caso = I_SALIDA;
    i_running = false;
  }
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == SDLK_ESCAPE)
    {
      i_running = false;
    }
  }

}

void CInstance_Menu_MJ_Online::OnRender()
{
  aplicar_superficie(0, 0, fondo, pantalla);
  menu->mostrar();

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}
