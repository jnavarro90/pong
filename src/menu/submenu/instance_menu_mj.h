/**
 * @file
 * @brief Clase de estancia para el menú multijugador y multijugador online
 *
 * Para más información sobre el funcionamiento de las estancias, vea las clases
 * CInstance_Menu_Main, CInstance, CEngine, CMenu y CBoton.
 * El diseño de este menú, con un diseño minimalista, es el siguiente:
 *
 * @image html menu_1.png
 */

#ifndef INSTANCE_MENU_MJ_H_
#define INSTANCE_MENU_MJ_H_

#include "../../instance.h"

#include "../menu.h"
#include "../../temporizador.h"

/**
 * @brief Clase que representa una estancia del menú multijugador
 *
 * Para más información sobre el funcionamiento de las estancias, vea las clases
 * CInstance_Menu_Main, CInstance, CEngine, CMenu y CBoton.
 * Un ejemplo del menú, con un diseño minimalista, es el siguiente:
 */
class CInstance_Menu_MJ: public CInstance
{
  private:
    bool i_running;

    CBoton* botones;
    CMenu* menu;

    SDL_Color color_negro;
    SDL_Color color_blanco;
  public:
    CInstance_Menu_MJ();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnLoop(int& caso);
    void OnEvent(int& caso);

    void OnRender();
};

/**
 * @brief Clase que representa una estancia del menú multijugador online
 *
 * Para más información sobre el funcionamiento de las estancias, vea las clases
 * CInstance_Menu_Main, CInstance, CEngine, CMenu y CBoton.
 * Un ejemplo del menú, con un diseño minimalista, es el siguiente:
 */
class CInstance_Menu_MJ_Online: public CInstance
{
  private:
    bool i_running;
    bool conectado;

    CBoton* botones;
    CMenu* menu;

    SDL_Color color_negro;
    SDL_Color color_blanco;
  public:
    CInstance_Menu_MJ_Online();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    //void OnLoop(int& caso);
    void OnEvent(int& caso);
    void OnRender();
};

#endif /* INSTANCE_MENU_MJ_H_ */
