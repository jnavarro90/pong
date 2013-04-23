#ifndef PELOTA_CPU_H_
#define PELOTA_CPU_H_

#include "../pelota_mj_local.h"

class CPelota_MJ_CPU : public CPelota_MJ_Local
{
  public:
    CPelota_MJ_CPU():CPelota_MJ_Local(){};

	   int getX(){return caja.x;}
   	int getY(){return caja.y;}

   	float getxVel();
   	float getyVel();

	   int mover(CPad& A, CPad& B);

	   //void empezar(enum gamepoint_pj_t);
};


#endif
