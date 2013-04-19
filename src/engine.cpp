/**
 * @file
 * @brief Define la clase CEngine
 */

#include <time.h>

#include "engine.h"

#include "opciones/opciones.h"
#include "opciones/tablero.h"

#include "menu/instance_menu.h"
#include "menu/submenu/instance_menu_mj.h"
#include "menu/submenu/instance_menu_1j.h"

#include "1jugador/infinito/instancia.h"

#include "multijugador/local/instancia.h"
#include "multijugador/online/instancia.h"
#include "multijugador/local/cpu/instancia.h"
/**
 * @brief Constructor por defecto
 *
 * Asigna valores por defecto o punteros nulos.
 */

CEngine::CEngine()
{
  pantalla = NULL;

  running = true;
}

/**
 * @brief Destructor por defecto
 *
 * Asigna valores por defecto o punteros nulos.
 */

CEngine::~CEngine()
{
  pantalla = NULL;

  running = false;
}

/**
 * @brief Inicializador del motor
 *
 * Inicia las librerias de SDL, tanto TTF como Mixer. Carga archivos de uso global y genera
 * las superficies de pantalla (SDL_Surface* pantalla), además de sus atributos.
 *
 * @return Devuelve false si ha fallado algo. Devuelve true si todo ha sido cargado correctamente.
 */

bool CEngine::Init()
{
  srand (time(NULL));

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return false;

  if(TTF_Init() == -1)
    return false;

  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1)
    return false;

  if(!LoadFiles())
    return false;

  opciones = new COpciones("auto.conf");
  tablero_mp = new CTablero;
  tablero_mp->construir(opciones->PANTALLA_ANCHO, opciones->PANTALLA_ALTO, opciones->PANTALLA_BPP);

  SDL_Surface* srf = cargar_img("media/img/icono.tga", true);
  SDL_WM_SetIcon(srf, NULL);

  if(!initPantalla())
    return false;

  SDL_WM_SetCaption( "Pong++", "Pong++" );
  color_blanco = SDL_MapRGB(pantalla->format, 255, 255, 255);

  return true;
}

/**
 * @brief Carga archivos de uso global (principalmente, sonidos).
 *
 * @return Devuelve false si ha fallado algo. Devuelve true si todo ha sido cargado correctamente.
 */

bool CEngine::LoadFiles()
{
  snd_pong = Mix_LoadWAV("media/snd/pong.wav");
  snd_ping = Mix_LoadWAV("media/snd/ping.wav");
  snd_pung = Mix_LoadWAV("media/snd/pung.wav");

  if(snd_pong == NULL || snd_ping == NULL || snd_pung == NULL)
    return false;

  return true;
}

/**
 * @brief Cierra/Descarga el motor del juego
 *
 * Desactiva y descarga todo lo realizado en la función Init()
 */

void CEngine::Close()
{
  UnLoadFiles();
  //closePantalla(); // no necesario

  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();

  delete opciones;
  delete tablero_mp;
}

/**
 * @brief Descarga los ficheros.
 *
 * Descarga todo lo cargado desde la función LoadFiles()
 */

void CEngine::UnLoadFiles()
{
  Mix_FreeChunk(snd_pong);
  Mix_FreeChunk(snd_ping);
  Mix_FreeChunk(snd_pung);
}

/**
 * @brief Función de ejecucion principal
 *
 * La función se encarga de ejecutar el bucle principal del juego, desde el cual se cargarán las
 * diversas estancias. La estructura es bastante sencilla:
 *
 * @code
 * int CEngine::OnExecute()
 * {
 *   if(!Init())
 *     return -1;
 *
 *   int menu = I_MENU_MAIN;
 *
 *   while(running)
 *   {
 *     if(menu == I_SALIDA)
 *     {
 *       running = false;
 *     }
 *     else
 *     {
 *       menu = instance[menu]->OnExecute();
 *     }
 *   }
 *   Close();
 *   return menu;
 * }
 * @endcode
 *
 * Ademas, las declaraciones del contenido del array de punteros instance se hacen en esta propia función.
 *
 * @return En caso de fallo, devuelve I_SALIDA (-1). En caso de finalizar correctamente, devuelve la
 * última estancia llamada por las funciones de CInstance::OnExecute() correspondiente.
 *
 *
 */

int CEngine::OnExecute()
{
  if(!Init())
  {
    cout << ERROR_STR_INIT << " ENGINE" << endl;
    return -1;
  }

  CInstance_Menu_Main i_menu;
  CInstance_Menu_1J i_menu_1j;
  CInstance_Menu_MJ i_menu_mj;
  instance[I_MENU_MAIN] = &i_menu;
  instance[I_MENU_1J] = &i_menu_1j;
  instance[I_MENU_MJ] = &i_menu_mj;

  CInstance_1J_INF i_1j_inf;
  instance[I_1J_INF] = &i_1j_inf;

  CInstance_Menu_MJ_Online i_mj_online;
  CInstance_MJ_Local i_mj_local;
  CInstance_MJ_CPU i_mj_cpu;
  CInstance_MJ_Online_Client i_mj_online_client;
  CInstance_MJ_Online_Server i_mj_online_server;
  instance[I_MJ_ONLINE] = &i_mj_online;
  instance[I_MJ_LOCAL] = &i_mj_local;
  instance[I_MJ_CPU] = &i_mj_cpu;
  instance[I_MJ_ONLINE_CLIENT] = &i_mj_online_client;
  instance[I_MJ_ONLINE_SERVER] = &i_mj_online_server;

  int menu = I_MENU_MAIN;

  while(running)
  {
    if(menu == I_SALIDA)
    {
      running = false;
    }
    else
    {
      #ifdef DEBUG
      system("CLS");
      #endif
      menu = instance[menu]->OnExecute();
    }
  }
  Close();

  return menu;
}
