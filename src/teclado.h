/** @file
 * @brief Declaración de la clase CTeclado
 * */

#ifndef TECADO_H_
#define TECADO_H_

#include <string>
#include "globals.h"

using namespace std;

/**
 * @brief Clase para introducir una cadena por el teclado y mostrarla por pantalla.
 *
 * El objeto generado a partir de esta clase gestionará los eventos de entrada desde el teclado y los mostrará por pantalla en
 * una posición determinada.
 *
 */
class CTeclado
{
  protected:
	   string str; /**< Guardar la cadena de caracteres de entrada*/
	   SDL_Surface* img_texto; /**< Guarda el texto generado en una superficie*/
    TTF_Font* ttf_fuente; /**< Fuente para generar el texto guardado en #img_texto*/
    SDL_Color color_texto; /**< Color del texto*/
	   int x; /**< Offset vertical con respecto a la #pantalla*/
	   int y; /**< Offset vertical con respecto a la #pantalla*/
	   uint tam; /**< Tamaño del texto*/
	   uint length; /**< Tamaño máximo de la cadena guardada en #str*/

  public:
	   CTeclado(){}; /**< Constructor por defecto. No asigna valores. */
	   CTeclado(const char* fuente, uint tam, SDL_Color* color, int ax, int ay, uint l = 16);
   	virtual ~CTeclado();

   	virtual void eventuar();
 	  virtual void mostrar();

 	  string getStr() {return str;} /**< @return Devuelve el contenido guardado en #str*/
};


#endif /* TECADO_H_ */
