#include "pad_cpu.h"
#include "../vars.h"

CPad_CPU::CPad_CPU()
{
  wait = false;
  calcular = true;

  caja.x = PAD_OFFSETJ2;
  caja.y = PANTALLA_ALTO/2 - PAD_ALTO/2;
  caja.w = PAD_ANCHO;
  caja.h = PAD_ALTO;

  yVel = PAD_VELOCIDAD;
  momento = 0;
}

CPad_CPU::~CPad_CPU()
{
  wait = false;
  calcular = false;

  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;

  yVel = 0;
  momento = 0;
}

void CPad_CPU::mostrar()
{
  aplicar_superficie(caja.x, caja.y, img_Pad, pantalla);
}

void CPad_CPU::mover(CPelota_CPU P)
{
  // Primero, hallamos dónde impactará la pelota.
  static int y;
  float m;

  if(P.getxVel() > 0)
  {
	if(calcular)
	{
      m = pendiente(P.getX(), P.getY(), P.getX()+P.getxVel(), P.getY()+P.getyVel());
      y = calcPos(m, PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - PELOTA_ANCHO, P.getX(), P.getY());
  	  //cout << "X:" << PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - PELOTA_ANCHO << " M: " << m << " Pos y; " << y << endl;

  	  cout << PANTALLA_ANCHO - PANTALLA_MARGEN_INFERIOR << endl;
  	  while(y < PANTALLA_MARGEN_SUPERIOR || y > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
	  {
	    if(y < PANTALLA_MARGEN_SUPERIOR)
        {
	      y = -y  + PANTALLA_MARGEN_SUPERIOR*2;
	    }
	    else
	    {
	      y = PANTALLA_ALTO - (y - PANTALLA_ALTO) - (PANTALLA_MARGEN_INFERIOR*2);
	    }
	  }
	}
	if(y % 2 != 0) // Dado que los pads se mueven a una cierta velocidad, para evitar "vibraciones", hacemos que la posición sea múltiplo de la velocidad del pad
      y += 1;

	calcular = false;

	if(caja.y + caja.h/2 < y)
	{
	  caja.y += yVel;
	  if(caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_SUPERIOR)
	  {
	    caja.y -= yVel;
	  }
    }
    else if(caja.y + caja.h/2 > y)
    {
      caja.y -= yVel;
      if(caja.y < PANTALLA_MARGEN_INFERIOR)
	  {
	    caja.y += yVel;
      }
    }
	cout << "Caja: " << caja.y + caja.h/2 << endl;
  }
  else if(P.getxVel() < 0)
  {
    calcular = true;
  }
}

float pendiente(float x, float y, float Vx, float Vy)
{
  return (Vy - y)/(Vx - x);
}

int calcPos(float m, float x, float x0, float y0)
{
  // y - y0 = m(x - x0) -> y = m(x - x0) + y0
  return (int) (m*(x - x0) + y0);
}


