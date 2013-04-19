/**
 * @file
 * @brief Declara la clase CEngine
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "globals.h"
#include "instance.h"

/**
 * @brief Clase principal del juego.
 *
 * Esta clase se encarga de gestionar las diversas estancias del juego, de tal forma que solo
 * haya carga una unica estancia en cada modo de juego
 */

class CEngine
{
  protected:
    CInstance* instance[N_INSTANCES]; /**< Punteros a todas las estancias iniciadas en Init() */
    bool running; /**< Booleano para determinar cuando el motor del juego deja de ejecutarse */

  public:
    CEngine();
    virtual ~CEngine();

    virtual bool Init();
      virtual bool LoadFiles();
      //virtual void BindInstances();
    virtual void Close();
      virtual void UnLoadFiles();

    virtual int OnExecute();
};

#endif /* CENGINE_H_ */
