#include "../../pad_mj.h"
#include "pelota_cpu.h"

#ifndef PAD_CPU_H_
#define PAD_CPU_H_

float pendiente(float x, float y, float Vx, float Vy);
//int calcPos(int m, int b, int x);
int calcPos(float m, float x, float x0, float y0);

class CPad_MJ_CPU : public CPad_MJ
{
  private:
    bool calcular;
  public:
	   CPad_MJ_CPU();
    ~CPad_MJ_CPU();

    void setCalcular(bool b = true) {calcular = b;}

    void mover(CPelota_MJ_CPU& pelota);
    //void mostrar();
};

#endif
