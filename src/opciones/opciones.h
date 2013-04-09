/*
 * opciones.h
 *
 *  Created on: 05/04/2013
 *      Author: Dani
 */

#ifndef OPCIONES_H_
#define OPCIONES_H_

#include <fstream>
#include <string>
#include "../globals.h"

#define defConf_PANTALLA_ANCHO 800
#define defConf_PANTALLA_ALTO 660
#define defConf_PANTALLA_BPP 32

#define defConf_PJ1_UP SDLK_w
#define defConf_PJ1_DOWN SDLK_s
#define defConf_PJ2_UP SDLK_UP
#define defConf_PJ2_DOWN SDLK_DOWN

#define defConf_PAD_VEL 2.5
#define defConf_PAD_ALTO 80
#define defConf_PAD_ANCHO 20
#define defConf_PAD_COLOR "FFFFFF"

#define defConf_PELOTA_VEL 3.5
#define defConf_PELOTA_ALTO 20
#define defConf_PELOTA_COLOR "FFFFFF"


using namespace std;

class COpciones
{
  public:
    int16 PANTALLA_ANCHO;
    int16 PANTALLA_ALTO;
    int16 PANTALLA_BPP;

    SDLKey PJ1_UP;
    SDLKey PJ1_DOWN;
    SDLKey PJ2_UP;
    SDLKey PJ2_DOWN;

    float PAD_VEL;
    int16 PAD_ALTO;
    int16 PAD_ANCHO;
    float PELOTA_VEL;
    int16 PELOTA_ALTO; // == PELOTA_ANCHO
    int16& PELOTA_ANCHO;

    Uint32 PAD_COLOR;
    Uint32 PELOTA_COLOR;

    COpciones(const char* file);

    void cargarFichero(ifstream& is);
    void crearFicheroDefault(const char* file);
    void cargarDefecto();

    void cargarDato(string id, string valor = "");
};

extern COpciones* opciones;

#endif /* OPCIONES_H_ */
