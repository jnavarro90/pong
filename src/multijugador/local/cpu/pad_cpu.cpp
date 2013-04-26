/**
 * @file
 * @brief Definición de CPad_MJ_CPU
 *
 */

#include "pad_cpu.h"

CPad_MJ_CPU::CPad_MJ_CPU():CPad_MJ()
{
  calcular = true;

  //caja.x = PAD_OFFSETJ2;
  caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - opciones->PAD_ANCHO;
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.w = opciones->PAD_ANCHO;
  caja.h = opciones->PAD_ALTO;

  yVel = opciones->PAD_VEL;
  //momento = 0;
}

CPad_MJ_CPU::~CPad_MJ_CPU()
{
  calcular = false;

  caja.x = 0;
  caja.y = 0;
  caja.w = 0;
  caja.h = 0;

  yVel = 0;
  momento = 0;
}

/**
 * @brief Gestionar datos
 *
 * @param P Objeto del tipo CPelota_MJ_CPU para obtener las coordenadas del mismo.
 *
 * El pad debe coger la posición y la velocidad de la pelota para, tras una serie de cálculos,
 * saber dónde impactará la pelota en el rango de alcance del pad de la cpu (por lo general,
 * en el lado derecho). En la siguiente imagen se puede apreciar como se hace el cálculo:
 *
 * @image html cpu_1.png
 */
void CPad_MJ_CPU::mover(CPelota_MJ_CPU& P)
{

  static int y; // Primero, hallamos dónde impactará la pelota.
  float m; // con ayuda de la "pendiente" que lleva la pelota en su traza de movimiento.

  if(P.getxVel() > 0)
  {
	   if(calcular)
	   {
      m = pendiente(P.getX(), P.getY(), P.getX()+P.getxVel(), P.getY()+P.getyVel());
      y = calcPos(m, opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - opciones->PELOTA_ANCHO, P.getX(), P.getY());

   	  while(y < PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR || y > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR )
	     {
	       if(y < PANTALLA_MARGEN_SUPERIOR )
        {
	         y = -y  + PANTALLA_MARGEN_SUPERIOR*2;
	       }
	       else
	       {
	         y = opciones->PANTALLA_ALTO - (y - opciones->PANTALLA_ALTO) - (PANTALLA_MARGEN_INFERIOR*2);
	       }
	     }
	   }
	   calcular = false;

	   if(caja.y + caja.h/2 < y - 2) // evitar vibraciones con un pequeño offset en el centro (-2)
	   {
	     caja.y += yVel;
	     if(caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_SUPERIOR - TABLERO_LINEAS_GROSOR)
	     {
	       caja.y -= yVel;
	     }
    }
    else if(caja.y + caja.h/2 > y + 2) // evitar vibraciones con un pequeño offset en el centro (+2)
    {
      caja.y -= yVel;
      if(caja.y < PANTALLA_MARGEN_INFERIOR + TABLERO_LINEAS_GROSOR)
	     {
	       caja.y += yVel;
      }
    }
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


