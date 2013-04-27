/**
 * @file
 * @brief Definición de CPad_MJ_Online, CPad_MJ_Online_Zombi, CPad_MJ_Online_Client y CPad_MJ_Online_Client_Zombi
 *
 */

#include "pad_mj_online.h"
#include "../../globals.h"

/**
 * @brief Constructor principal
 *
 * @param lado Lado de la pantalla en el que se pondrá el pad
 * @param U Tecla para hacer subir el pad
 * @param D Tecla para hacer bajar el pad
 */
CPad_MJ_Online::CPad_MJ_Online(lado_t lado, SDLKey U, SDLKey D): CPad_MJ()
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;

  KUp = U;
  KDown = D;

  if(SDL_GetKeyState(NULL)[KUp])
  {
    yVel -= opciones->PAD_VEL;
  }
  if(SDL_GetKeyState(NULL)[KDown])
  {
    yVel += opciones->PAD_VEL;
  }
}

/**
 * @brief Destructor
 *
 * Asigna valores nulos
 */
CPad_MJ_Online::~CPad_MJ_Online()
{

  caja.x = caja.y = caja.h = caja.w = 0;
  yVel = momento = 0;
}

/**
 * @brief Gestionar datos de entrada
 */
void CPad_MJ_Online::eventuar()
{
  if(event.type == SDL_KEYDOWN)
  {
	   if(event.key.keysym.sym == KUp)
	   {
	     yVel -= opciones->PAD_VEL;
   	}
   	else if(event.key.keysym.sym == KDown)
	   {
	     yVel += opciones->PAD_VEL;
   	}
  }
  if(event.type == SDL_KEYUP)
  {
   	if(event.key.keysym.sym == KUp)
	   {
	     yVel += opciones->PAD_VEL;
	   }
	   else if(event.key.keysym.sym == KDown)
	   {
	     yVel -= opciones->PAD_VEL;
	   }
  }
}

/**
 * @brief Gestionar datos y mover el pad
 */
void CPad_MJ_Online::mover()
{
  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_SUPERIOR + TABLERO_LINEAS_GROSOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR - TABLERO_LINEAS_GROSOR)
  {
	caja.y -= yVel;
  }
}

/**
 * @brief Constructor principal
 *
 * @param lado Lado de la pantalla en el que se pondrá el pad
 */
CPad_MJ_Online_Zombi::CPad_MJ_Online_Zombi(lado_t lado):CPad_MJ()
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL  - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;
}

/**
 * @brief Destructor
 *
 * Asigna valores nulos
 */
CPad_MJ_Online_Zombi::~CPad_MJ_Online_Zombi()
{
  caja.x = caja.y = caja.w = caja.h = 0;
}

/**
 * @brief Gestionar datos y mover el pad
 *
 * @param mov Entrada del cliente remoto
 *
 * Dependiendo del tipo de movimiento especificado en los parámetros, el pad se moverá hacia arriba, hacia abajo o se queará quieto.
 * Incrementa el valor "y" en #caja y le da el valor oportuno a #momento.
 */
void CPad_MJ_Online_Zombi::mover(int8 mov)
{
  if(mov == arriba)
  {
    yVel = -opciones->PAD_VEL;
    momento = arriba;
  }
  else if(mov == abajo)
  {
   	yVel = opciones->PAD_VEL;
	   momento = abajo;
  }
  else if(mov == quieto)
  {
	   yVel = 0;
	   momento = 0;
  }

  caja.y += yVel;
  if(caja.y < PANTALLA_MARGEN_INFERIOR || caja.y + caja.h > opciones->PANTALLA_ALTO - PANTALLA_MARGEN_INFERIOR)
  {
    caja.y -= yVel;
  }
}

/**
 * @brief Constructor principal
 *
 * @param lado Lado de la pantalla en el que se pondrá el pad
 * @param U Tecla para hacer subir el pad
 * @param D Tecla para hacer bajar el pad
 */
CPad_MJ_Online_Client::CPad_MJ_Online_Client(lado_t lado, SDLKey U, SDLKey D)
{
  // esto funciona (de momento). Cuidado con yVel y momento
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL  - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;
  KUp = U;
  KDown = D;

  yVel = 0;
  momento = 0;
}

/**
 * @brief Gestionar datos de entrada del cliente
 *
 * @param mov Valor para enviar al servidor y que lo procese.
 *
 * Esto se usará en el cliente. Dependiendo de la entrada del teclado especificada en #event,
 * se le dará un valor u otro al parámetro de salida mov.
 */
void CPad_MJ_Online_Client::eventuar(int8& mov)
{
  if(event.type == SDL_KEYDOWN)
  {
   	if(event.key.keysym.sym == KUp)
	   {
	     mov += 1;
	   }
	   else if(event.key.keysym.sym == KDown)
	   {
	     mov -= 1;
	   }
  }
  else if(event.type == SDL_KEYUP)
  {
	   if(event.key.keysym.sym == KUp)
	   {
	     mov -= 1;
	   }
	   else if(event.key.keysym.sym == KDown)
	   {
	     mov += 1;
	   }
  }
}

/**
 * @brief Asignar un valor vertical a la estructura #caja.
 *
 * @param y Nueva coordenada vertical del pad
 */
void CPad_MJ_Online_Client::setY(int y)
{
  caja.y = y;
}


/**
 * @brief Constructor principal
 *
 * @param lado Lado de la pantalla en el que se pondrá el pad
 */
CPad_MJ_Online_Client_Zombi::CPad_MJ_Online_Client_Zombi(lado_t lado)
{
  if(lado == izq)
  {
    caja.x = PANTALLA_MARGEN_LATERAL;
  }
  else if(lado == der)
  {
    caja.x = opciones->PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL  - opciones->PAD_ANCHO;
  }
  caja.y = opciones->PANTALLA_ALTO/2 - opciones->PAD_ALTO/2;
  caja.h = opciones->PAD_ALTO;
  caja.w = opciones->PAD_ANCHO;
}

/**
 * @brief Asignar un valor vertical a la estructura #caja.
 *
 * @param y Nueva coordenada vertical del pad
 */
void CPad_MJ_Online_Client_Zombi::setY(int y)
{
  caja.y = y;
}


