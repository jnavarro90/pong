#ifndef INSTANCE_1J_INF_H_
#define INSTANCE_1J_INF_H_

#include "pad_1j_inf.h"
#include "pelota_1j_inf.h"

#include "../turbo.h"
#include "../../instance.h"
#include "../../temporizador.h"

enum returns {perder = 0, juego, rebote, rebote_pad};

class CInstance_1J_INF: public CInstance
{
  protected:
    CPad_1J_INF* PJ1;
    CPelota_1J_INF* pelota;

    CTemporizador* tMarca;
    SDL_Surface* marca;

    CTurbo* turbo;

    bool fin;
  public:
    CInstance_1J_INF();

    bool Init();
      bool LoadFiles();

    void Close();
      void UnLoadFiles();

    int OnExecute();

    void OnEvent(int& salida);
    void OnLoop(int& salida);
    void OnRender();
};

#endif /* INSTANCE_1J_INF_H_ */
