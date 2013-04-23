/**
 * @file
 * @brief Declaración de CInstance_Menu_Main
 *
 * Para más información sobre el funcionamiento de las estancias, vea las clases CInstance, CEngine, CMenu y CBoton.
 * Un ejemplo del menú, con un diseño minimalista, es el siguiente:
 *
 * @image html menu_1.png
 */

#ifndef INSTANCE_MENU_H_
#define INSTANCE_MENU_H_

#include "../instance.h"

#include "menu.h"
#include "../temporizador.h"

const int FRAMES_PER_SECOND = 60; /**< Número de frames por segundo para limitar la salida */

/**
 * @brief Clase que representa una estancia del menú principal
 *
 * Para más información sobre el funcionamiento de las estancias, vea las clases CInstance, CEngine, CMenu y CBoton.
 * Un ejemplo del menú, con un diseño minimalista, es el siguiente:
 *
 * @image html menu_1.png
 */
class CInstance_Menu_Main: public CInstance
{
  private:
    bool i_running; /**< ¿Ejecutando esta estancia?*/

    CBoton* botones;/**< Array de botones CBoton para usar en #menu.*/
    CMenu* menu;/**< Clase principal para gestionar el menú.*/

    SDL_Color color_negro;/**< Color base nº1. Ver definiciones de métodos para entender su uso.*/
    SDL_Color color_blanco;/**< Color base nº2.  Ver definiciones de métodos para entender su uso.*/
  public:
    CInstance_Menu_Main();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnLoop(int& caso);
    void OnEvent(int& caso);
    void OnRender();
};




#endif /* INSTANCE_MENU_H_ */
