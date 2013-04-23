/**
 * @file
 * @brief Definición de CInstance
 *
 */

#include "instance.h"

/**
 * @brief Función de iniciación.
 *
 * @return Si todo se ha iniciado correctamente, devuelve true. En caso contrario, devuelve false
 *
 * Inicializa todo lo necesario para que la estancia funcione correctamente. Debe ser desinicializado poseriormente en Close()
 */
bool CInstance::Init()
{
  if(!LoadFiles())
    return false;
  return true;
}

/**
 * @brief Función de carga de archivos.
 *
 * @return Si todo se ha cargado correctamente, devuelve true. En caso contrario, devuelve false
 *
 * Carga todos los archivos necesarios. Llamado desde Init()
 */
bool CInstance::LoadFiles()
{
  return true;
}

/**
 * @brief Prototipo de función de ejecución.
 *
 * @return Devuelve la próxima estancia a ser ejecutada por el bucle principal ubicado en CEngine::OnExecute()
 *
 * Ejecuta el bucle principal de la estancia que se estructura de la forma siguiente:
 * \code
 * Init()            // Iniciar
 * while(ejecutando) // Bucle principal
 * {
 *   OnEvent()       // Gestionar eventos
 *   OnLoop()        // Gestionar datos
 *   OnRender()      // Mostrar por pantalla
 * }
 * Close()           // Cerrar
 * return estancia_siguiente;
 * \endcode
 *
 */
int CInstance::OnExecute()
{
  if(!Init())
    return I_SALIDA;

  int salida = 0;

  while(i_running)
  {
    while(SDL_PollEvent(&event))
    {
      OnEvent();
    }
    OnLoop();
    OnRender();
  }

  Close();
  return salida;
}

