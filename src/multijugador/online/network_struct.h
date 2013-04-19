#ifndef NETWORK_STRUCT_H_
#define NETWORK_STRUCT_H_

#include "../../globals.h"

// Por simplicidad, vamos a suponer que un jugador hace de servidor, y otro, de cliente

enum fSnd_pelota {fsnd_empty = 0x00, fsnd_pong = 0x1, fsnd_pung = 0x2};
/*
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
extern void CdataToChar(network_data_client_t* t, uchar& c);
extern void charToCdata(uchar& c, network_data_client_t* t);
*/

class CNetwork_Data_Client
{
  private:
    char buffer[NET_MJ_CLIENTDATA_SIZE];
  public:
    int8 evento; // 1 byte
    int8 unused; // 1 byte
    Uint32 ticks; // 4 bytes
    // Total: 6 bytes
  public:
    CNetwork_Data_Client();

    void makeBuffer();
    char* getBuffer();

    void readBuffer(char* b);
};

class CNetwork_Data_Server
{
  private:
    char buffer[NET_MJ_SERVERDATA_SIZE];
  public:
    int16 pelota_x, pelota_y; // 2 + 2 bytes
    int16 pad1_y; // 2 bytes
    int16 pad2_y; // 2 bytes
    flags fs; // 1 byte
    uint8 marcador1, marcador2; // 1 + 1 bytes
    uint8 sinUso; // 1 byte
    // ticks usado  para tratar retardos y saltar frames
    Uint32 ticks; // 4 bytes
    // Total: 12 + 4 bytes
  public:
    CNetwork_Data_Server();

    void makeBuffer();
    char* getBuffer();

    void readBuffer(uchar* b);
};

class CNetwork_Data_Settings
{
  private:
    char buffer[NET_MJ_SETTINGS_SIZE];
  public:
    int16 PANTALLA_ANCHO; // 2 bytes
    int16 PANTALLA_ALTO; // 2 bytes

    int16 PAD_ALTO; // 2 bytes
    int16 PAD_ANCHO; // 2 bytes

    int16 PELOTA_ALTO; // 2 bytes
    int16 unused; // 2 bytes
    // Total: 12 bytes
  public:
    CNetwork_Data_Settings();

    void makeBuffer();
    char* getBuffer();

    void readBuffer(uchar* b);
};

#endif /* NETWORK_STRUCT_H_ */
