/**
 * @file
 * @brief Declaración de CTurbo
 */

#ifndef TURBO_H_
#define TURBO_H_

#include "../globals.h"
#include "../entidad.h"

/**
 * @brief Clase para mostrar por #pantalla un... objeto.
 *
 * Clase de broma para mostrar un elemento por pantalla al escribir una secuencia bastante sencilla.
 * Por el momento, está implementada en CInstance_1J_INF. "Turbo" es el siguiente personaje:
 *
 * @image html turbo_1.png
 */
class CTurbo: public CEntidad
{
  private:
    //SDL_Rect caja;
    SDL_Rect* clip;/**< Clip a usar*/
    SDL_Rect clips[4];/**< Conjunto total de clips*/

    SDL_Surface* img;/**< Superficie para guardar una imagen*/
    bool running;/**< Variable para saber si se está ejecutando*/

    int frame;/**< Mide la cantidad de frames desde que se empezó a ejecutar*/
    int cheatCount;/**< Variable auxiliar para verificar la entrada correcta de la secuencia*/

  public:
    void Init();
      void LoadFiles();
    void Close();
      void UnLoadFiles();

    void OnEvent();
    void OnRender();
    void OnLoop();
};

#endif /* TURBO_H_ */
