/** @file
 * @brief Definici�n de la clase CTeclado
 * */

#include "teclado.h"


/**
 * @brief Constructor principal
 *
 * @param fuente Ruta del fichero *.ttf a cargar
 * @param color Color del texto a generar
 * @param tam Tama�o con el que se cargar� la fuente
 * @param ax,ay Offset sobre #x, #y
 * @param l Longitud m�xima de la cadena a ingresar.
 *
 * Asigna los valores pasados como par�metros y llama a la funci�n SDL_EnableUNICODE()
 */
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

/**
 * @brief Destructor
 *
 * Asigna los valores a 0 y libera superficies y archivos cargados.
 */

CTeclado::~CTeclado()
{
  TTF_CloseFont(ttf_fuente);
  SDL_FreeSurface(img_texto);

  str = "";

  color_texto.r = color_texto.b = color_texto.g = 0;
  y = x = 0;
  length = 0;

  SDL_EnableUNICODE( SDL_DISABLE ); //  � mala idea ?
}

/**
 * @brief Funci�n para gestionar eventos
 *
 * Se a�aden los caract�res tecleados a la cadena #str. Si el tama�o de #str ha superado el valor de #length, no se a�adir�
 * ning�n car�cter. En caso de pulsar la tecla SDLK_BACKSPACE y hay algo escrito en #str, se borrar� el �ltimo car�cter introducido.
 * Se generar� el texto como imagen en la superficie #img_texto en caso de que hayan habido cambios.
 */
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
      img_texto = TTF_RenderText_Blended(ttf_fuente, str.c_str(), color_texto);
    }
  }
}

/**
 * @brief Funci�n para mostrar por pantalla
 *
 * Si #img_texto no tiene un valor nulo (se ha generado al menos una imagen a partir del texto), se superpondr� a la
 * superficie #pantalla en la posici�n relatia #x,#y. En caso contrario, no se har� nada.
 */

void CTeclado::mostrar()
{
  if(img_texto != NULL)
  {
    aplicar_superficie(x, y, img_texto, pantalla);
  }
}
