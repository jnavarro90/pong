/**
 * @file
 * @brief Definici�n de la clase COpciones.
 */

#include <sstream>
#include <limits>
#include <stdlib.h>

#include "opciones.h"

using namespace std;

COpciones* opciones = NULL;

/**
 * @brief Constructor principal
 *
 * @param file Ruta del fichero desde el que se cargan los datos.
 *
 * El funcionamiento del constructor es el siguiente. Primero, carga los datos por defecto con las definiciones defConf ubicadas
 * en opciones.h. Posteriormente, trata de abrir el archivo. Si no se puede abrir o no existe, se crear� un fichero nuevo con los valores
 * por defecto. En caso de que s� se pueda abrir, se recorrer�n todas las l�neas y se tratar� de hacer las asignaciones
 * correspondientes con la funci�n cargarDato().
 */
COpciones::COpciones(const char* file): PELOTA_ANCHO(PELOTA_ALTO)
{
  //PELOTA_ANCHO = PELOTA_ALTO;
  cargarDefecto();

  ifstream is(file);
  if(is.good())
    cargarFichero(is);
  else
  {
    crearFicheroDefault(file);
    cout << "Error cargando datos por defecto desde el fichero \"" << file << "\"." << endl;
    cout << "Creando archivo \"" << file << "\"" << endl;
  }
  is.close();
}

/**
 * @brief Cargador de ficheros
 *
 * @param is Flujo ifstream desde el cual se ha abierto el fichero.
 *
 * En caso de que se pueda acceder al fichero, se tratar�n de leer todas las l�neas. Se ignorar�n las l�neas en blanco
 * y las comentadas (las que empiezan por #). Se intentar� hacer una carga para cada l�nea le�da por medio de la
 * funci�n cargarDato().
 */
void COpciones::cargarFichero(ifstream& is)
{
  string id, valor;
  while(getline(is, id, ' '))
  {
    getline(is, valor, '\n');
    if(id[0] != '#' && id[0] != '\n') // Linea no comentada o en blanco
    {
      cargarDato(id, valor);
    }
  }
}

/**
 * @brief Carga un dato en un miembro de la clase.
 *
 * @param id Identificacor de la opci�n. Debe tener un nombre en min�sculas y debe equivaler a uno definido en la propia clase.
 * @param valor Valor a asignar al identificador id.
 *
 * La funci�n analizar� la l�nea le�da del tipo \<opcion\> \<valor\>. En caso de que no se pase ning�n valor, se
 * asignar� el valor por defecto. Las opciones tienen el mismo nombre que en la misma clase, s�lo que con letras
 * min�sculas. Las asignaciones de teclas no est� implementadas. En cualquier caso, como valor es de tipo string,
 * se deben hacer los cambios necesarios para transformarlo a un entero, de punto flotante o hexadecimal. V�ase la
 * definici�n de la funci�n para entender las asignaciones mejor.
 */
