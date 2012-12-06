#include "main_mj_local.h"

using namespace std;

const int FRAMES_PER_SECOND = 60;

bool multijugador_local_cargar()
{
  img_fondo = cargar_img("media/img/fondo_mj_local.png", false);
  img_Pad = cargar_img("media/img/pad.png", false);
  img_Pelota = cargar_img("media/img/pelota.png", false);

  if(img_fondo == NULL || img_Pad == NULL || img_Pelota == NULL)
    return false;

  ttf_fuente_texto = TTF_OpenFont("media/ttf/bit.ttf", 16);
  ttf_fuente_marcador = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);

  if(ttf_fuente_texto == NULL || ttf_fuente_marcador == NULL)
    return false;

  return true;
}

void multijugador_local_limpiar()
{
  SDL_FreeSurface(img_fondo);
  SDL_FreeSurface(img_Pad);
  SDL_FreeSurface(img_Pelota);

  return;
}


void main_mj_local()
{
  CTemporizador fps;
  //CPelota_MJ_Local pelota;
  CPelota_CPU pelota;
  CMarcador marcador;
  CPad_MJ_local PJ1(false, SDLK_w, SDLK_s);
  //CPad_MJ_local PJ2(true, SDLK_UP, SDLK_DOWN);
  CPad_CPU PJ2;

  //bool cap = true;
  int frame = 0;
  int partido = 0;
  bool salir = false;

  if(multijugador_local_cargar() == false)
    return;

  if(SDL_Flip(pantalla) == -1)
    return;

  pelota.empezar();

  while(salir == false)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      PJ1.eventuar();
      //PJ2.eventuar();
      if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
      {
        //Mix_PlayChannel( -1, snd_pung, 0 );
        pelota.empezar();
      }
      if(event.type == SDL_QUIT)
        salir = true;
    }
    partido = pelota.mover(PJ1, PJ2);
    PJ1.mover();
    PJ2.mover(pelota);

    if(partido == 1)
    {
      marcador.incM1();
    }
    else if(partido == 2)
    {
      marcador.incM2();
    }

    // Mostrar por pantalla
    aplicar_superficie(0, 0, img_fondo, pantalla);

    PJ1.mostrar();
    PJ2.mostrar();

    pelota.mostrar();
    marcador.mostrar();

    if(SDL_Flip(pantalla) == -1)
      return;

    frame++;
    if(/*cap == true && */(fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  multijugador_local_limpiar();

  return;
}
