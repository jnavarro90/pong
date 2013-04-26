/**
 * @file
 * @brief Declaraci�n de CPelota_1J_INF
 *
 */

#ifndef PELOTA_1J_INF_H_
#define PELOTA_1J_INF_H_

#include "../../pelota.h"
#include "pad_1j_inf.h"

/**
 * @brief setVel para un jugador. Vea setVel().
 */
void setVel_1j_inf(float& yVel, float& xVel, int pos_actual, int momento);

/**
 * @brief getPos para un jugador. Vea getPos().
 */
int getPos_1j_inf(SDL_Rect pelota, SDL_Rect pad);

/**
 * @brief Enum para saber que tipo de acci�n hacer cuando la funci�n CPelota_1J_INF::mover() devuelva un valor.
 */
enum return_1j_inf {perder = 0, juego, rebote, rebote_pad};

/**
 * @brief Clase general para definir la pelota de 1 jugador-infinito
 *
 * El funcionamiento de esta clase es muy simple. Puede ver los m�todos de la clase en s� y de la clase base
 * CPelota para entender el correcto funcionamiento de esta.
 *
 */
class CPelota_1J_INF: public CPelota
{
  private:
	  bool stop; /**< �La pelota est� parada? */
	  bool lock; /**< �La pelota est� bloqueada? */
	  float xVel; /** Velocidad horizontal de la pelota en bits por frame*/
	  float yVel; /** Velocidad vertical de la pelota en bits por frame*/
  public:
	  CPelota_1J_INF();
	  ~CPelota_1J_INF();

	  int mover(CPad_1J_INF& PJ1, bool setVel = false);

	  void incVel(float n);
	  void decTam(float n);

	  void empezar();
};

#endif /* PELOTA_1J_INF_H_ */
