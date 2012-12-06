#include "globals.h"

SDL_Event event;

SDL_Surface* pantalla = NULL;
//SDL_Surface* imgPelota = NULL;
//SDL_Surface* imgPad = NULL;
//SDL_Surface* fondo = NULL;
//SDL_Surface* txtMarcador = NULL;
//SDL_Surface* sur_particula = NULL;

//SDL_Rect pared;

Mix_Chunk* snd_ping = NULL;
Mix_Chunk* snd_pong = NULL;
Mix_Chunk* snd_pung = NULL;

//SDL_Color colorTexto = {255, 255, 255};
//TTF_Font* fuente_texto = NULL;
//TTF_Font* fuente_marcador = NULL;

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





