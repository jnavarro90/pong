#ifndef PAD_MJ_ONLINE_H_
#define PAD_MJ_ONLINE_H_

#include "../pad_mj.h"

enum lado { izq = 0, der };
enum mov { abajo = -1, quieto = 0, arriba = 1 };

class CPad_MJ_Online: public CPad
{
  protected:
	SDLKey KUp, KDown;
  public:
	CPad_MJ_Online(enum lado, SDLKey U, SDLKey D);
	~CPad_MJ_Online();

    void eventuar();
    void mover();
};

class CPad_MJ_Online_Zombi: public CPad
{
  // Casi mejor trabajar con una funcion eventuar o algo...
  public:
	CPad_MJ_Online_Zombi(enum lado lado);
	~CPad_MJ_Online_Zombi();

    //void setY(int y);
    void mover(int8 mov);
};

// En estas clases sobran los miembros yVel y momento derivados de clases superires. Arreglar esta chapuza.
class CPad_MJ_Online_Client: public CPad
{
  protected:
	SDLKey KUp, KDown;
  public:
	CPad_MJ_Online_Client(enum lado, SDLKey U, SDLKey D);

	void eventuar(int8& mov);
	void setY(int y);
};

class CPad_MJ_Online_Client_Zombi: public CPad
{
  public:
	CPad_MJ_Online_Client_Zombi(enum lado);

	void setY(int y);
};

#endif /* PAD_MJ_ONLINE_H_ */
