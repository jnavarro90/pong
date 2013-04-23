#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "engine.h"

#include "opciones/opciones.h"
#include "opciones/tablero.h"

//#include <windows.h>

using namespace std;

// Esto se usa para debug (mostrar por consola);
#ifdef DEBUG
  #undef main
#endif

/*DWORD WINAPI EngineCaller(LPVOID lpParam)
{
  return CEngine().OnExecute();
}

int main( int argc, char* args[] )
{
#ifdef WIN32
  HANDLE hThread = CreateThread(NULL, 0, EngineCaller, NULL, 0, NULL);
  if(hThread == NULL)
    cout << "Error creando thread para el bucle principal del programa." << endl;

  WaitForSingleObject(hThread, INFINITE);

  if(CloseHandle(hThread) == 0)
    cout << "Error cerrando thread del bucle principal del programa." << endl;
  return 0;
#else
  return CEngine().OnExecute();
#endif
}*/

/**
 * @file
 * @brief Función principal.
 *
 * Genera un objeto de la clase CEngine y ejecuta la función CEngine::OnExecute().
 *
 * @return Devuelve el valor que valor que devuelva la función CEngine::OnExecute().
 */
int main()
{
  return CEngine().OnExecute();
}
