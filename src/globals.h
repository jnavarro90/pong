// Includes
#include <string>
#include <sstream>
#include <iostream>

#include "sdl.h"

using namespace std;

//#pragma once

#ifndef GLOBALS_H_
#define GLOBALS_H_

// ___________CONSTANTES_____________
// ----------- PANTALLA -------------
// ----------------------------------

const int PANTALLA_ANCHO = 800;
const int PANTALLA_ALTO = 400;
const int PANTALLA_BPP = 32;

const int PANTALLA_MARGEN_SUPERIOR = 15;
const int PANTALLA_MARGEN_INFERIOR = 15;
const int PANTALLA_MARGEN_LATERAL = 50;

// ___________CONSTANTES_____________
// ------------- PAD ----------------
// ----------------------------------

const int PAD_ANCHO = 20;
const int PAD_ALTO = 80;
const int PAD_MEDIO = PAD_ALTO/2;

const int PAD_OFFSETJ1 = PANTALLA_MARGEN_LATERAL;
const int PAD_OFFSETJ2 = PANTALLA_ANCHO - PANTALLA_MARGEN_LATERAL - PAD_ANCHO;

// ___________CONSTANTES_____________
// ----------- MARCADOR -------------
// ----------------------------------

const int TEXTO_MARCADOR_ANCHO = 160;

// ___________ESTRUCTURAS____________
// ------------ VARIOS --------------
// ----------------------------------
extern SDL_Event event;

extern SDL_Surface* pantalla;
//extern SDL_Surface* imgPelota;
//extern SDL_Surface* imgPad;
//extern SDL_Surface* fondo;
//extern SDL_Surface* txtMarcador;
//extern SDL_Surface* sur_particula;

//xtern SDL_Rect pared;

extern Mix_Chunk* snd_ping;
extern Mix_Chunk* snd_pong;
extern Mix_Chunk* snd_pung;

//extern SDL_Color colorTexto;
//extern TTF_Font* fuente_texto;
//extern TTF_Font* fuente_marcador;

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
