#ifndef PELOTA_CPU_H_
#define PELOTA_CPU_H_

#include "../pelota_mj_local.h"

class CPelota_CPU : public CPelota_MJ_Local
{
  public:
	int getX(){return caja.x;}
	int getY(){return caja.y;}

	float getxVel(){return xVel;}
	float getyVel(){return yVel;}
};


#endif
