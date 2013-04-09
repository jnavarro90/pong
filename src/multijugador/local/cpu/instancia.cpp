#include "instancia.h"

#include "../../../temporizador.h"

using namespace std;

const int FRAMES_PER_SECOND = 60;

// Juego hasta que uno llegue a GAMESET_COUNT. Posiblemente modificable por el usuario
int GAMESET_COUNT = 5;
const int iTimeGameset = 5;
const int iTimeGamepoint = 3;

CInstance_MJ_CPU::CInstance_MJ_CPU()
{
  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;
  wrGameset = NULL;
  wrGamepoint = NULL;

  fondo = NULL;
  i_running = true;

  color_blanco.r = color_blanco.g = color_blanco.b = 0xFF;
  color_rojo.r = 0xFF;
  color_rojo.g = color_rojo.b = 0x00;
}

CInstance_MJ_CPU::~CInstance_MJ_CPU()
{
  PJ1 = NULL;
  PJ2 = NULL;
  pelota = NULL;
  marcador = NULL;
  wrGameset = NULL;
  wrGamepoint = NULL;

  fondo = NULL;
}

bool CInstance_MJ_CPU::Init()
{
  if(!LoadFiles())
    return false;

  i_running = true;
  gameset = gamepoint = false;

  PJ1 = new CPad_MJ_Local(false, SDLK_w, SDLK_s);
  PJ2 = new CPad_MJ_CPU;

  pelota = new CPelota_MJ_CPU();
  marcador = new CMarcador(ttf_bitM, &color_blanco);

  if(rand()%2 == 0)
    gamepoint_pj = gamepoint_pj1;
  else
    gamepoint_pj = gamepoint_pj2;

  wrGameset = new CWarning(ttf_consolas, "¡Juego terminado!", &color_rojo);
  wrGamepoint = new CWarning(ttf_consolas, "+1", &color_rojo);

  return true;
}

bool CInstance_MJ_CPU::LoadFiles()
{
  /*fondo = cargar_img("media/img/fondo_mj_local.png", false);

  if(fondo == NULL)
  {
    cout << ERROR_STR_FILE << "media/img/fondo_mj_local.png" << endl;
    return false;
  }*/

  ttf_bitM = TTF_OpenFont("media/ttf/bit.ttf", TEXTO_MARCADOR_ANCHO);
  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 36);

  if(ttf_bitM == NULL)
  {
    cout << ERROR_STR_FILE << "media/ttf/bit.ttf" << endl;
    return false;
  }
  if(ttf_consolas == NULL)
  {
    cout << ERROR_STR_FILE << "media/ttf/consolab.ttf" << endl;
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

  delete wrGameset;
  delete wrGamepoint;
}


void CInstance_MJ_CPU::UnLoadFiles()
{
  //SDL_FreeSurface(fondo);
  TTF_CloseFont(ttf_bitM);
  TTF_CloseFont(ttf_consolas);
}

int CInstance_MJ_CPU::OnExecute()
{
  if(!Init())
  {
    cout << ERROR_STR_INIT << "MJ_CPU" << endl;
    return I_SALIDA;
  }

  int frame = 0;
  CTemporizador fps;

  int salida = I_MENU_MJ;

  pelota->empezar(gamepoint_pj);

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

#ifdef DEBUG
    OnDebug();
#endif

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
    if(event.key.keysym.sym == SDLK_ESCAPE)
    {
      i_running = false;
    }
    #ifdef DEBUG
    else if(event.key.keysym.sym == SDLK_RETURN)
    {
      gamepoint_pj_t gp = gamepoint_pj2;
      if(rand()%2 == 0)
        gp = gamepoint_pj1;
      pelota->empezar(gp);
    }
    #endif
  }
}

void CInstance_MJ_CPU::OnLoop()
{
  PJ1->mover();
  PJ2->mover(*pelota);

  if(gameset)
  {
    if(gameset_timer.getTicks() >= iTimeGameset*1000.f)
    {
      gameset_timer.parar();
      i_running = false;
    }
    return;
  }
  else if(gamepoint)
  {
    if(gamepoint_timer.getTicks() >= iTimeGamepoint*1000.f)
    {
      gamepoint = false;
      // hacer que la pelota empiece hacia el lado contrario del que marco punto (usar un enum o algo)
      pelota->empezar(gamepoint_pj);
    }
  }

  int partido = pelota->mover(*PJ1, *PJ2);

  if(partido == 1)
  {
    marcador->incM1();

    gamepoint = true;
    gamepoint_pj = gamepoint_pj1;
    gamepoint_timer.empezar();
    gamepoint_offset_x = opciones->PANTALLA_ANCHO/2 - 55;
    if(marcador->getM1() >= GAMESET_COUNT)
    {
      gameset = true;
      gameset_timer.empezar();
    }
  }
  else if(partido == 2)
  {
    marcador->incM2();

    gamepoint = true;
    gamepoint_pj = gamepoint_pj2;
    gamepoint_timer.empezar();
    gamepoint_offset_x = opciones->PANTALLA_ANCHO/2 + 10;
    if(marcador->getM2() >= GAMESET_COUNT)
    {
      gameset = true;
      gameset_timer.empezar();
    }
  }
}

void CInstance_MJ_CPU::OnRender()
{
  //aplicar_superficie(0, 0, fondo, pantalla);
  tablero_mp->mostrar();

  PJ1->mostrar();
  PJ2->mostrar();
  pelota->mostrar();
  marcador->mostrar();

  if(gameset)
  {
    wrGameset->mostrar_ch(opciones->PANTALLA_ALTO/2+20);
  }
  if(gamepoint)
  {
    wrGamepoint->mostrar_cv(gamepoint_offset_x);
  }

  if(SDL_Flip(pantalla) == -1)
  {
    cout << ERROR_STR_FLIP << endl;
    i_running = false;
  }
}

#ifdef DEBUG
void CInstance_MJ_CPU::OnDebug()
{
  gotoxy(0,0);
  cout << "ENTIDAD\tPOS.X\tPOS.Y" << endl;
  cout << "PJ1:\t" << PJ1->getCaja().x << "\t" << PJ1->getCaja().y << endl;
  cout << "PJ2:\t" << PJ2->getCaja().x << "\t" << PJ2->getCaja().y << endl;
  cout << "PELOTA:\t" << pelota->getCaja().x << "\t" << pelota->getCaja().y << endl;
}
#endif
