/**
 * @file
 * @brief Definici�n de CPad_1J_INF
 *
 */

#include "pad_1j_inf.h"
#include "../../globals.h"

float PAD_1J_INF_VELOCIDAD = PAD_VELOCIDAD;
int PAD_1J_INF_ALTO = PAD_ALTO;
int PAD_1J_INF_MEDIO = PAD_ALTO/2;

/**
 * @brief Constructor por defecto
 *
 * Asigna valores por defecto. Si alguna tecla est� pulsada, se a�ade velocidad al pad para desacelerarlo cuando se suelte.
 */
CPad_1J_INF::CPad_1J_INF()
{
  KUp = SDLK_w;
  KDown = SDLK_s;

  yVel = 0;
  if(SDL_GetKeyState(NULL)[KUp])
  {
    yVel -= PAD_1J_INF_VELOCIDAD;
  }
  if(SDL_GetKeyState(NULL)[KDown])
  {
    yVel += PAD_1J_INF_VELOCIDAD;
  }


  caja.w = PAD_ANCHO;
  caja.h = PAD_ALTO;

  caja.y = PANTALLA_ALTO/2 + caja.h/2;
  caja.x = PANTALLA_MARGEN_LATERAL;

  //yVel = PAD_VELOCIDAD;
  //yVel = 0;
  momento = 0;
}

/**
 * @brief Destructor
 *
 * Asigna valores nulos a los miembros de la clase.
 */
CPad_1J_INF::~CPad_1J_INF()
{
  caja.w = 0;
  caja.h = 0;

  caja.y = 0;
  caja.x = 0;

  yVel = 0;
  momento = 0;
}

/**
 * @brief Mover el pad
 *
 * Si el pad tiene velocidad, se aplicar� a la variable caja.y (Rect_Float::y). Adem�s, dependiendo de la velocidad
 * se a�adir� un sentido al momento cin�tico.
 */
void CPad_1J_INF::mover()
{
  if(yVel < 0)
  {
    momento = 1;
  }
  else if(yVel > 0)
  {
	   momento = -1;
  }
  else if(yVel == 0)
  {
	   momento = 0;
  }

  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_SUPERIOR || caja.y + caja.h > PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    caja.y -= yVel;
  }
}

/**
 * @brief Incrementar velocidad
 *
 * Se aumenta el valor de la velocidad. Si el pad est� en movimiento, se tendr� en cuenta para evitar desfases.
 */
void CPad_1J_INF::incVel(float n)
{
  PAD_1J_INF_VELOCIDAD += n;
  // Por si el pad se esta moviendo, decrementamos su velocidad actual
  if(yVel < 0)
  {
    yVel -= n;
  }
  if(yVel > 0)
  {
    yVel += n;
  }
}

/**
 * @brief Decrementar tama�o
 *
 * Se decrementa el tama�o (altura) del pad hasta, como m�nimo, el valor #PAD_1J_INF_MIN_ALTO.
 */
void CPad_1J_INF::decTam(int n)
{
  if(/*n < 0 || */caja.h > PAD_1J_INF_MIN_ALTO)
  {
    // Decrementa el tama�o con respecto al centro.
    caja.y += n/2;
    caja.h -= n;
    PAD_1J_INF_ALTO -= 2*n;
    PAD_1J_INF_MEDIO -= n;
  }
}

/**
 * @brief Gestionar eventos
 *
 * Si se pulsa la tecla para subir el pad, se restar� a yVel el valor #PAD_1J_INF_VELOCIDAD. Si se suelta, se sumar� dicho valor.
 * En caso de pulsar la tecla para bajar, se sumar� si se aprieta la tecla y se restar� si se suelta.
 * Para entender las direcciones, vea el siguiente diagrama de representaci�n de ejes en SDL:
 *
 * <pre>
 *   ________ X
 *  |
 *  |
 *  |
 *  |
 *  Y
 * </pre>
 */
void CPad_1J_INF::eventuar()
{
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == KUp)
      yVel -= PAD_1J_INF_VELOCIDAD;
    else if(event.key.keysym.sym == KDown)
      yVel += PAD_1J_INF_VELOCIDAD;
  }
  else if(event.type == SDL_KEYUP)
  {
	   if(event.key.keysym.sym == KUp)
	     yVel += PAD_1J_INF_VELOCIDAD;
	   else if(event.key.keysym.sym == KDown)
	     yVel -= PAD_1J_INF_VELOCIDAD;
  }
}
