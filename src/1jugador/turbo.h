#ifndef TURBO_H_
#define TURBO_H_

#include "../globals.h"


class CTurbo
{
  private:
    SDL_Rect caja;
    SDL_Rect* clip;
    SDL_Rect clips[4];

    SDL_Surface* img;
    bool running;

    int frame;
    int animation;
    int cheatCount;

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
