#include "../../../pad.h"
#include "pelota_cpu.h"

#ifndef PAD_CPU_H_
#define PAD_CPU_H_

float pendiente(float x, float y, float Vx, float Vy);
//int calcPos(int m, int b, int x);
int calcPos(float m, float x, float x0, float y0);

class CPad_CPU : public CPad
{
  private:
	bool wait;
    bool calcular;
  public:
	CPad_CPU();
    ~CPad_CPU();

    void mover(CPelota_CPU pelota);
    void mostrar();
};

#endif
