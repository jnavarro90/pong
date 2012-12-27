#include "network_struct.h"

// Datos servidor
void SdataToChar(network_data_server_t* t, uchar c[_NET_BYTES_])
{
  // Pelota
  c[0] = (t->pelota_x >> 8);
  c[1] = t->pelota_x;
  c[2] = (t->pelota_y >> 8);
  c[3] = t->pelota_y;

  // Pad1
  c[4] = (t->pad1_y >> 8);
  c[5] = t->pad1_y;

  // Pad2
  c[6] = (t->pad2_y >> 8);
  c[7] = t->pad2_y;

  // Flags
  c[8] = t->fs;

  // Marcador
  c[9] = (t->marcador1);
  c[10] = (t->marcador2);

  // Sin usar
  c[11] = (t->sinUso);

}

void charToSdata(uchar c[_NET_BYTES_], network_data_server_t* t)
{
  // Pelota
  t->pelota_x = (c[0] << 8) | c[1];
  t->pelota_y = (c[2] << 8) | c[3];

  // Pad1
  t->pad1_y = (c[4] << 8) | c[5];

  // Pad2
  t->pad2_y = (c[6] << 8) | c[7];

  // Flags
  t->fs = c[8];

  // Marcador;
  t->marcador1 = c[9];
  t->marcador2 = c[10];

  // Sin usar
  t->sinUso = c[11];
}

// Datos cliente
void CdataToChar(network_data_client_t* t, uchar c)
{
  c = t->evento;
}
void charToCdata(uchar c, network_data_client_t* t)
{
  t->evento = c;
}



/*void int16ToChar(uint16 in[4], unsigned char c[8])
{
  for(int i = 0; i < 8; i+=2)
  {
	   c[i] = (in[i/2] >> 8);
	   c[i+1] = (in[i/2]);
  }
}

void charToInt16(unsigned char c[8], uint16 in[4])
{
  for(int j = 0; j < 4; j++)
  {
	   in[j] = (c[j*2] << 8) | c[j*2 + 1];
  }
}*/


