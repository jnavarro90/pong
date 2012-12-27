#ifndef PELOTA_MJ_ONLINE_H_
#define PELOTA_MJ_ONLINE_H_

#include "../pelota_mj.h"
#include "pad_mj_online.h"

class CPelota_MJ_Online: public CPelota_MJ
{
  public:
	   void empezar();
	   int mover(CPad PJ1, CPad PJ2, flags& f);
};

class CPelota_MJ_Online_Client: public CPelota
{
  public:
    void setXY(int x, int y);
};


#endif /* PELOTA_MJ_ONLINE_H_ */
