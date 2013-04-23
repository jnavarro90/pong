/**
 * @file
 * @brief Declaración de la clase COpciones.
 */

#ifndef OPCIONES_H_
#define OPCIONES_H_

#include <fstream>
#include <string>
#include "../globals.h"

#define defConf_PANTALLA_ANCHO 800 /**< Valor por defecto del ancho de la #pantalla para COpciones::PANTALLA_ANCHO*/
#define defConf_PANTALLA_ALTO 660 /**< Valor por defecto del alto de la #pantalla para COpciones::PANTALLA_ALTO*/
#define defConf_PANTALLA_BPP 32 /**< Valor por defecto de los bits por píxel de la #pantalla para COpciones::PANTALLA_BPP*/
#define defConf_PANTALLA_COMPLETA false /**< Valor por defecto de la opción de #pantalla completa para COpciones::PANTALLA_COMPLETA*/

#define defConf_PJ1_UP SDLK_w /**< Valor por defecto de la tecla para mover arriba del jugador 1 para COpciones::PJ1_UP. No implementado.*/
#define defConf_PJ1_DOWN SDLK_s /**< Valor por defecto de la tecla para mover abajo del jugador 1 para COpciones::PJ1_DOWN. No implementado.*/
#define defConf_PJ2_UP SDLK_UP /**< Valor por defecto de la tecla para mover arriba del jugador 2 para COpciones::PJ2_UP. No implementado.*/
#define defConf_PJ2_DOWN SDLK_DOWN /**< Valor por defecto de la tecla para mover abajo del jugador 2 para COpciones::PJ2_DOWN. No implementado.*/

#define defConf_PAD_VEL 2.5 /**< Valor por defecto de la velocidad de los pads para COpciones::PAD_VEL */
#define defConf_PAD_ALTO 80 /**< Valor por defecto de la altura de los pads para COpciones::PAD_ALTO */
#define defConf_PAD_ANCHO 20  /**< Valor por defecto del ancho de los pads para COpciones::PAD_ANCHO */
#define defConf_PAD_COLOR "FFFFFF"  /**< Valor por defecto del color de los pads para COpciones::PAD_COLOR */

#define defConf_PELOTA_VEL 3.5 /**< Valor por defecto de la velocidad de la pelota para COpciones::PELOTA_VEL */
#define defConf_PELOTA_ALTO 20 /**< Valor por defecto de la altura de la pelota para COpciones::PELOTA_ALTO */
#define defConf_PELOTA_COLOR "FFFFFF" /**< Valor por defecto del color de la pelota para COpciones::PELOTA_COLOR */

using namespace std;

/**
 * @brief Clase cargar opciones de juego
 *
 * Esta clase se encarga de cargar y mantener los datos de variables que se pueden modificar. Por defecto, el juego
 * cargará las opciones del fichero auto.conf ubicado en el mismo directorio que el ejecutable. El objeto principal
 * de esta clase será #opciones, cargado desde CEngine::Init(). Vea las funciones de esta clase para ver como se hace la carga.
 */

class COpciones
{
  public:
    int16 PANTALLA_ANCHO; /**< Valor del ancho de la #pantalla*/
    int16 PANTALLA_ALTO; /**< Valor del alto de la #pantalla*/
    int16 PANTALLA_BPP; /**< Valor de los bits por píxel de la #pantalla*/
    bool PANTALLA_COMPLETA; /**< Valor de la opción de #pantalla completa*/

    SDLKey PJ1_UP; /**< Valor de la tecla para mover arriba del jugador 1. No implementado.*/
    SDLKey PJ1_DOWN; /**< Valor de la tecla para mover abajo del jugador 1. No implementado.*/
    SDLKey PJ2_UP; /**< Valor de la tecla para mover arriba del jugador 2. No implementado.*/
    SDLKey PJ2_DOWN; /**< Valor de la tecla para mover abajo del jugador 2. No implementado.*/

    float PAD_VEL; /**< Valor de la velocidad de los pads */
    int16 PAD_ALTO; /**< Valor de la altura de los pads */
    int16 PAD_ANCHO;  /**< Valor del ancho de los pads */
    Uint32 PAD_COLOR; /**< Valor del color de los pads */

    float PELOTA_VEL; /**< Valor de la velocidad de la pelota */
    int16 PELOTA_ALTO; /**< Valor de la altura de la pelota */
    int16& PELOTA_ANCHO; /**< Valor del ancho de la pelota. Es un equivalente a #PELOTA_ANCHO */
    Uint32 PELOTA_COLOR;

    COpciones(const char* file);

    void cargarFichero(ifstream& is);
    void crearFicheroDefault(const char* file);
    void cargarDefecto();

    void cargarDato(string id, string valor = "");
};

extern COpciones* opciones; /**< Variable global de opciones. Cargada desde CEngine::OnExecute() a partir del fichero auto.conf */

#endif /* OPCIONES_H_ */
