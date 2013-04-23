/**
 * @file
 * @brief Declaraci�n de la clase CTablero.
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "../globals.h"

/**
 * @brief Clase para dibujar el fondo del modo de cualquier modo multijugador
 *
 * Esta clase se encarga de dibujar y almacenar un fondo de pantalla para los modos de juego multijugador. La construcci�n del fondo
 * se puede apreciar en la funci�n construir().
 */

class CTablero
{
  private:
    SDL_Surface* tablero;/**< Variable para guardar la imagen de fondo.*/
  public:
    CTablero();
    ~CTablero();

    void construir(int16 ancho, int16 alto, int16 bpp, bool menu = false);
    void mostrar();
};

/**
 * @brief Variable global de fondo de pantalla multijugador
 *
 * Iniciado en CEngine::Init() una �nica vez. Se generar� cada vez que se cambie el tama�o de pantalla
 * ( CInstance_MJ_Online_Client::OnExecute() ). Se usar� en las estancias generadas a partir de las clases CInstance_MJ_Online_Client,
 * CInstance_MJ_Online_Server, CInstance_MJ_Local, CInstance_MJ_CPU
 */
extern CTablero* tablero_mp;


#endif /* TABLERO_H_ */
