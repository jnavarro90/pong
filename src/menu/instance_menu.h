#ifndef INSTANCE_MENU_H_
#define INSTANCE_MENU_H_

#include "../instance.h"

#include "menu.h"
#include "menu_vars.h"
#include "../temporizador.h"

const int FRAMES_PER_SECOND = 60;

class CInstance_Menu_Main: public CInstance
{
  private:
    bool i_running;

    CBoton* botones;
    CMenu* menu;

    SDL_Color color_negro;
    SDL_Color color_blanco;
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
