#ifndef INSTANCE_MENU_MJ_H_
#define INSTANCE_MENU_MJ_H_

#include "../../instance.h"

#include "../menu.h"
#include "../../temporizador.h"

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
