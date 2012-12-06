#include "pelota_mj_local.h"

CPelota_MJ_Local::~CPelota_MJ_Local()
{
  stop = false;
  lock = false;
}

void CPelota_MJ_Local::empezar()
{
  lock = false;
  stop = false;
  caja.x = PANTALLA_ANCHO/2 - PELOTA_ANCHO/2;
  caja.y = rand() % (PANTALLA_ALTO - (PANTALLA_MARGEN_INFERIOR + PANTALLA_MARGEN_SUPERIOR + PELOTA_ANCHO)) + PANTALLA_MARGEN_SUPERIOR;

  if(rand() % 2 == 0)
  {
    xVel = VELOCIDAD/2;
  }
  else
  {
    xVel = -VELOCIDAD/2;
  }
  yVel = 0;
}

int CPelota_MJ_Local::mover(CPad A, CPad B)
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
  else if(caja.x + caja.w >= PANTALLA_ANCHO) // Gana el pad izq (j1)
  {
    caja.x = PANTALLA_ANCHO - PELOTA_ANCHO;
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
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    caja.y -= yVel;
    yVel = -yVel;
    Mix_PlayChannel( -1, snd_pong, 0 );
  }

  SDL_Rect& Pad1 = A.getCaja();
  SDL_Rect& Pad2 = B.getCaja();
  int pos = 0;

  // Si choca con el pad izquierdo
  if(caja.x < Pad1.x + Pad1.w)
  {
    pos = getPos(this->getCaja(), Pad1);
    if(pos == OUT_RANGE)
    {
      lock = true;
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

void CPelota_MJ_Local::mostrar()
{
  //SDL_Rect aux;
  //aux.x = aux.y = 0;
  //aux.w = aux.h = PELOTA_ANCHO;
  aplicar_superficie((int)caja.x, (int)caja.y, img_Pelota, pantalla/*, &aux*/);
}

 /*
 *  Velocidad añadida al rebotar contra el pad relativa a la distancia a la que se encuentra de el centro y del
 *  momento (si el pad se mueve o no). El momento añade una cierta distancia a la posicion actual.
 *
 *  ___  _ _ _ Añadir máxima velocidad incremental al rebotar
 * |   |
 * |   |
 * |___| _ _ _ No añadir velocidad al rebote
 * |   |
 * |   |
 * |___| _ _ _ Añadir máxima velocidad (-) incremental al rebotar
 *
 */

void setVel(float& yVel, float& xVel, int pos_actual, int momento) // momento = {0 (no), 1 (arriba), -1 (abajo) }
{
  if(momento > 0) // momento == 1 (abajo)
  {
    pos_actual += MOMENTO_INC;
  }
  if(momento < 0) // momento == -1 (abajo)
  {
    pos_actual -= MOMENTO_INC;
  }

  float equivVel = -pos_actual*VELOCIDAD_INC_MAX/PAD_MEDIO;

  yVel = yVel + equivVel;

  if(yVel > VELOCIDAD_MAX)
  {
    yVel = VELOCIDAD_MAX;
  }
  else if(yVel < -VELOCIDAD_MAX)
  {
    yVel = -VELOCIDAD_MAX;
  }

  float vel = sqrt(VELOCIDAD*VELOCIDAD - yVel*yVel);

  if(xVel > 0)
  {
    xVel = -vel;
  }
  else
  {
    xVel = vel;
  }
}

/*       NO RANGO
 * MAX ___  _ _ _ _ _
 *    |   |
 *    |   |
 *  0 |___| EN RANGO
 *    |   |
 *    |   |
 *    |___| _ _ _ _ _
 * MIN
 *       NO RANGO
 */

int getPos(SDL_Rect pelota, SDL_Rect pad)
{
  // Esta comprobación se realiza cuando la pelota "atraviesa" por una esquina el pad, antes de reajustas posiciones.
  // Si no esta en el rango del pad, devuelve un valor "nulo"
  if(pelota.y +  pelota.h <= pad.y || pelota.y >= pad.y + pad.h)
    return OUT_RANGE;
  // Si entra en el rango del PAD, devolvemos la posición relativa.
  else if(pelota.y + pelota.h > pad.y && pelota.y < pad.y + pad.h)
    return (int)(pad.y + pad.h/2 - (pelota.y + pelota.h/2 ));
  return 0;
}
