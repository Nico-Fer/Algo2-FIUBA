#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include <stdio.h>
#include "lista.h"
#include "heap.h"

#define MAX_NOMBRE 100

typedef struct gimnasio{
	char nombre_gimnasio[MAX_NOMBRE];
	lista_t* entrenadores;
	int dificultad;
	int id_puntero_funcion;
}gimnasio_t;

typedef struct entrenador{
	char nombre_entrenador[MAX_NOMBRE]; 
	lista_t* pokemones;
}entrenador_t;

typedef struct pokemon{
	char nombre_pokemon[MAX_NOMBRE];
	int velocidad;
	int defensa;
	int ataque;
}pokemon_t;

/*
* Si recibe NULL, crea un heap de gimnasios reservando la memoria necesaria.
* Si recibe un heap ya existente, lee el archivo, inserta los gimnasios y devuelve un puntero al mismo heap.
* Devuelve un puntero al heap creado o NULL en caso de error.
*/

heap_t* crear_heap_gimnasio(heap_t* heap_gimnasio, const char* ruta_archivo);

/*
* Quita al entrenador o lider de la pila de entrenadores, con sus respectivos pokemones.
* Devuelve 1 en caso de exito o -1 en caso de error.
*/

int quitar_entrenador(gimnasio_t* gimnasio);

/*
* Quita el primer gimnasio que se encuentra en el heap de gimnasios.
* Devuelve 1 en caso de exito o -1 en caso de error.
*/

int quitar_gimnasio(heap_t* heap_gimnasio);

/*
*Muestra el gimnasio por pantalla y asus respectivos entrenadores
*/

void mostrar_gimnasio(gimnasio_t* gimnasio);

#endif /*__GIMNASIO_H__*/