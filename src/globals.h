/**
 * @file
 * @brief Declaración de variables globales y constantes
 */

#include <string>
#include <sstream>
#include <iostream>

#include "sdl.h"

using namespace std;

#ifdef DEBUG
#include <windows.h>
extern void gotoxy(int x, int y);
#endif


typedef char int8;
//typedef char byte;
typedef unsigned char uint8;
typedef short int int16;
typedef unsigned short int uint16;

typedef unsigned int uint;
typedef unsigned char uchar;

typedef unsigned char flags;

//#pragma once

#ifndef GLOBALS_H_
#define GLOBALS_H_

// ____________FUNCIONES_____________
// ------------- TYPE ---------------
// ----------------------------------

ostream& operator<<(ostream& os, flags f);

// _____________DEFINES______________
// -------------- NET ---------------
// ----------------------------------

#define NET_MJ_PORT 8888 /**< @brief Puerto a utilizar en la conexión del modo multijugador-online */

#define NET_MJ_SETTINGS_SIZE 12 /**< @brief Suma de los miembros de CNetwork_Data_Settings*/
#define NET_MJ_SERVERDATA_SIZE 16 /**< @brief Suma de los miembros de CNetwork_Data_Server*/
#define NET_MJ_CLIENTDATA_SIZE 6 /**< @brief Suma de los miembros de CNetwork_Data_Client*/


// _____________DEFINES______________
// ------------ ERRORES -------------
// ----------------------------------

#define ERROR_CODE_GENERAL -1

#define ERROR_STR_NET  "Error iniciano módulo de red."
#define ERROR_STR_FLIP "Error volcando contenido por pantalla."
#define ERROR_STR_INIT "Error iniciando módulo: "
#define ERROR_STR_FILE "Error cargando archivo: "
#define ERROR_STR_SURFACE "Error creando superficie: "

// ___________CONSTANTES_____________
// ----------- PANTALLA -------------
// ----------------------------------

const int PANTALLA_ANCHO = 800;
const int PANTALLA_ALTO = 400;
const int PANTALLA_BPP = 32;

const int PANTALLA_MARGEN_SUPERIOR = 15;
const int PANTALLA_MARGEN_INFERIOR = 15;
const int PANTALLA_MARGEN_LATERAL = 50;

const int TABLERO_LINEAS_GROSOR = 5;

// ___________CONSTANTES_____________
// ------------- PAD ----------------
// ----------------------------------

const int PAD_ANCHO = 20;
const int PAD_ALTO = 80;
const int PAD_MEDIO = PAD_ALTO/2;

//const int PAD_OFFSETJ1 = PANTALLA_MARGEN_LATERAL;
//const int PAD_OFFSETJ2 = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - PAD_ANCHO;

// ___________CONSTANTES_____________
// ----------- MARCADOR -------------
// ----------------------------------

const int TEXTO_MARCADOR_ANCHO = 160;

// _____________ENUMS________________
// ------------ VARIOS --------------
// ----------------------------------

enum INSTANCES
{
  I_SALIDA = -1, I_MENU_MAIN = 0,
  I_MENU_1J, I_MENU_MJ, I_MENU_OPCIONES,
  I_1J_INF, I_1J_HISTORIA,
  I_MJ_LOCAL, I_MJ_CPU, I_MJ_ONLINE, I_MJ_ONLINE_CLIENT, I_MJ_ONLINE_SERVER
};

#define N_INSTANCES 12

//enum instance_list { error = -1, salir = 0, menu_main, menu_1j, menu_mj, menu_mj_online, modo_1j_inf, modo_mj_local, modo_mj_cpu, modo_mj_online_c, modo_mj_online_s, opciones_};

// ___________ESTRUCTURAS____________
// ------------ VARIOS --------------
// ----------------------------------
extern SDL_Event event; /** Estructura para gestionar todos los eventos de entrada del teclado. Se usa en todas las estancias CInstance::OnEvent()*/

/*! Superficie que guardará todo el contenido que se va a mostrar por pantalla en cada frame de la ejecución.
 * Se inicia en CEngine::Init()
 */
extern SDL_Surface* pantalla;
extern bool initPantalla(); /** Inicia la pantalla. Vea la definición para entender el funcionamiento.*/
//extern void closePantalla(); // inutil

extern Mix_Chunk* snd_ping;
extern Mix_Chunk* snd_pong;
extern Mix_Chunk* snd_pung;

//extern Uint32 color_blanco;
//extern SDL_Color color_blanco_t;

extern TTF_Font* ttf_consolas;
extern TTF_Font* ttf_consolasM;
extern TTF_Font* ttf_bitM;

/**
 * @brief Estructura similar a SDL_Rect
 *
 * @code
 *
 * struct Rect_Float
 * {
 *   float x,y;
 *   int w, h;
 * }
 *
 * @endcode
 *
 * En vez de usar enteros para las coordenadas, usamos números en punto flotante.
 * A la hora de representarlos por pantalla, se toman los valores enteros.
 */
struct Rect_Float
{
  float x, y;
  int w, h;
};

// Clases

// Funciones
extern void aplicar_superficie(int x, int y, SDL_Surface* entrada, SDL_Surface* destino, SDL_Rect* clip = NULL);

extern SDL_Surface* cargar_img(std::string s, bool alphapng = false);

#endif /* GLOBALS_H_ */
