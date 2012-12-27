#include "pelota_mj_online.h"

void CPelota_MJ_Online::empezar()
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

// Vamos a usar un sistema de flags para enviar los "sonidos" al cliente.
enum fSnd_pelota {fsnd_pong = 0x1, fsnd_pung = 0x2};

int CPelota_MJ_Online::mover(CPad A, CPad B, flags& f)
{
  if(stop)
    return 0;

  // pq no se mueve?
  caja.x += xVel;
  if(caja.x <= 0) // Fin de la partida al salirse de rango. Pierda el pad izq. Gana el pad der (j2)
  {
    caja.x = 0;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    f = f | fsnd_pung; // Activar flags de sonido "pung" para el cliente
    return 2;
  }
  else if(caja.x + caja.w >= PANTALLA_ANCHO) // Gana el pad izq (j1)
  {
    caja.x = PANTALLA_ANCHO - PELOTA_ANCHO;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    f = f | fsnd_pung;
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
    f = f | fsnd_pong;
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
    }
    else
    {
      // Calcular velocidades
      setVel(yVel, xVel, pos, A.getMomento());
      // Además, vamos a hacer que la pelota no "atraviese" el pad colocándola justo en frente de éste.
      caja.x = Pad1.x + Pad1.w;

      Mix_PlayChannel( -1, snd_pong, 0 );
      f = f | fsnd_pong;
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
      f = f | fsnd_pong;
    }
  }
  return 0;
}

void CPelota_MJ_Online_Client::setXY(int x, int y)
{
  caja.x = x;
  caja.y = y;
}

