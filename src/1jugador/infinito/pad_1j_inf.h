/**
 * @file
 * @brief Declaración de CPad_1J_INF
 *
 */

#ifndef PAD_1J_INF_H_
#define PAD_1J_INF_H_

#include "../../pad.h"

extern float PAD_1J_INF_VELOCIDAD;/**< Velocidad del pad.*/
extern int PAD_1J_INF_ALTO;/**< Altura del pad.*/
extern int PAD_1J_INF_MEDIO;/**< La mitad de la altura del pad.*/

const int PAD_1J_INF_MIN_ALTO = PAD_ALTO/2; /**< Minimo de altura si se decrementa.*/
const int PAD_1J_INF_MIN_VEL = PAD_VELOCIDAD/4; /** Minimo de velocidad si se decrementa.*/

/**
 * @brief Clase general para definir el pad de 1 jugador-infinito
 *
 * El funcionamiento de esta clase es muy simple. Puede ver los métodos de la clase en sí y de la clase base
 * CPad para entender el correcto funcionamiento de esta.
 *
 */
class CPad_1J_INF: public CPad
{
  private:
	   SDLKey KUp;/**< Tecla para subir el pad*/
	   SDLKey KDown;/**< Tecla para bajar el pad*/
	   float yVel;/**< Velocidad vertical del pad*/
  public:
   	CPad_1J_INF();
   	~CPad_1J_INF();

	   void decTam(int n); // Decrementar tamaño
	   void incVel(float n); // Decrementar velocidad

   	void mover();
   	void eventuar();

   	int getTam(){return caja.h;}
};


#endif /* PAD_1J_INF_H_ */
