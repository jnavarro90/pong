#include "menu_mj.h"
#include "../../estancias.h"
#include "../menu_vars.h"
#include "../menu.h"
#include "../main_menu.h"
#include "../../temporizador.h"
#include "../../globals.h"

const int FRAMES_PER_SECOND = 60;

int menu_mj_online_main()
{
  if(!menu_cargar())
    return -1;

  CTemporizador fps;
  int frame = 0;

  SDL_Color color_negro = {0, 0, 0};
  SDL_Color color_blanco = {255, 255, 255};
  SDL_Rect cajas = {100, 200, 150, 25};

  CBoton* botones = new CBoton[3];
  botones[0] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Crear Partida");
  cajas.y += 30;
  botones[1] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Unirse a Partida");
  cajas.y += 30;
  botones[2] = CBoton(ttf_consolas, &color_negro, &color_blanco, &cajas, "Volver");

  CMenu menu(botones, 3);

  int caso = 0;

  while(caso == 0)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      caso = menu.eventuar();
      if(event.type == SDL_QUIT)
      {
        caso = -1;
      }
    }
    if(caso > 0 && caso != 3)
    {
      caso += INSTANCIA_MJ_ONLINE_M;
    }
    if(caso == 3)
    {
      caso = INSTANCIA_VOLVER;
    }

    aplicar_superficie(0, 0, img_fondo_menu, pantalla);
    menu.mostrar();

    if(SDL_Flip(pantalla) == -1)
      return 0;

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  delete []botones;
  botones = NULL;

  menu_limpiar();
  return caso;
}


