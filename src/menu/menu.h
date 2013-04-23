/**
 * @file
 * @brief Declaraci�n de la clase CMenu
 */

#ifndef MENU_H_
#define MENU_H_

#include "boton.h"

/**
 * @brief Clase para almacenar conjuntos de botones
 *
 * Se encargar� de gestionar el uso de un cierto n�mero de botones como si se tratase de un bot�n.
 * Se verificar�, para cada bot�n, que el rat�n est� encima de alg�n bot�n y que se haga click izquierdo encima de alguno.
 */
class CMenu
{
  private:
    CBoton* botones;/**< Array de botones para gestionar*/
    int nBotones;/**< Numero de botones a almacenar*/
  public:
    CMenu(CBoton* botones, int n);
    ~CMenu();

    void mostrar();
    int eventuar();
};


#endif /* MENU_H_ */
