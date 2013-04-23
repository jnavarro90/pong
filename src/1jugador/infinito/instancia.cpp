/**
 * @file
 * @brief Definición de CInstance_1J_INF
 *
 */

#include "instancia.h"

#include "../../temporizador.h"

using namespace std;

const int FRAMES_PER_SECOND = 60;

CInstance_1J_INF::CInstance_1J_INF()
{
  PJ1 = NULL;
  pelota = NULL;

  tMarca = NULL;
  marca = NULL;

  fondo = NULL;
  i_running = true;
}

bool CInstance_1J_INF::Init()
{
  if(!LoadFiles())
    return false;

  i_running = true;
  fin = false;
  incVel = false;
  decTam = false;

  PJ1 = new CPad_1J_INF();
  pelota = new CPelota_1J_INF();
  turbo = new CTurbo;

  tMarca = new CTemporizador;

  turbo->Init();

  return true;
}

bool CInstance_1J_INF::LoadFiles()
{
  fondo = cargar_img("media/img/fondo_1j_inf.png", false);
  if(fondo == NULL)
  {
    cout << ERROR_STR_FILE << "media/img/fondo_1j_inf.png" << endl;
    return false;
  }

  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);
  if(ttf_consolas == NULL)
  {
    cout << ERROR_STR_FILE << "media/ttf/consolab.ttf" << endl;
    return false;
  }

  return true;
}

void CInstance_1J_INF::Close()
{
  UnLoadFiles();

  i_running = false;
  fondo = NULL;
  fin = false;

  turbo->Close();

  delete PJ1;
  delete pelota;
  delete turbo;

  delete tMarca;
}


void CInstance_1J_INF::UnLoadFiles()
{
  SDL_FreeSurface(fondo);
  TTF_CloseFont(ttf_consolas);
}

int CInstance_1J_INF::OnExecute()
{
  if(!Init())
  {
    cout << ERROR_STR_INIT << " 1J_INF" << endl;
    return I_SALIDA;
  }

  int frame = 0;
  CTemporizador fps;

  int salida = I_MENU_1J;

  pelota->empezar();
  tMarca->empezar();

  while(i_running)
  {
    fps.empezar();
    while(SDL_PollEvent(&event))
    {
      OnEvent(salida);
    }
    OnLoop(salida);
    OnRender();

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }
  Close();

  return salida;
}

void CInstance_1J_INF::OnEvent(int& salida)
{
  PJ1->eventuar();
  turbo->OnEvent();

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
  if(event.type == SDL_QUIT)
  {
    salida = I_SALIDA;
    i_running = false;
  }
}

void CInstance_1J_INF::OnLoop(int& salida)
{
  // enum returns {perder = 0, juego, rebote, rebote_pad};
  static int dificultad = 0;

  // ¿¿¿???
  // Aumentar la velocidad del pad y la pelota cada X rebotes contra la pared
  // Disminuir el tamaño del pad y de la pelota cada Y rebotes contra el pad <- ¿?

  int partido = pelota->mover(*PJ1);
  incVel = decTam = false;
  if(partido == perder)
  {
    if(!fin)
    {
      fin = true;
      tMarca->empezar();
    }
    else
    {
      if(tMarca->getTicks()/1000.f >= 5)
      {
        i_running = false;
        salida = I_1J_INF;
      }
    }
    return;
  }
  else if(partido == rebote)
  {
    dificultad++;
    if(dificultad > 5)
    {
      dificultad = 0;
      pelota->decTam(5);
      PJ1->decTam(10);
    }
  }

  turbo->OnLoop();
  PJ1->mover();
}

void CInstance_1J_INF::OnRender()
{
  aplicar_superficie(0, 0, fondo, pantalla);

  PJ1->mostrar();
  pelota->mostrar();
  turbo->OnRender();

  if(SDL_Flip(pantalla) == -1)
  {
    cerr << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}
