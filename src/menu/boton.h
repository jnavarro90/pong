/**
 * @file
 * @brief Declaración de la clase CBoton
 */

#ifndef BOTON_H_
#define BOTON_H_

#include "../globals.h"
#include <string>

/**
 * @brief Cambiar una estructura SDL_Color a color negro.
 *
 * @param color Estructura de salida
 */
void cambiarNegro(SDL_Color* color);
/**
 * @brief Cambiar una estructura SDL_Color a color blanco.
 *
 * @param color Estructura de salida
 */
void cambiarBlanco(SDL_Color* color);

/**
 *  @brief Enumeración para alinear el texto en los botones
 */
enum align_t { align_derecha = 0, align_centro, align_izquierda };

using namespace std;

/**
 * @brief Clase para representar botones
 *
 * Se utilizará para representar un botón de un determinado tamaño con texto de color cambiante en función de si
 * la entrada del ratón está dentro del marco del botón.
 */
class CBoton
{
  private:
    SDL_Rect caja;/**< Posición y tamaño del botón*/
    string texto;/**< Texto colocado dentro del botón*/

    SDL_Color* color1;/**< Color del texto sin el ratón encima */
    SDL_Color* color2;/**< Color del texto con el ratón encima */
    TTF_Font* ttf_fuente; /**< Fuente con la que se generará el texto */

    align_t align; /**< Alineación del texto*/

    SDL_Surface* srf_texto; /**< Superficie donde se guardará la imagen generada */
  public:
    /**
     * @brief Constructor vacío
     */
    CBoton(){};
    CBoton(TTF_Font* f, SDL_Color* c1, SDL_Color* c2, SDL_Rect* cuadro, const char* texto, enum align_t align = align_izquierda);
    ~CBoton();

    void mostrar();

    bool encima();
};

#endif /* BOTON_H_ */
