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
    CInstance(){};
    virtual ~CInstance(){};

    virtual bool Init();
      virtual bool LoadFiles();

    virtual void Close(){}
      virtual void UnLoadFiles(){}

    virtual int OnExecute();

    virtual void OnLoop(){};
    virtual void OnEvent(){};
    virtual void OnRender(){};
};



#endif /* INSTANCE_H_ */
