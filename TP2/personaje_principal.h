#ifndef __PERSONAJE_PRINCIPAL_H__
#define __PERSONAJE_PRINCIPAL_H__

#include "abb.h"
#include "lista.h"

#define MAX_NOMBRE 100

typedef struct personaje{
	char nombre[MAX_NOMBRE];
	lista_t* pokemon_para_combatir;
	abb_t* pokemon_en_caja;
}personaje_t;

/*
* Crea un personaje con el archivo recibido, reservando la memoria necesaria.
* Devuelve un puntero al personaje creado o NULL en caso de error.
*/

personaje_t* crear_personaje(const char* ruta_archivo);

/*
*Recibe un puntero a un personaje y libera la memoria.
*/

void personaje_destruir(personaje_t* personaje);

/*
* Recibe un puntero que apunta a un pokemon que esta en la caja. 
* Y la posicion del pokemon en combatir.
* Se realiza un intercambio de pokemones entre la lista de combatir y la caja.
* Devuelve 1 en caso de exito ,-1 en caso de error y 0 si no se encuentra uno de los pokemon.
*/

int intercambio_pokemon(personaje_t* personaje, size_t posicion_pokemon_en_party, pokemon_t* pokemon_a_buscar_en_caja);

/*
* Recibe un puntero al pokemon del lider y lo agrega a la caja del personaje.
* Devuelve 1 en caso de exito y -1 en caso de error.
*/

int tomar_pokemon(personaje_t* personaje, pokemon_t* pokemon);

/*
* Muestra al personaje junto a sus pokemones.
*/

void mostrar_personaje(personaje_t* personaje);

/*
* Mejora en 1 las estadisticas de todos los pokemon del personaje.
*/

void mejorar_personaje(personaje_t* personaje);

#endif /*__PERSONAJE_PRINCIPAL_H__*/