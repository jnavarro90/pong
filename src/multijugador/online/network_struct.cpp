#include "network_struct.h"
#include "../../opciones/opciones.h"

// Cliente

CNetwork_Data_Client::CNetwork_Data_Client()
{
  evento = 0;
}

void CNetwork_Data_Client::makeBuffer()
{
  buffer = evento;
}

char CNetwork_Data_Client::getBuffer()
{
  return buffer;
}

void CNetwork_Data_Client::readBuffer(char b)
{
  evento = b;
}

// Servidor

CNetwork_Data_Server::CNetwork_Data_Server()
{
  pelota_x = pelota_y = 0;
  pad1_y = pad2_y = 0;
  fs = 0;
  marcador1 = marcador2 = 0;
  sinUso = 0;
}

void CNetwork_Data_Server::makeBuffer()
{
  // Pelota
  buffer[0] = (pelota_x >> 8);
  buffer[1] = pelota_x;
  buffer[2] = (pelota_y >> 8);
  buffer[3] = pelota_y;

  // Pad1
  buffer[4] = pad1_y >> 8;
  buffer[5] = pad1_y;

  // Pad2
  buffer[6] = pad2_y >> 8;
  buffer[7] = pad2_y;

  // Flags
  buffer[8] = fs;

  // Marcador
  buffer[9] = marcador1;
  buffer[10] = marcador2;

  // Sin usar
  buffer[11] = sinUso;
}

char* CNetwork_Data_Server::getBuffer()
{
  return buffer;
}

void CNetwork_Data_Server::readBuffer(uchar* c)
{
  // Pelota
  pelota_x = (c[0] << 8) | c[1];
  pelota_y = (c[2] << 8) | c[3];

  // Pad1
  pad1_y = (c[4] << 8) | c[5];

  // Pad2
  pad2_y = (c[6] << 8) | c[7];

  // Flags
  fs = c[8];

  // Marcador;
  marcador1 = c[9];
  marcador2 = c[10];

  // Sin usar
  sinUso = c[11];
}

// SETTINGS

CNetwork_Data_Settings::CNetwork_Data_Settings()
{
  PANTALLA_ANCHO = opciones->PANTALLA_ANCHO;
  PANTALLA_ALTO = opciones->PANTALLA_ALTO;
  PAD_ANCHO = opciones->PAD_ANCHO;
  PAD_ALTO = opciones->PAD_ALTO;
  PELOTA_ALTO = opciones->PELOTA_ALTO;
  unused = 0;
}

void CNetwork_Data_Settings::makeBuffer()
{
  // PANTALLA
  buffer[0] = (PANTALLA_ANCHO >> 8);
  buffer[1] = PANTALLA_ANCHO;
  buffer[2] = (PANTALLA_ALTO >> 8);
  buffer[3] = PANTALLA_ALTO;

  // PAD_ALTO
  buffer[4] = PAD_ALTO >> 8;
  buffer[5] = PAD_ALTO;

  // PAD_ANCHO
  buffer[6] = PAD_ANCHO >> 8;
  buffer[7] = PAD_ANCHO;

  // PELOTA_ALTO
  buffer[8] = PELOTA_ALTO >> 8;
  buffer[9] = PELOTA_ALTO;

  // unused
  buffer[10] = unused >> 8;
  buffer[11] = unused;
}

char* CNetwork_Data_Settings::getBuffer()
{
  return buffer;
}

void CNetwork_Data_Settings::readBuffer(uchar* c)
{
  // PANTALLA
  PANTALLA_ANCHO = (c[0] << 8) | c[1];
  PANTALLA_ALTO = (c[2] << 8) | c[3];

  // PAD_ALTO
  PAD_ALTO = (c[4] << 8) | c[5];

  // PAD_ANCHO
  PAD_ANCHO = (c[6] << 8) | c[7];

  // PELOTA_ALTO
  PELOTA_ALTO = (c[8] << 8) | c[9];

  // unused
  unused = (buffer[10] << 8) | c[11];
}

