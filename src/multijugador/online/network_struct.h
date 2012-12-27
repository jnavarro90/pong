#ifndef NETWORK_STRUCT_H_
#define NETWORK_STRUCT_H_

#include "../../globals.h"

// Por simplicidad, vamos a suponer que un jugador hace de servidor, y otro, de cliente

//enum datos { pelota_x = 0, pelota_y, pad1_y, pad2_y }; // falta snd_pong, snd_pung (flags); marcador1, marcador2 (4 bytes)
enum fSnd_pelota {fsnd_pong = 0x1, fsnd_pung = 0x2};

// Total: 12 bytes
struct network_data_server_t // lo que envia el servidor = lo que recibe el cliente
{
  int16 pelota_x, pelota_y;
  int16 pad1_y;
  int16 pad2_y;
  flags fs;
  uint8 marcador1, marcador2;
  uint8 sinUso;
}; // Falta añadir datos del marcador.

// Total: 1 byte
struct network_data_client_t // Lo que envia el cliente = lo que recibe el servidor
{
  int8 evento;// Si se mueve hacia arriba, hacia abajo o si se queda quieto
};

// Datos servidor
extern void SdataToChar(network_data_server_t* t, uchar c[_NET_BYTES_]);
extern void charToSdata(uchar c[_NET_BYTES_], network_data_server_t* t);

// Datos cliente
extern void CdataToChar(network_data_client_t* t, uchar c);
extern void charToCdata(uchar c, network_data_client_t* t);

/*template<typename T>
char* dataToChar(T* data)
{
  char* c = reinterpret_cast<char*>(data);
  return c;
}

template<typename T>
T* charToData(char* c)
{
  //T* data = reinterpret_cast<T>(c);
  T* data = reinterpret_cast<T*>(c);
  return data;
}*/


//extern void int16ToChar(uint16 in[4], unsigned char c[8]);
//extern void charToInt16(unsigned char c[8], uint16 in[4]);

#endif /* NETWORK_STRUCT_H_ */
