/** @file
 * @brief Definición de la clase CTemporizador
 * */


#include "temporizador.h"
/**
 * @brief Constructor por defecto
 *
 * Asigna valores por defecto. Pone el temporizador como no #pausado y como no #empezado.
 *
 */
CTemporizador::CTemporizador()
{
  empezadoTicks = 0;
  pausadoTicks = 0;

  pausado = false;
  empezado = false;
}

/**
 * @brief Empieza el temporizador
 *
 * Activa el flag de #empezado y desactiva el flag de #pausado. Se le asigna a #empezadoTicks el momento actual en el que se ha empezado.
 *
 */
void CTemporizador::empezar()
{
  empezado = true;
  pausado = false;

  empezadoTicks = SDL_GetTicks();
}

/**
 * @brief Para el temporizador
 *
 * Desactiva el flag de #empezado y desactiva el flag de #pausado. Así, el temporizador queda parado.
 *
 */
void CTemporizador::parar()
{
  empezado = false;
  pausado = false;
}

/**
 * @brief Obtener el número de milisegundos desde que empezó el contador
 *
 * Calcula el tiempo en milisegundos que el contador lleva corriendo.
 *
 * @return Si el temporizador no ha empezado, devuelve 0. Si hay empezado y está pausado, devuelve el último instante cuando se pausó.
 * Si no está pausado, devuelve el nº de milisegundos que lleva corriendo el temporizador (SDL_GetTicks() - #empezadoTicks).
 * Para pasar a segundos, basta con dividir el valor entre 1000.f
 *
 */
int CTemporizador::getTicks()
{
  if(empezado)
  {
    if(pausado)
      return pausadoTicks;
    else
      return SDL_GetTicks() - empezadoTicks;
  }

  return 0;
}

/**
 * @brief Pausar el temporizador
 *
 * Activa el flag de #pausado en caso de que el temporizador esté corriendo. Además, asigna a #pausadoTicks el tiempo que lleva
 * corriendo el temporizador en milisegundos.
 */
void CTemporizador::pausar()
{
  if(empezado && !pausado)
  {
    pausado = true;
    pausadoTicks = SDL_GetTicks() - empezadoTicks;
  }
}

/**
 * @brief Reanuda el temporizador
 *
 * En caso de que el temporizador esté pausado, desactiva el flag #pausado y hace que el momento en el que empezó el
 * temporizador sea el momento actual menos el tiempo que haya estado pausado.
 */
void CTemporizador::resumir()
{
  if(pausado)
  {
    pausado = false;
    empezadoTicks = SDL_GetTicks() - pausadoTicks;

    pausadoTicks = 0;
  }
}

/**
 * @brief Pausado?
 *
 * @return Devuelve el valor guardado en #pausado para saber si el temporizador está pausado o no.
 */
bool CTemporizador::Pausado()
{
  return pausado;
}

/**
 * @brief Empezado?
 *
 * @return Devuelve el valor guardado en #empezado para saber si el temporizador ha empezado o no.
 */
bool CTemporizador::Empezado()
{
  return empezado;
}
