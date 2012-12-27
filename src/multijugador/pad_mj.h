#ifndef PAD_MULTIJUGADOR_H_
#define PAD_MULTIJUGADOR_H_

#include "../pad.h"

// De momento, esta clase es inutil. Ya vere lo que hacemos con ella...
// Tal vez añadiendole yVel y momento podemos hacer que CPad_MJ_Online y CPad_MJ_Online_Zombi deriven de esta.

class CPad_MJ: public CPad
{
  public:
	CPad_MJ();
	~CPad_MJ();

	//void mostrar();
};



#endif /* PAD_MULTIJUGADOR_H_ */
