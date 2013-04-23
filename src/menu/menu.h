/**
 * @file
 * @brief Declaración de la clase CMenu
 */

#ifndef MENU_H_
#define MENU_H_

#include "boton.h"

/**
 * @brief Clase para almacenar conjuntos de botones
 *
 * Se encargará de gestionar el uso de un cierto número de botones como si se tratase de un botón.
 * Se verificará, para cada botón, que el ratón esté encima de algún botón y que se haga click izquierdo encima de alguno.
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
