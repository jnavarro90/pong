/** @file
 * @brief Declaración de la clase CWarning
 */

#ifndef WARNING_H_
#define WARNING_H_

#include "globals.h"

using namespace std;

/**
 * @brief Clase para mostrar avisos (texto) por pantalla
 *
 * Esta clase se utiliza para mostrar en la superficie #pantalla un texto deseado almacenado en la variable #str. Se dibujará con
 * el color guardado en #color1 y con la fuente apuntada por #ttf_fuente.
 */
class CWarning
{
  private:
    SDL_Surface* srf_texto;/**< Superficie para guardar el texto generado */
    TTF_Font* ttf_fuente;/**< Tipo de fuente a utilizar previamente cargada */
    SDL_Color color1; /**< Color con el que se dibujará el texto */
    string str; /** Cadena de caracteres que almacenará el texto */
  public:
    CWarning(TTF_Font* fuente, const char* txt, SDL_Color* color);
    ~CWarning();

    void mostrar();
    void mostrar(int x, int y);
    void mostrar_ch(int y);
    void mostrar_cv(int x);
};


#endif /* WARNING_H_ */
