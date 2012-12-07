#include "menu_mj.h"
#include "../../estancias.h"
#include "../menu_vars.h"
#include "../menu.h"
#include "../main_menu.h"
#include "../../temporizador.h"
#include "../../globals.h"

const int FRAMES_PER_SECOND = 60;

int menu_mj_main()
{
  if(!menu_cargar())
    return -1;
  CTemporizador fps;
  int frame = 0;

  CBoton* botones = new CBoton[4];
  botones[0] = CBoton(100, 200, 150, 25, "VS Local");
  botones[1] = CBoton(100, 230, 150, 25, "VS Online");
  botones[2] = CBoton(100, 260, 150, 25, "VS Máquina");
  botones[3] = CBoton(100, 290, 150, 25, "Volver");

  CMenu menu(botones, 4);

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
	if(caso != -1 && caso != 0 && caso != 4)
	{
	  caso += INSTANCIA_MJ;
	}
	if(caso == 4)
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

  menu_limpiar();
  return caso;
}
