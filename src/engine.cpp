#include <time.h>

#include "engine.h"

#include "menu/instance_menu.h"
#include "menu/submenu/instance_menu.h"

#include "1jugador/infinito/instancia.h"

#include "multijugador/local/instancia.h"
#include "multijugador/online/instancia.h"
#include "multijugador/local/cpu/instancia.h"

CEngine::CEngine()
{
  pantalla = NULL;

  running = true;
}

CEngine::~CEngine()
{
  pantalla = NULL;

  running = false;
}

bool CEngine::Init()
{
  srand (time(NULL));

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return false;

  if(TTF_Init() == -1)
    return false;

  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1)
    return false;

  if(!LoadFiles())
    return false;

  //BindInstances();

  pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, PANTALLA_BPP, SDL_SWSURFACE); // Usar SDL_HWSURFACE?
  if(pantalla == NULL)
    return false;

  SDL_WM_SetCaption( "Pong C++", "media/img/p++.ico" );
  color_blanco = SDL_MapRGB(pantalla->format, 255, 255, 255);

  return true;
}

bool CEngine::LoadFiles()
{
  snd_pong = Mix_LoadWAV("media/snd/pong.wav");
  snd_ping = Mix_LoadWAV("media/snd/ping.wav");
  snd_pung = Mix_LoadWAV("media/snd/pung.wav");

  if(snd_pong == NULL || snd_ping == NULL || snd_pung == NULL)
    return false;

  return true;
}

void CEngine::Close()
{
  UnLoadFiles();
  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();
}

void CEngine::UnLoadFiles()
{
  Mix_FreeChunk(snd_pong);
  Mix_FreeChunk(snd_ping);
  Mix_FreeChunk(snd_pung);
}

int CEngine::OnExecute()
{
  if(!Init())
  {
    cerr << ERROR_STR_INIT << " ENGINE" << endl;
    return -1;
  }

  CInstance_Menu_Main i_menu;
  CInstance_Menu_MJ i_menu_mj;
  instance[I_MENU_MAIN] = &i_menu;
  instance[I_MENU_MJ] = &i_menu_mj;

  CInstance_1J_INF i_1j_inf;
  instance[I_1J_INF] = &i_1j_inf;

  CInstance_Menu_MJ_Online i_mj_online;
  CInstance_MJ_Local i_mj_local;
  CInstance_MJ_CPU i_mj_cpu;
  CInstance_MJ_Online_Client i_mj_online_client;
  CInstance_MJ_Online_Server i_mj_online_server;
  instance[I_MJ_ONLINE] = &i_mj_online;
  instance[I_MJ_LOCAL] = &i_mj_local;
  instance[I_MJ_CPU] = &i_mj_cpu;
  instance[I_MJ_ONLINE_CLIENT] = &i_mj_online_client;
  instance[I_MJ_ONLINE_SERVER] = &i_mj_online_server;

  int menu = I_MENU_MAIN;

  while(running)
  {
    if(menu == I_SALIDA)
    {
      running = false;
    }
    else
    {
      menu = instance[menu]->OnExecute();
    }
  }
  Close();

  return menu;
}
