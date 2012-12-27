#include "teclado.h"

CTeclado::CTeclado(const char* fuente, uint tam, SDL_Color* color, int ax, int ay, uint l)
{
  ttf_fuente = TTF_OpenFont(fuente, tam);

  str = "";
  img_texto = NULL;

  length = l;

  color_texto.r = color->r;
  color_texto.b = color->b;
  color_texto.g = color->g;

  x = ax;
  y = ay;

  SDL_EnableUNICODE( SDL_ENABLE );
}

CTeclado::~CTeclado()
{
  TTF_CloseFont(ttf_fuente);
  SDL_FreeSurface(img_texto);

  str = "";

  color_texto.r = color_texto.b = color_texto.g = 0;
  y = x = 0;
  length = 0;

  //  ¿ mala idea ?
  SDL_EnableUNICODE( SDL_DISABLE );
}

void CTeclado::eventuar()
{
  if(event.type == SDL_KEYDOWN)
  {
    string temp = str;

    if(str.length() <= length)
    {
      // Si es un  simbolo ( ' ', '.', '_', '-', '/')
      if(event.key.keysym.unicode == (Uint16)' ' || event.key.keysym.unicode == (Uint16)'.' || event.key.keysym.unicode == (Uint16)'_' || event.key.keysym.unicode == (Uint16)'-' || event.key.keysym.unicode == (Uint16)'/')
      {
        str += (char)event.key.keysym.unicode;
      }
      // Si es un numero
      else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
      {
        str += (char)event.key.keysym.unicode;
      }
      // Si es una mayuscula
      else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
      {
        str += (char)event.key.keysym.unicode;
      }
      // Si es una letra minuscula
      else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
      {
        str += (char)event.key.keysym.unicode;
      }
    }
    // Si queremos borrar y la cadena no es vacia
    if((event.key.keysym.sym == SDLK_BACKSPACE) && (str.length() != 0 ))
    {
      // Borrar el ultimo caracter
      str.erase( str.length() - 1 );
    }
    if(str != temp)
    {
      SDL_FreeSurface(img_texto);

      img_texto = TTF_RenderText_Solid(ttf_fuente, str.c_str(), color_texto);
    }
  }
}

void CTeclado::mostrar()
{
  if(img_texto != NULL)
  {
    aplicar_superficie(x, y, img_texto, pantalla);
  }
}
