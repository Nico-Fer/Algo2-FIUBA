#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "gimnasio.h"
#include "personaje_principal.h"
#include "heap.h"

typedef struct juego{
	heap_t* heap_gimnasio;
	personaje_t* personaje;
	int estado;
}juego_t;

#endif /*__JUEGO_H__*/
