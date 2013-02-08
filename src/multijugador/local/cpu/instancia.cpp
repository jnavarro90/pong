#include "instancia.h"

#include "../../../temporizador.h"

using namespace std;

const int FRAMES_PER_SECOND = 60;

CInstance_MJ_CPU::CInstance_MJ_CPU()
{
  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;

  fondo = NULL;
  i_running = true;

  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;
}

CInstance_MJ_CPU::~CInstance_MJ_CPU()
{
  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;

  fondo = NULL;
  i_running = false;
}

bool CInstance_MJ_CPU::Init()
{
  if(!LoadFiles())
    return false;

  i_running = true;

  PJ1 = new CPad_MJ_Local(false, SDLK_w, SDLK_s);
  PJ2 = new CPad_CPU;

  pelota = new CPelota_CPU();
  marcador = new CMarcador(ttf_bitM, &color_blanco);

  return true;
}

bool CInstance_MJ_CPU::LoadFiles()
{
  fondo = cargar_img("media/img/fondo_mj_local.png", false);

  if(fondo == NULL)
  {
    cerr << ERROR_STR_FILE << "media/img/fondo_mj_local.png" << endl;
    return false;
  }

  ttf_bitM = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);

  if(ttf_bitM == NULL)
  {
    cerr << ERROR_STR_FILE << "media/ttf/bit.ttf" << endl;
    return false;
  }

  return true;
}

void CInstance_MJ_CPU::Close()
{
  UnLoadFiles();

  i_running = false;
  fondo = NULL;

  delete PJ1;
  delete PJ2;

  delete pelota;
  delete marcador;
}


void CInstance_MJ_CPU::UnLoadFiles()
{
  SDL_FreeSurface(fondo);
  TTF_CloseFont(ttf_bitM);
}

int CInstance_MJ_CPU::OnExecute()
{
  if(!Init())
  {
    cerr << ERROR_STR_INIT << "MJ_CPU" << endl;
    return I_SALIDA;
  }

  int frame = 0;
  CTemporizador fps;

  int salida = I_MENU_MJ;

  pelota->empezar();

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent();
      if(event.type == SDL_QUIT)
      {
        i_running = false;
        salida = I_SALIDA;
      }
    }
    OnLoop();
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }
  Close();

  return salida;
}

void CInstance_MJ_CPU::OnEvent()
{
  PJ1->eventuar();
  if(event.type == SDL_KEYDOWN)
  {
    if(event.key.keysym.sym == SDLK_RETURN)
    {
      pelota->empezar();
    }
    else if(event.key.keysym.sym == SDLK_ESCAPE)
    {
      i_running = false;
    }
  }
}

void CInstance_MJ_CPU::OnLoop()
{
  int partido = 0;

  partido = pelota->mover(*PJ1, *PJ2);

  PJ1->mover();
  PJ2->mover(*pelota);

  if(partido == 1)
  {
    marcador->incM1();
  }
  else if(partido == 2)
  {
    marcador->incM2();
  }
}

void CInstance_MJ_CPU::OnRender()
{
  aplicar_superficie(0, 0, fondo, pantalla);

  PJ1->mostrar();
  PJ2->mostrar();
  pelota->mostrar();
  marcador->mostrar();

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}
