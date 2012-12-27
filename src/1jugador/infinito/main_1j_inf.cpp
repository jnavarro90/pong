#include "main_1j_inf.h"
#include "pad_1j_inf.h"
#include "pelota_1j_inf.h"
#include "vars.h"
#include "../../temporizador.h"
#include "../../globals.h"

using namespace std;

//const int FRAMES_PER_SECOND = 60;

bool cargar_1j_inf()
{
  img_1j_inf_fondo = cargar_img("media/img/fondo_1j_inf.png", false);

  if(img_1j_inf_fondo == NULL)
    return false;


  /*if(ttf_fuente_texto == NULL || ttf_fuente_marcador == NULL)
    return false;*/

  return true;
}

void limpiar_1j_inf()
{
  SDL_FreeSurface(img_1j_inf_fondo);

  return;
}


int main_1j_inf()
{
  CTemporizador fps;
  int frame = 0;

  CPelota_1J_INF pelota;
  CPad_1J_INF PJ1;

  bool salir = false;
  int salida = -1;

  int estado = 0;
  int dificultad = 8;
  int dificultad_contador = 0;

  if(cargar_1j_inf() == false)
    return -1;

  if(SDL_Flip(pantalla) == -1)
    return -1;

  color_1j_inf = SDL_MapRGB(pantalla->format, 255, 255, 255);

  pelota.empezar();

  while(salir == false)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      // Gestionar eventos
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
      if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
      {
      	PJ1.decTam(-2);
    	//pelota.incVel(1);
      	cout << "inc" << endl;
      }
      if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
      {
      	PJ1.decTam(1);
    	//pelota.incVel(-2);
      }
      if(event.type == SDL_QUIT)
        salir = true;
    }

    // Calcular posiciones
    estado = pelota.mover(PJ1);
    PJ1.mover();

    if(estado != juego)
      dificultad_contador++;

    if(dificultad_contador == dificultad)
    {
      switch(estado)
      {
        case perder: cout << "Pierdes." << endl; break;
        case juego: break;
        case rebote_pad: pelota.incVel(0.25); PJ1.decTam(1); break;
        case rebote: pelota.decTam(1); break;
        default: break;
      }
      dificultad_contador = 0;

      if(dificultad > 1)
        dificultad--;
    }

    // Mostrar por pantalla
    aplicar_superficie(0, 0, img_1j_inf_fondo, pantalla);
    PJ1.mostrar();
    pelota.mostrar();

    if(SDL_Flip(pantalla) == -1)
      return -1;

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  limpiar_1j_inf();

  return salida;
}




