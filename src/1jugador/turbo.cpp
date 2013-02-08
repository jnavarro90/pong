#include "turbo.h"

#define TURBO_ANCHO 200
#define TURBO_ALTO 150

int TURBO_VEL = 4;
const int FRAMES_PER_SECOND = 60;

void CTurbo::Init()
{
  img = NULL;
  img = cargar_img("media/img/turbo.png", true);
  cout << "img:" << img << endl;
  cheatCount = 0;
  frame = 0;

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

void CTurbo::Close()
{
  UnLoadFiles();

  img = NULL;
}
void CTurbo::UnLoadFiles()
{
  SDL_FreeSurface(img);
}

// Secuencia: m l t v ↑ ↓
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
          cout << "Codigo activado" << endl;
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

void CTurbo::OnRender()
{
  if(running)
  {
    aplicar_superficie(caja.x, caja.y, img, pantalla, clip);
  }
}

void CTurbo::OnExecute()
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
