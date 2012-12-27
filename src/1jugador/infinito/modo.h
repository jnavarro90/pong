#ifndef MODO_H_
#define MODO_H_

class CModo
{
  private:
	int accion;
	// int vidas, puntuacion
	float segundos;
  public:
	CModo(int, float);
	~CModo();

	void accionar(int n);

};


#endif /* MODO_H_ */
