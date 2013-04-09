#ifndef PELOTA_MJ_ONLINE_H_
#define PELOTA_MJ_ONLINE_H_

#include "../pelota_mj.h"
#include "pad_mj_online.h"

#include "../../opciones/opciones.h"

class CPelota_MJ_Online: public CPelota_MJ
{
  public:
    CPelota_MJ_Online();

	   void empezar();
	   int mover(CPad& PJ1, CPad& PJ2, flags& f);
};

class CPelota_MJ_Online_Client: public CPelota
{
  public:
    CPelota_MJ_Online_Client(): CPelota(){};

    void setXY(int x, int y);
};


#endif /* PELOTA_MJ_ONLINE_H_ */
