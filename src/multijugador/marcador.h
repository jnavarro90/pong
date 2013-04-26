/**
 * @file
 * @brief Declaración de CMarcador
 *
 */

#ifndef MARCADOR_H_
#define MARCADOR_H_

#include "../globals.h"
#include "../opciones/opciones.h"

/** @brief Offset del texto */
extern const int MARCADOR_OFFSET;
/** @brief Offset vertical de los marcadores */
extern const int MARCADOR_Y;
/** @brief Offset para arreglar desajustes*/
extern const int MARCADOR_OFFSET_FIX;
/** @brief Offset horizontal del marcador del jugador 1 */
extern int MARCADOR_OFFSET_J1;
/** @brief Offset horizontal del marcador del jugador 2 */
extern int MARCADOR_OFFSET_J2;

using namespace std;

/**
 * @brief Clase para representar un marcador.
 *
 * La clase almacenará el valor de los marcadores y 2 superficies para guardar el texto de los marcadores.
 */
class CMarcador
{
  protected:
    int marca1; /**< Número de puntos del jugador 1 */
    int marca2; /**< Número de puntos del jugador 2 */
    SDL_Surface* srf_marca1; /**< Texto del marcador del jugador 1 */
    SDL_Surface* srf_marca2; /**< Texto del marcador del jugador 2 */
    TTF_Font* ttf_fuente; /** Fuente para dibujar el texto guardado en srf_marca1 y srf_marca2 */
    SDL_Color* color; /** Color para dibujar el texto guardado en srf_marca1 y srf_marca2 */

  public:
    CMarcador(TTF_Font* fuente, SDL_Color* c);
    /**
     * @brief Constructor vacío
     */
    CMarcador(){};
    ~CMarcador();

    //void refrescar();
    void reset();
    void mostrar();

    void incM1();
    void incM2();

    /**
     * @brief Obtener marca del jugador 1
     *
     * @return Devuelve el valor almacenado por #marca1
     */
    int getM1(){return marca1;}
    /**
     * @brief Obtener marca del jugador 2
     *
     * @return Devuelve el valor almacenado por #marca2
     */
    int getM2(){return marca2;}
};

#endif /* MARCADOR_H_ */
