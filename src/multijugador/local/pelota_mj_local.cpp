/**
 * @file
 * @brief Definición de CPelota_MJ_Local
 *
 */

#include "pelota_mj_local.h"

CPelota_MJ_Local::CPelota_MJ_Local(): CPelota_MJ()
{
  VELOCIDAD_MAX = opciones->PELOTA_VEL;
  //VELOCIDAD = 5;
  VELOCIDAD_INC_MAX = (opciones->PELOTA_VEL*7)/8;
  MOMENTO_INC = (opciones->PAD_ALTO)/8;
};

CPelota_MJ_Local::~CPelota_MJ_Local()
{
  stop = false;
  lock = false;
}


void CPelota_MJ_Local::empezar(enum gamepoint_pj_t gamepoint_pj)
{
  color = opciones->PELOTA_COLOR;

  lock = false;
  stop = false;
  caja.x = opciones->PANTALLA_ANCHO/2 - opciones->PELOTA_ALTO/2;
  caja.y = rand() % (opciones->PANTALLA_ALTO - (PANTALLA_MARGEN_INFERIOR + PANTALLA_MARGEN_SUPERIOR + opciones->PELOTA_ANCHO)) + PANTALLA_MARGEN_SUPERIOR;

  if(gamepoint_pj == gamepoint_pj1)
  {
    xVel = opciones->PELOTA_VEL/3;
  }
  else
  {
    xVel = -opciones->PELOTA_VEL/3;
  }
  yVel = 0;
}

int CPelota_MJ_Local::mover(CPad& A, CPad& B)
{
  if(stop)
    return 0;

  caja.x += xVel;
  if(caja.x <= 0) // Fin de la partida al salirse de rango. Pierda el pad izq. Gana el pad der (j2)
  {
    caja.x = 0;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    return 2;
  }
  else if(caja.x + caja.w >= opciones->PANTALLA_ANCHO) // Gana el pad izq (j1)
  {
    caja.x = opciones->PANTALLA_ANCHO - opciones->PELOTA_ANCHO;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    return 1;
  }
  // Si la pelota está bloqueada, ignora a los rebotes con los pads. La partida sigue en curso hasta que toque un borde.
  // También ignora el movimiento vertical.
  if(lock)
  {
    yVel = 0;
    return 0;
  }

  caja.y += yVel;
  // Si choca contra los bordes superiores, rebota sin más.
  if(caja.y < PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR)
  {
    caja.y -= yVel;
    yVel = -yVel;
    Mix_PlayChannel( -1, snd_pong, 0 );
  }

  SDL_Rect Pad1 = A.getCaja();
  SDL_Rect Pad2 = B.getCaja();
  int pos = 0;

  // Si choca con el pad izquierdo
  if(caja.x < Pad1.x + Pad1.w)
  {
    pos = getPos(this->getCaja(), Pad1);
    if(pos == OUT_RANGE)
    {
      lock = true;
      color = SDL_MapRGB(pantalla->format, 0xFF, 0x00, 0x00); // teñir la pelota de rojo (visible)
    }
    else
    {
      // Calcular velocidades
      setVel(yVel, xVel, pos, A.getMomento());
      // Además, vamos a hacer que la pelota no "atraviese" el pad colocándola justo en frente de éste.
      caja.x = Pad1.x + Pad1.w;

      Mix_PlayChannel( -1, snd_pong, 0 );
    }
  }
  // Si choca contra el pad derecho
  else if(caja.x + caja.w > Pad2.x)
  {
    pos = getPos(this->getCaja(), Pad2);
    if(pos == OUT_RANGE)
    {
      color = SDL_MapRGB(pantalla->format, 0xFF, 0x00, 0x00); // teñir la pelota de rojo (visible)
      lock = true;
    }
    else
    {
      // Calcular velocidades
      setVel(yVel, xVel, pos, B.getMomento());
      // Además, vamos a hacer que la pelota no "atraviese" el pad colocándola justo en frente de éste.
      caja.x = Pad2.x - caja.w;

      Mix_PlayChannel( -1, snd_pong, 0 );
    }
  }
  return 0;
}

/*void CPelota_MJ_Local::mostrar()
{
  //SDL_Rect aux;
  //aux.x = aux.y = 0;
  //aux.w = aux.h = PELOTA_ANCHO;
  aplicar_superficie((int)caja.x, (int)caja.y, img_Pelota, pantalla);
}*/