void COpciones::cargarDato(string id, string valor)
{
  if(id == "pantalla_ancho")
  {
    if(valor != "")
    {
      PANTALLA_ANCHO = atoi(valor.c_str());
      if(PANTALLA_ANCHO < 500)
        PANTALLA_ANCHO = defConf_PANTALLA_ANCHO;
    }
    else
      PANTALLA_ANCHO = defConf_PANTALLA_ANCHO;
  }
  else if(id == "pantalla_alto")
  {
    if(valor != "")
    {
      PANTALLA_ALTO = atoi(valor.c_str());
      if(PANTALLA_ALTO < 380 || (PANTALLA_ALTO - 60) % 40 != 0)
      {
        cout << "Formato de pantalla_alto(mayor que 260) :" << "60 + N, siendo N multiplo de 40." << endl;
        PANTALLA_ALTO = defConf_PANTALLA_ALTO;
      }
    }
    else
      PANTALLA_ALTO = defConf_PANTALLA_ALTO;
  }
  else if(id == "pantalla_bpp")
  {
    if(valor != "")
    {
      PANTALLA_BPP = atoi(valor.c_str());
      if( PANTALLA_BPP < 0 || PANTALLA_BPP > 64)
        PANTALLA_BPP = defConf_PANTALLA_BPP;
    }
    else
      PANTALLA_BPP = defConf_PANTALLA_BPP;
  }
  else if(id == "pantalla_completa")
  {
    if(valor != "")
    {
      if(valor == "true")
        PANTALLA_COMPLETA = true;
      else if(valor == "false")
        PANTALLA_COMPLETA = defConf_PANTALLA_COMPLETA;
    }
    else
      PANTALLA_COMPLETA = defConf_PANTALLA_BPP;
  }
  else if(id == "pad_vel")
  {
    if(valor != "")
    {
      PAD_VEL = atof(valor.c_str());
      if( PAD_VEL <= 0)
        PAD_VEL = defConf_PAD_VEL;
    }
    else
      PAD_VEL = defConf_PAD_VEL;
  }
  else if(id == "pad_alto")
  {
    if(valor != "")
    {
      PAD_ALTO = atoi(valor.c_str());
      if( PAD_ALTO <= 1)
        PAD_VEL = defConf_PAD_ALTO;
    }
    else
      PAD_ALTO = defConf_PAD_ALTO;
  }
  else if(id == "pad_ancho")
  {
    if(valor != "")
    {
      PAD_ANCHO = atoi(valor.c_str());
      if( PAD_ANCHO <= 1)
        PAD_ANCHO = defConf_PAD_ANCHO;
    }
    else
      PAD_ANCHO = defConf_PAD_ANCHO;
  }
  else if(id == "pelota_vel")
  {
    if(valor != "")
    {
      PELOTA_VEL = atof(valor.c_str());
      if( PELOTA_VEL <= 0)
        PELOTA_VEL = defConf_PELOTA_VEL;
    }
    else
      PELOTA_VEL = defConf_PELOTA_VEL;
  }
  else if(id == "pelota_alto")
  {
    if(valor != "")
    {
      PELOTA_ALTO = atoi(valor.c_str());
      if( PELOTA_ALTO <= 0)
        PELOTA_VEL = defConf_PELOTA_ALTO;
    }
    else
      PELOTA_ALTO = defConf_PELOTA_ALTO;
  }
  else if(id == "pad_color")
  {
    if(valor != "" && valor.size() == 6)
    {
      uint8 red = strtol(valor.substr(0,2).c_str(), NULL, 16); // string a hexadecimal
      uint8 green = strtol(valor.substr(2,2).c_str(), NULL, 16); // string a hexadecimal
      uint8 blue = strtol(valor.substr(4,2).c_str(), NULL, 16); // string a hexadecimal

      PAD_COLOR = SDL_MapRGB(SDL_SetVideoMode(0 ,0 ,32 ,SDL_HWSURFACE)->format, red, green, blue);
    }
    else
      PAD_COLOR = SDL_MapRGB(SDL_SetVideoMode(0 ,0 ,32 ,SDL_HWSURFACE)->format, 0xFF, 0xFF, 0xFF);
  }
  else if(id == "pelota_color")
  {
    if(valor != "" && valor.size() == 6)
    {
      uint8 red = strtol(valor.substr(0,2).c_str(), NULL, 16); // string a hexadecimal
      uint8 green = strtol(valor.substr(2,2).c_str(), NULL, 16); // string a hexadecimal
      uint8 blue = strtol(valor.substr(4,2).c_str(), NULL, 16); // string a hexadecimal

      PELOTA_COLOR = SDL_MapRGB(SDL_SetVideoMode(0 ,0 ,32 ,SDL_HWSURFACE)->format, red, green, blue);
    }
    else
      PELOTA_COLOR = SDL_MapRGB(SDL_SetVideoMode(0 ,0 ,32 ,SDL_HWSURFACE)->format, 0xFF, 0xFF, 0xFF);
  }
  else {
    cout << "Orden \"" << id << "\" con valor \"" << valor << "\"no reconocida." << endl;
  }
  // resto de configuraciones
}

/**
 * @brief Cargador por defecto
 *
 * Usa la funci�n cargarDato con todas los identificadores y un valor nulo "" para cada identificador.
 * De esta forma, se cargar�n para todas las opciones el valor por defecto correspondiente.
 */
void COpciones::cargarDefecto()
{
  string aux_id;

  aux_id = "pantalla_ancho";
  cargarDato(aux_id);
  aux_id = "pantalla_alto";
  cargarDato(aux_id);
  aux_id = "pantalla_bpp";
  cargarDato(aux_id);
  aux_id = "pantalla_completa";
  cargarDato(aux_id);

  aux_id = "pad_alto";
  cargarDato(aux_id);
  aux_id = "pad_ancho";
  cargarDato(aux_id);
  aux_id = "pad_vel";
  cargarDato(aux_id);
  aux_id = "pad_color";
  cargarDato(aux_id);

  aux_id = "pelota_alto";
  cargarDato(aux_id);
  aux_id = "pelota_vel";
  cargarDato(aux_id);
  aux_id = "pelota_color";
  cargarDato(aux_id);

}

/**
 * @brief Creado de fichero de opciones por defecto
 *
 * @param file Ruta de fichero de salida.
 *
 * En caso de no haber podido leer el fichero, el programa crear� un fichero en la ruta espeficiada por file. Se cargar�
 * en el fichero todos los identificadores junto con todas las opciones por defecto defConf. En caso de que no se pueda
 * crear el fichero (corrupci�n...), no se har� nada.
 */
void COpciones::crearFicheroDefault(const char* file)
{
  ofstream os(file);

  if(!os.good())
  {
    os.close();
    cout << "Error creando fichero \"" << file << "\"." << endl;
  }

  os << "pantalla_ancho " << defConf_PANTALLA_ANCHO << endl;
  os << "pantalla_alto " << defConf_PANTALLA_ALTO << endl;
  os << "pantalla_bpp " << defConf_PANTALLA_BPP << endl;

  os << "pad_alto " << defConf_PAD_ALTO << endl;
  os << "pad_ancho " << defConf_PAD_ANCHO << endl;
  os << "pad_vel " << defConf_PAD_VEL << endl;
  os << "pad_color " << defConf_PAD_COLOR << endl;

  os << "pelota_alto " << defConf_PELOTA_ALTO << endl;
  os << "pelota_vel " << defConf_PELOTA_VEL << endl;
  os << "pelota_color " << defConf_PELOTA_COLOR << endl;

  os.close();
}


