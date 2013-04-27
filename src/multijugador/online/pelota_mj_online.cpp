/**
 * @file
 * @brief Definición de CPelota_MJ_Online y CPelota_MJ_Online_Client
 *
 */

#include "pelota_mj_online.h"

/**
 * @brief Constructor principal
 *
 * Asigna los valores a las velocidades dependiendo de la estructura #opciones del tipo COpciones.
 */
CPelota_MJ_Online::CPelota_MJ_Online(): CPelota_MJ()
{
  VELOCIDAD_MAX = opciones->PELOTA_VEL;
  //VELOCIDAD = 5;
  VELOCIDAD_INC_MAX = (opciones->PELOTA_VEL*7)/8;
  MOMENTO_INC = (opciones->PAD_ALTO)/8;
}

/**
 * @brief Iniciar la pelota
 *
 * Vea CPelota_MJ_Local::empezar() para ver el funcionamiento (parecido) de la función.
 */
void CPelota_MJ_Online::empezar()
{
  lock = false;
  stop = false;
  caja.x = opciones->PANTALLA_ANCHO/2 - opciones->PELOTA_ANCHO/2;
  caja.y = rand() % (opciones->PANTALLA_ALTO - (PANTALLA_MARGEN_INFERIOR + PANTALLA_MARGEN_SUPERIOR + opciones->PELOTA_ANCHO)) + PANTALLA_MARGEN_SUPERIOR;

  if(rand() % 2 == 0)
  {
    xVel = opciones->PELOTA_VEL/2;
  }
  else
  {
    xVel = -opciones->PELOTA_VEL/2;
  }

  yVel = 0;
}

// Vamos a usar un sistema de flags para enviar los "sonidos" al cliente.
//enum fSnd_pelota {fsnd_pong = 0x1, fsnd_pung = 0x2};

/**
 * @brief Función de movimiento de la pelota
 *
 * @return Devuelve un valor para saber el estado de la partida del tipo #partido_t
 *
 * @param A Pad izquierdo a tener en cuenta para los rebotes de la pelota
 * @param B Pad derecho a tener en cuenta para los rebotes de la pelota
 * @param f Flags que se enviarán al cliente para saber si debe reproducir algún sonido. vea #fSnd_pelota
 *
 * El funcionamiento de la clase es similar a CPelota_MJ_Local::mover() o CPelota_MJ::mover()
 */
int CPelota_MJ_Online::mover(CPad& A, CPad& B, flags& f)
{
  if(stop)
    return partido_jugando;

  // pq no se mueve?
  caja.x += xVel;
  if(caja.x <= 0) // Fin de la partida al salirse de rango. Pierda el pad izq. Gana el pad der (j2)
  {
    caja.x = 0;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    f = f | fsnd_pung; // Activar flags de sonido "pung" para el cliente
    return partido_ganaJ2;
  }
  else if(caja.x + caja.w >= opciones->PANTALLA_ANCHO) // Gana el pad izq (j1)
  {
    caja.x = opciones->PANTALLA_ANCHO - opciones->PELOTA_ANCHO;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    f = f | fsnd_pung;
    return partido_ganaJ1;
  }
  // Si la pelota está bloqueada, ignora a los rebotes con los pads. La partida sigue en curso hasta que toque un borde.
  // También ignora el movimiento vertical.
  if(lock)
  {
    yVel = 0;
    return partido_jugando;
  }

  caja.y += yVel;
  // Si choca contra los bordes superiores, rebota sin más.
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
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
  return partido_jugando;
}

void CPelota_MJ_Online_Client::setXY(int x, int y)
{
  caja.x = x;
  caja.y = y;
}

