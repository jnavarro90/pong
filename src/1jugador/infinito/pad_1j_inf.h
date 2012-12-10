#ifndef PAD_1J_INF_H_
#define PAD_1J_INF_H_

#include "../../pad.h"

extern float PAD_1J_INF_VELOCIDAD;
extern int PAD_1J_INF_ALTO;
extern int PAD_1J_INF_MEDIO;

const int PAD_1J_INF_MIN_ALTO = PAD_ALTO/2;
const int PAD_1J_INF_MIN_VEL = PAD_VELOCIDAD/4;

class CPad_1J_INF: public CPad
{
  private:
	SDLKey KUp, KDown;
  public:
	CPad_1J_INF();
	~CPad_1J_INF();

	void decTam(int n); // Decrementar tamaño
	void incVel(float n); // Decrementar velocidad

	void mostrar();
	void mover();
	void eventuar();

	int getTam(){return caja.h;}
};


#endif /* PAD_1J_INF_H_ */
