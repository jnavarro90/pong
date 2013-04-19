/**
 * @file
 * @brief Declaración de CInstance
 *
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "globals.h"
#include "opciones/opciones.h"

/**
 * @brief Clase base (abstracta) para derivar y declarar las diversas estancias del juego.
 *
 * Su unico propósito es dar un formato equivalente para todas las estancias, aunque no todas las funciones
 * sea iguales.
 */

class CInstance
{
  protected:
    SDL_Surface* fondo; /**< Superficie que contendrá la imagen cargada en el fondo. */
    bool i_running; /**< Como running en CEngine, pero propia a cada estancia. */
  public:
    CInstance(){}; /**< Constructor vacío. */
    virtual ~CInstance(){}; /**< Destructor vacío. */

    virtual bool Init();
      virtual bool LoadFiles();

    virtual void Close(){} /**< Des-inicializador. */
      virtual void UnLoadFiles(){} /**< Des-cargador de archivos. */

    virtual int OnExecute();

    virtual void OnLoop(){}; /**< Gestionar datos. */
    virtual void OnEvent(){}; /**< Gestionar eventos de entrada. */
    virtual void OnRender(){};  /**< Mostrar por pantalla. */
};



#endif /* INSTANCE_H_ */
