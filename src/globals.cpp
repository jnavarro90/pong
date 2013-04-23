/**
 * @file
 * @brief Definición de variables globales
 */

#include <math.h>

#include "globals.h"
#include "opciones/opciones.h"

SDL_Event event;
SDL_Surface* pantalla = NULL;

Mix_Chunk* snd_ping = NULL;
Mix_Chunk* snd_pong = NULL;
Mix_Chunk* snd_pung = NULL;

//SDL_Color color_blanco_t = {255, 255, 255};

TTF_Font* ttf_consolas = NULL;
TTF_Font* ttf_consolasM = NULL;
TTF_Font* ttf_bitM = NULL;

//Uint32 color_blanco;

bool initPantalla()
{
  // Set Flags
  Uint32 flags = SDL_SWSURFACE;
  if(opciones->PANTALLA_COMPLETA)
    flags = flags | SDL_FULLSCREEN;

  // Asignar memoria y opciones a la superficie de #pantalla
  pantalla = SDL_SetVideoMode(opciones->PANTALLA_ANCHO, opciones->PANTALLA_ALTO, opciones->PANTALLA_BPP, flags);
  if(pantalla == NULL)
  {
    cout << "Error creando ventana ( SDL_SetVideMode() )" << endl;
    return false;
  }
  return true;
}

#ifdef DEBUG
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#endif

ostream& operator<<(ostream& os, flags f)
{
  for(int i = 7; i >= 0; i--)
  {
    if(f & (int)pow(2,i)) // comprobar para cada bit
      os << 1;
    else
      os << 0;
  }
  return os;
}
void aplicar_superficie(int x, int y, SDL_Surface* entrada, SDL_Surface* destino, SDL_Rect* clip)
{
  SDL_Rect offset;

  offset.x = x;
  offset.y = y;

  // Combinar bits
  SDL_BlitSurface(entrada, clip, destino, &offset);
}

SDL_Surface* cargar_img(std::string s, bool alphapng)
{
  // Punteros
  SDL_Surface* img = NULL;
  SDL_Surface* opImg = NULL;

  // Cargar bmp
  img = IMG_Load(s.c_str());

  if(img != NULL)
  {
    if(!alphapng)
      opImg = SDL_DisplayFormat(img);
    else
      opImg = SDL_DisplayFormatAlpha(img);
    SDL_FreeSurface(img);
  }

  if(opImg != NULL && alphapng != true)
  {
    Uint32 colorkey = SDL_MapRGB( opImg->format, 0, 0, 0xFF);
    SDL_SetColorKey(opImg, SDL_SRCCOLORKEY, colorkey);
  }

  return opImg;
}





