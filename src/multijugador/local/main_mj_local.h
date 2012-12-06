#ifndef MAIN_MJ_LOCAL_H_
#define MAIN_MJ_LOCAL_H_

#include "../../temporizador.h"
#include "pelota_mj_local.h"
#include "pad_mj_local.h"
#include "../marcador.h"
#include "vars.h"

#include "cpu/pelota_cpu.h"
#include "cpu/pad_cpu.h"

extern const int FRAMES_PER_SECOND;

extern bool multijugador_local_cargar();

extern void multijugador_local_limpiar();

extern void main_mj_local();


#endif /* MAIN_MJ_LOCAL_H_ */
