/*
 * instance_menu_opciones.h
 *
 *  Created on: 11/04/2013
 *      Author: Dani
 */

#ifndef INSTANCE_MENU_OPCIONES_H_
#define INSTANCE_MENU_OPCIONES_H_

#include "../../instance.h"

class CInstance_Menu_Opciones: public CInstance
{
  private:
    bool i_running;

    CBoton* botones;
    CMenu* menu;

    SDL_Color color_negro;
    SDL_Color color_blanco;
  public:
    CInstance_Menu_Opciones();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnLoop(int& caso);
    void OnEvent(int& caso);

    void OnRender();
};



#endif /* INSTANCE_MENU_OPCIONES_H_ */
