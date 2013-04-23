/**
 * @file
 * @brief Definición de la clase CMenu
 */

#include "menu.h"

/**
 * @brief Constructor principal
 *
 * @param b Array de botones del tipo CBoton previamente inicializado.
 * @param n Numero de botones en el array b
 *
 * Se cargarán los valores en los correspondientes miembros de la clase, #botones y #nBotones
 */
CMenu::CMenu(CBoton* b, int n)
{
  botones = b;
  nBotones = n;
}

/**
 * @brief Destructor
 *
 * Asigna valores nulos a los miembros de la clase
 */
CMenu::~CMenu()
{
  botones = NULL;
  nBotones = 0;
}

/**
 * @brief Mostrar por pantalla
 *
 * Recorre el vector #botones y llama a la función CBoton::mostrar() de cada uno.
 */
void CMenu::mostrar()
{
  for(int i = 0; i < nBotones; i++)
  {
    botones[i].mostrar();
  }
}

/**
 * @brief Gestionar eventos
 *
 * @return Devuelve el número del botón pulsado, desde 1 hasta nBotones. Si no se ha pulsado ninguno, devolverá 0.
 *
 * Si el usuario a hecho click con el mouse, se comprobarán todos los marcos de los botones hasta encontrar alguno que cuadre
 * con la posición del ratón. Si no cuadra con ninguno, se supone que el usuario no ha pulsado ningún botón.
 */
int CMenu::eventuar()
{
  if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
  {
    for(int i = 0; i < nBotones; i++)
    {
	     if(botones[i].encima())
	       return i+1;
    }
  }
  return 0;
}
