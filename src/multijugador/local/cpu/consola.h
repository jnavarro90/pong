#ifndef CONSOLA_H_
#define CONSOLA_H_

#include "globals.h"

const int CPU_ANCHO = 20;
const int CPU_ALTO = 80;
//const int CPU_VELOCIDAD = 3;
// Al trabajar con flotantes, podemos obtener velocidades mejores.
const float CPU_VELOCIDAD = 2.5;
const int CPU_OFFSET = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - PAD_ANCHO;

class CConsola
{
  private:
    CPelota* pelota_track;
    SDL_Rect caja;
    //int yVel;
    float yVel;
    float x,y;
  public:
    CConsola(CPelota &pelota);

    SDL_Rect& getCaja(){return caja;};

    void mover();
    void mostrar();
};

CConsola::CConsola(CPelota &pelota)
{
  pelota_track = &pelota;

  caja.x = CPU_OFFSET;
  caja.y = PANTALLA_ALTO/2 - CPU_ALTO/2;

  x = (float)caja.x;
  y = (float)caja.y;

  caja.h = CPU_ALTO;
  caja.w = CPU_ANCHO;

  yVel = CPU_VELOCIDAD;
}

void CConsola::mover()
{
  // Si la pelota está parada o bloqueada, ni te muevas.
  if(pelota_track->getLock() || pelota_track->getStop())
    return;

  // Si está muy lejos del centro del pad, sube
  if(caja.y >= pelota_track->getCaja().y + pelota_track->getCaja().h/2)
  {
    //yVel = -CPU_VELOCIDAD;
    yVel = -CPU_VELOCIDAD;
    y += yVel;
    //caja.y += yVel;
    caja.y = (int)y;
  }
  // Si está muy abajo, baja
  else if( caja.y + caja.h/2 <= pelota_track->getCaja().y)
  {
    //yVel = CPU_VELOCIDAD;
    yVel = CPU_VELOCIDAD;
    y += yVel;
    //caja.y += yVel;
    caja.y = (int)y;
  }
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    y -= yVel;
    //caja.y -= yVel;
    caja.y = (int)y;
  }
}

void CConsola::mostrar()
{
  aplicar_superficie(caja.x, caja.y, imgPad, pantalla);
}


#endif /* CONSOLA_H_ */
