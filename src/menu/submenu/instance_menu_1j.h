#ifndef INSTANCE_MENU_1J_H_
#define INSTANCE_MENU_1J_H_

#include "../../instance.h"

#include "../menu.h"
#include "../../temporizador.h"

class CInstance_Menu_1J: public CInstance
{
  private:
    bool i_running;

    CBoton* botones;
    CMenu* menu;

    SDL_Color color_negro;
    SDL_Color color_blanco;
  public:
    CInstance_Menu_1J();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnLoop(int& caso);
    void OnEvent(int& caso);

    void OnRender();
};



#endif /* INSTANCE_MENU_1J_H_ */
