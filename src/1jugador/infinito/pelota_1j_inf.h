#ifndef PELOTA_1J_INF_H_
#define PELOTA_1J_INF_H_

#include "../../pelota.h"
#include "pad_1j_inf.h"

void setVel_1j_inf(float& yVel, float& xVel, int pos_actual, int momento);
int getPos_1j_inf(SDL_Rect pelota, SDL_Rect pad);

class CPelota_1J_INF: public CPelota
{
  private:
	  bool stop, lock;
	  float xVel, yVel;
  public:
	  CPelota_1J_INF();
	  ~CPelota_1J_INF();

	  int mover(CPad_1J_INF& PJ1);

	  void incVel(float n);
	  void decTam(float n);

	  void empezar();
};

#endif /* PELOTA_1J_INF_H_ */
