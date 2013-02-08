#ifndef PELOTA_MJ_H_
#define PELOTA_MJ_H_

#include "../pelota.h"

class CPelota_MJ: public CPelota
{
  protected:
	   bool stop, lock;
	   float xVel, yVel;
  public:
	   CPelota_MJ(): stop(false), lock(false) {};
	   virtual ~CPelota_MJ() {};

	//void empezar();
    virtual int mover(CPad PJ1, CPad PJ2);
};

#endif /* PELOTA_MJ_H_ */
