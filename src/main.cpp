#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "multijugador/local/main_mj_local.h"

using namespace std;

//const int FRAMES_PER_SECOND = 60;

bool inicializar()
{
  srand (time(NULL));
  //srand(SDL_GetTicks());

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
      return false;

  pantalla = SDL_SetVideoMode(PANTALLA_ANCHO, PANTALLA_ALTO, PANTALLA_BPP, SDL_SWSURFACE); // Usar SDL_HWSURFACE?

  if(pantalla == NULL)
    return false;

  if(TTF_Init() == -1)
      return false;

  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1)
      return false;
  //Mix_AllocateChannels(3);

  SDL_WM_SetCaption( "Pong C++", NULL );

  return true;
}

bool cargar()
{
  snd_pong = Mix_LoadWAV("media/snd/pong.wav");
  snd_ping = Mix_LoadWAV("media/snd/ping.wav");
  snd_pung = Mix_LoadWAV("media/snd/pung.wav");

  if(snd_pong == NULL || snd_ping == NULL || snd_pung == NULL)
    return false;

  return true;
}

void limpiar()
{
  //SDL_FreeSurface(fondo);
  //SDL_FreeSurface(imgPad);
  //SDL_FreeSurface(imgPelota);
  //SDL_FreeSurface(sur_particula);

  Mix_FreeChunk(snd_pong);
  Mix_FreeChunk(snd_ping);
  Mix_FreeChunk(snd_pung);

  TTF_Quit();
  SDL_Quit();
  Mix_CloseAudio();
}

int main( int argc, char* args[] )
{
  cout << "dani" << endl;
  if(inicializar() == false)
    return 0;

  cargar();

  main_mj_local();

  limpiar();
  return 0;
}

