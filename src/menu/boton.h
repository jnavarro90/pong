/**
 * @file
 * @brief Declaraci�n de la clase CBoton
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
 *  @brief Enumeraci�n para alinear el texto en los botones
 */
enum align_t { align_derecha = 0, align_centro, align_izquierda };

using namespace std;

/**
 * @brief Clase para representar botones
 *
 * Se utilizar� para representar un bot�n de un determinado tama�o con texto de color cambiante en funci�n de si
 * la entrada del rat�n est� dentro del marco del bot�n.
 */
class CBoton
{
  private:
    SDL_Rect caja;/**< Posici�n y tama�o del bot�n*/
    string texto;/**< Texto colocado dentro del bot�n*/

    SDL_Color* color1;/**< Color del texto sin el rat�n encima */
    SDL_Color* color2;/**< Color del texto con el rat�n encima */
    TTF_Font* ttf_fuente; /**< Fuente con la que se generar� el texto */

    align_t align; /**< Alineaci�n del texto*/

    SDL_Surface* srf_texto; /**< Superficie donde se guardar� la imagen generada */
  public:
    /**
     * @brief Constructor vac�o
     */
    CBoton(){};
    CBoton(TTF_Font* f, SDL_Color* c1, SDL_Color* c2, SDL_Rect* cuadro, const char* texto, enum align_t align = align_izquierda);
    ~CBoton();

    void mostrar();

    bool encima();
};

#endif /* BOTON_H_ */
