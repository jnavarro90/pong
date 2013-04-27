/**
 * @file
 * @brief Definicion de CTurbo
 */

#include "turbo.h"

#define TURBO_ANCHO 200
#define TURBO_ALTO 150

int TURBO_VEL = 4;
const int FRAMES_PER_SECOND = 60;

/**
 * @brief Iniciador
 *
 * Carga la imagen de turbo en #img y asigna valores por defecto, definidos por el usuario.
 */
void CTurbo::Init()
{
  img = NULL;
  img = cargar_img("media/img/turbo.png", true);

  cheatCount = 0;
  frame = 0;

  running = false;

  caja.w = TURBO_ANCHO;
  caja.h = TURBO_ALTO;
  caja.x = -TURBO_ANCHO;
  caja.y = PANTALLA_ALTO/2 - TURBO_ALTO/2;

  for(int i = 0; i < 4; i++)
  {
    clips[i].w = TURBO_ANCHO;
    clips[i].h = TURBO_ALTO;
  }

  clips[0].x = 0;
  clips[0].y = 0;
  clips[1].x = TURBO_ANCHO;
  clips[1].y = 0;
  clips[2].x = 0;
  clips[2].y = TURBO_ALTO;
  clips[3].x = TURBO_ANCHO;
  clips[3].y = TURBO_ALTO;

  clip = &clips[1];
}

/**
 * @brief Desiniciador
 *
 * Descaga archivos y asigna valores nulos.
 */
void CTurbo::Close()
{
  UnLoadFiles();

  img = NULL;
}

/**
 * @brief Descargador de archivos
 *
 * Descaga archivos de memoria. En esta caso, el contenido de la variable #img.
 */
void CTurbo::UnLoadFiles()
{
  SDL_FreeSurface(img);
}

/**
 * @brief Eventuar
 *
 * Comprueba el registro de eventos de la variable global #event para verificar si se ha introducido correctamente la secuencia.
 * Se inicia un contador (#cheatCount) a 0. Cada vez que se pulsa una tecla de la secuencia, se aumenta el contador en uno.
 * Si el contador ha alcanzado el número de teclas a pulsar, se activará el objeto de esta clase, cambiando la variable
 * #running a true. Si, a mitad de la secuencia se introduce una tecla errónea, se restablece el contador a 0. Actualmente,
 * la secuencia es: M L T V ↑ ↓
 */
void CTurbo::OnEvent()
{
  if(event.type == SDL_KEYDOWN && !running)
  {
    switch(cheatCount)
    {
      case 0:
        if(event.key.keysym.sym == SDLK_m)
        {
          cheatCount++;
        }
        else
        {
          cheatCount = 0;
        }
      break;
      case 1:
        if(event.key.keysym.sym == SDLK_l)
        {
          cheatCount++;
        }
        else
        {
          cheatCount = 0;
        }
      break;
      case 2:
        if(event.key.keysym.sym == SDLK_t)
        {
          cheatCount++;
        }
        else
        {
          cheatCount = 0;
        }
      break;
      case 3:
        if(event.key.keysym.sym == SDLK_v)
        {
          cheatCount++;
        }
        else
        {
          cheatCount = 0;
        }
      break;
      case 4:
        if(event.key.keysym.sym == SDLK_UP)
        {
          cheatCount++;
        }
        else
        {
          cheatCount = 0;
        }
      break;
      case 5:
        if(event.key.keysym.sym == SDLK_DOWN)
        {
          cheatCount++;
          running = true;
        }
        else
        {
          cheatCount = 0;
        }
      break;
    }
  }
}
/**
 * @brief Mostrar por #pantalla
 *
 * Si la variable #running está puesta a true, se mostrará por pantalla.
 * Si no, se deberá insertar la secuencia para que aparezca.
 */
void CTurbo::OnRender()
{
  if(running)
  {
    aplicar_superficie(caja.x, caja.y, img, pantalla, clip);
  }
}

/**
 * @brief Gestionar datos
 *
 * Si la variable #running está puesta a true, se tratarán los datos. Se hará que el objeto se mueva
 * de un lado a otro de la pantalla. Cada frame que pase en el programa incrementa la variable #frame y por tanto,
 * se cambia la variable #clip por la correspondiente de #clips. Finalmente, cuando haga todo el recorrido,
 * se desactivará la variable #running y se esperará a volver a insertar la secuencia.
 */
void CTurbo::OnLoop()
{
  if(running)
  {
    caja.x += TURBO_VEL;
    if(TURBO_VEL > 0)
    {
      if(caja.x == PANTALLA_ANCHO/2 - TURBO_ANCHO/2)
      {
        clip = &clips[0];
        frame++;
        if(frame < FRAMES_PER_SECOND + FRAMES_PER_SECOND/2)
        {
          caja.x -= TURBO_VEL;
        }
        else
        {
          frame = 0;
        }
      }
      else
      {
        clip = &clips[1];
      }
      if(caja.x > PANTALLA_ANCHO)
      {
        TURBO_VEL = -TURBO_VEL;
      }
    }
    if(TURBO_VEL < 0)
    {
      if(caja.x == PANTALLA_ANCHO/2 - TURBO_ANCHO/2)
      {
        clip = &clips[2];
        frame++;
        if(frame < FRAMES_PER_SECOND + FRAMES_PER_SECOND/2)
        {
          caja.x -= TURBO_VEL;
        }
        else
        {
          frame = 0;
        }
      }
      else
      {
        clip = &clips[3];
      }
      if(caja.x <= -TURBO_ANCHO)
      {
        TURBO_VEL = -TURBO_VEL;
        running = false;
        cheatCount = 0;
        clip = &clips[1];
      }
    }
  }
}
