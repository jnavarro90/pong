#include "vars.h"
#include "../globals.h"

SDL_Surface* img_fondo_boton = NULL;

SDL_Surface* ttf_txt_menu_1jugador = NULL;
SDL_Surface* ttf_txt_menu_multijugador = NULL;
SDL_Surface* ttf_txt_menu_opciones = NULL;

SDL_Color ttf_color_txt_menu = {0, 0, 0};

TTF_Font* ttf_consolas = NULL;

Uint32 color = SDL_MapRGB(pantalla->format, 255, 255, 255);
