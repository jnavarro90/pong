/**
 * @file
 * @brief Declaraci�n de CMarcador_Online
 *
 */

#ifndef MARCADOR_ONLINE_H_
#define MARCADOR_ONLINE_H_

#include "../marcador.h"

/**
 * @brief Clase para representar un marcador a nivel de cliente.
 *
 * La clase almacenar� el valor de los marcadores (descargados del servidor)
 * y 2 superficies para guardar el texto de los marcadores.
 */
class CMarcador_Online: public CMarcador
{
  public:
    CMarcador_Online(TTF_Font* f, SDL_Color* c);
    ~CMarcador_Online();

    void setM1(int n);
    void setM2(int n);
};


#endif /* MARCADOR_ONLINE_H_ */
