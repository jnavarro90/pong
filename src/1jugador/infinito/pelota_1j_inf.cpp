#include "pelota_1j_inf.h"
#include "pad_1j_inf.h"
#include "vars.h"
#include "../../globals.h"

const float FACTOR1 = (2/3.0);
const float FACTOR2 = (2/5.0);

float PELOTA_1J_INF_VELOCIDAD = 6.0;
float PELOTA_1J_INF_VELOCIDAD_MAX = PELOTA_1J_INF_VELOCIDAD*FACTOR1;
float PELOTA_1J_INF_VELOCIDAD_INC = PELOTA_1J_INF_VELOCIDAD*FACTOR2;

const int PELOTA_1J_INF_TAM_MIN = 6; //px

CPelota_1J_INF::CPelota_1J_INF()
{
  caja.x = PANTALLA_ANCHO/2 - PELOTA_ANCHO/2;
  caja.y = PANTALLA_ALTO/2 - PELOTA_ANCHO/2;
  caja.w = PELOTA_ANCHO;
  caja.h = PELOTA_ANCHO;

  xVel = 0;
  yVel = 0;
}

CPelota_1J_INF::~CPelota_1J_INF()
{
  stop = false;
  lock = false;

  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;

  xVel = 0;
  yVel = 0;
}

void CPelota_1J_INF::mostrar()
{
  SDL_Rect aux;
  aux.x = (int)caja.x;
  aux.y = (int)caja.y;
  aux.h = (int)caja.h;
  aux.w = (int)caja.w;

  SDL_FillRect(pantalla, &aux, color_1j_inf);
}

/* Editar:  ¿? */
int CPelota_1J_INF::mover(CPad_1J_INF A)
{
  if(stop)
  {
    return perder;
  }

  caja.x += xVel;

  if(caja.x <= 0) // Fin de la partida al salirse de rango. Pierda el pad izq. Gana el pad der (j2)
  {
    caja.x = 0;
    stop = true;
    Mix_PlayChannel( -1, snd_pung, 0 );
    return perder;
  }

  int salida = juego;

  if(caja.x + caja.w > PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL) // Si choca contra la pared derecha
  {
    caja.x -= xVel;
    xVel = -xVel;
    Mix_PlayChannel( -1, snd_pong, 0 );
    salida = rebote;
  }

  // Si la pelota está bloqueada, ignora a los rebotes con los pads. La partida sigue en curso hasta que toque un borde.
  // También ignora el movimiento vertical.
  if(lock)
  {
    yVel = 0;
    return juego;
  }

  caja.y += yVel;

  // Si choca contra los bordes superiores, rebota sin más.
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    caja.y -= yVel;
    yVel = -yVel;
    Mix_PlayChannel( -1, snd_pong, 0 );
    salida = rebote;
  }

  SDL_Rect Pad = A.getCaja();
  int pos = 0;

  // Si choca con el pad izquierdo
  if(caja.x < Pad.x + Pad.w)
  {
    pos = getPos_1j_inf(this->getCaja(), Pad);
    if(pos == OUT_RANGE)
    {
      lock = true;
      salida = juego;
    }
    else
    {
      // Calcular velocidades
      setVel_1j_inf(yVel, xVel, pos, A.getMomento());
      // Además, vamos a hacer que la pelota no "atraviese" el pad colocándola justo en frente de éste.
      caja.x = Pad.x + Pad.w;
      Mix_PlayChannel( -1, snd_pong, 0 );
      salida = rebote_pad;
    }
  }

  return salida;
}

// Suponemos que siempre aumenta su velocidad (hasta el infinito!)
void CPelota_1J_INF::incVel(float n)
{
  PELOTA_1J_INF_VELOCIDAD += n;

  PELOTA_1J_INF_VELOCIDAD_MAX = PELOTA_1J_INF_VELOCIDAD*FACTOR1;
  PELOTA_1J_INF_VELOCIDAD_INC = PELOTA_1J_INF_VELOCIDAD*FACTOR2;

  // Si la pelota se mueve, recalcular la velocidad, ¿no?
}

void CPelota_1J_INF::decTam(float n)
{
  if(caja.w > PELOTA_1J_INF_TAM_MIN)
  {
    caja.x += n/2;
    caja.w -= n;
    caja.y += n/2;
    caja.h -= n;
  }
}

void CPelota_1J_INF::empezar()
{
  lock = stop = false;
  caja.y = PANTALLA_ALTO/2 - caja.w/2;
  caja.x = PANTALLA_ANCHO/2;

  yVel = 0;
  xVel = PELOTA_1J_INF_VELOCIDAD/2;
}

/*void CPelota_1J_INF::recalc()
{
  PELOTA_1J_INF_VELOCIDAD_MAX = PELOTA_1J_INF_VELOCIDAD*FACTOR1;
  PELOTA_1J_INF_VELOCIDAD_INC = PELOTA_1J_INF_VELOCIDAD*FACTOR2;
}*/

void setVel_1j_inf(float& yVel, float& xVel, int pos_actual, int momento) // momento = {0 (no), 1 (arriba), -1 (abajo) }
{
  if(momento > 0) // momento == 1 (abajo)
  {
    pos_actual += MOMENTO_INC;
  }
  if(momento < 0) // momento == -1 (abajo)
  {
    pos_actual -= MOMENTO_INC;
  }

  float equivVel = -pos_actual*PELOTA_1J_INF_VELOCIDAD_INC/PAD_1J_INF_MEDIO;

  yVel = yVel + equivVel;

  if(yVel > PELOTA_1J_INF_VELOCIDAD_MAX)
  {
    yVel = PELOTA_1J_INF_VELOCIDAD_MAX;
  }
  else if(yVel < -PELOTA_1J_INF_VELOCIDAD_MAX)
  {
    yVel = -PELOTA_1J_INF_VELOCIDAD_MAX;
  }

  float vel = sqrt(PELOTA_1J_INF_VELOCIDAD*PELOTA_1J_INF_VELOCIDAD - yVel*yVel);

  if(xVel > 0)
  {
    xVel = -vel;
  }
  else
  {
    xVel = vel;
  }
}

int getPos_1j_inf(SDL_Rect pelota, SDL_Rect pad)
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
