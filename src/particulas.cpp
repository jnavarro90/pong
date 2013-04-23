/**
 * @file
 * @brief Definición de CParticula
 *
 */

#include "particulas.h"

CParticula::CParticula(int X, int Y)
{
  x = X;
  y = Y;

  frame = 0;
  //tipo = sur_particula;
}

void CParticula::mostrar()
{
  aplicar_superficie(x, y, tipo, pantalla);
  frame++;
}

bool CParticula::muerta()
{
  if(frame > 20)
    return true;

  return false;
}
