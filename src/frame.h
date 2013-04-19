/**
 * @file
 * @brief Declara la clase CFrame
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "globals.h"
#include "entidad.h"

/**
 * @brief Clase para dibujar marcos
 *
 * Esta clase se encarga de crear una superficie en forma de "marco", con un color de fondo, un color de marco y un determinado
 * grosor. La superficie se genera en la llamada al constructor, y se libera cuando se destruye el objeto.
 *
 */

class CFrame
{
  private:
    //SDL_Rect caja;  /**< Útil para saber la posición de dibujado en la pantalla. */
    SDL_Surface* srf_frame;  /**< Superficie para guardar el marco generado. */
  public:
    CFrame(int widht, int height, int grosor, Uint32 color_marco, Uint32 color_fondo);
    ~CFrame();

    void combinar(int x, int y, SDL_Surface* salida);
    void mostrar(int x, int y);
};


#endif /* FRAME_H_ */
