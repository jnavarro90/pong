#include "main_mj_local_cpu.h"

using namespace std;

const int FRAMES_PER_SECOND = 60;

bool multijugador_local_cargar_cpu()
{
  img_fondo = cargar_img("media/img/fondo_mj_local.png", false);
  img_Pad = cargar_img("media/img/pad.png", false);
  img_Pelota = cargar_img("media/img/pelota.png", false);

  if(img_fondo == NULL || img_Pad == NULL || img_Pelota == NULL)
    return false;

  //ttf_fuente_texto = TTF_OpenFont("media/ttf/bit.ttf", 16);
  ttf_bitM = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);

  if(/*ttf_fuente_texto == NULL || */ttf_bitM == NULL)
    return false;

  return true;
}

void multijugador_local_cpu_limpiar()
{
  SDL_FreeSurface(img_fondo);
  SDL_FreeSurface(img_Pad);
  SDL_FreeSurface(img_Pelota);

  //TTF_CloseFont(ttf_fuente_texto);
  TTF_CloseFont(ttf_bitM);

  return;
}


int main_mj_local_cpu()
{
  //bool cap = true;
  int frame = 0;
  int partido = 0;
  bool salir = false;

  int salida = -1;

  if(multijugador_local_cargar_cpu() == false)
    return -1;

  CTemporizador fps;

  SDL_Color color_blanco = { 255, 255, 255 };

  CPelota_CPU pelota;
  CMarcador marcador(ttf_bitM, &color_blanco);
  CPad_MJ_local PJ1(false, SDLK_w, SDLK_s);
  CPad_CPU PJ2;

  pelota.empezar();

  while(salir == false)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      PJ1.eventuar();
      if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
      {
        //Mix_PlayChannel( -1, snd_pung, 0 );
        pelota.empezar();
      }
      if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
      {
	    salir = true;
        salida = 0;
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
      return -1;

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  multijugador_local_cpu_limpiar();

  //return -1;
  return salida;
}
