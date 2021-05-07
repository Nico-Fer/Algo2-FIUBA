#include "abb.h"
#include "lista.h"
#include "gimnasio.h"
#include "personaje_principal.h"
#include <string.h>
#include <stdio.h>

static const int ERROR = -1;
static const int EXITO = 1;
static const int NO_SE_ENCONTRO = 0;

static const int CANT_LEIDOS_PERSONAJE = 1;
static const int CANT_LEIDOS_POKEMON = 4;

static const char PERSONAJE = 'E';
static const char POKEMON = 'P';

static const int IGUAL = 0;
static const int MAYOR = 1;
static const int MENOR = -1;

static const int MAX_STAT = 63;

static const int CANT_MAX_POKE = 6;

#define LECTURA_PERSONAJE "%100[^\n]\n"
#define LECTURA_POKEMON "%100[^;];%i;%i;%i\n"

#define VERDE "\x1b[32;1m"
#define BLANCO "\x1b[37;1m"
#define AMARILLO "\x1b[33;1m"


int comparador_pokemon(void* pokemon1, void* pokemon2){
	int comparacion = strcmp(((pokemon_t*)pokemon1)->nombre_pokemon, ((pokemon_t*)pokemon2)->nombre_pokemon);

	if(comparacion>0) return MAYOR;

	if(comparacion<0) return MENOR;

	return IGUAL;
}

void deestructor_pokemon(void* pokemon){
	free((pokemon_t*)pokemon);
}

/*
* Inicializa los campos de mi pokemon, respecto a lo leido del archivo.
*/

void inicializar_pokemon_personaje(pokemon_t* pokemon_aux, char nombre_pokemon[MAX_NOMBRE], int velocidad, int ataque, int defensa){
	strcpy(pokemon_aux->nombre_pokemon, nombre_pokemon);
	pokemon_aux->velocidad = velocidad;
	pokemon_aux->ataque = ataque;
	pokemon_aux->defensa = defensa;
}

/*
*
*/

pokemon_t* crear_pokemon(char nombre_pokemon[MAX_NOMBRE], int velocidad, int ataque, int defensa){

	pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
	if(!pokemon) return NULL;

	inicializar_pokemon_personaje(pokemon, nombre_pokemon, velocidad, ataque, defensa);

	return pokemon;
}

/*
*
*/

void agregar_pokemon_para_combatir(personaje_t* personaje, FILE* archivo_personaje, int* leidos){

	char nombre_pokemon[MAX_NOMBRE];
	int velocidad, ataque, defensa;

	*leidos = fscanf(archivo_personaje, LECTURA_POKEMON, nombre_pokemon, &velocidad, &ataque, &defensa);

	if(*leidos==CANT_LEIDOS_POKEMON){ 

		pokemon_t* pokemon_aux = crear_pokemon(nombre_pokemon, velocidad, ataque, defensa);
		if(!pokemon_aux){
			*leidos = ERROR;
			return;
		}

		int pudo_encolar = lista_encolar(personaje->pokemon_para_combatir, pokemon_aux);

		if(pudo_encolar==ERROR) *leidos = ERROR;

	}else{
		*leidos = ERROR;
	}

}

/*
*
*/

void agregar_pokemon_a_la_caja(personaje_t* personaje, FILE* archivo_personaje, int* leidos){

	char nombre_pokemon[MAX_NOMBRE];
	int velocidad, ataque, defensa;

	*leidos = fscanf(archivo_personaje, LECTURA_POKEMON, nombre_pokemon, &velocidad, &ataque, &defensa);

	if(*leidos==CANT_LEIDOS_POKEMON){ 

		pokemon_t* pokemon_aux = crear_pokemon(nombre_pokemon, velocidad, ataque, defensa);
		if(!pokemon_aux){
			*leidos = ERROR;
			return;
		}

		int pudo_encolar = arbol_insertar(personaje->pokemon_en_caja, pokemon_aux);

		if(pudo_encolar==ERROR) *leidos = ERROR;

	}else{
		*leidos = ERROR;
	}

}

/*
*
*/

void agregar_pokemones(personaje_t* personaje, FILE* archivo_personaje, int* leidos){

	char caracter_principal;
	while(*leidos!=0 && *leidos!=ERROR){

		*leidos = fscanf(archivo_personaje, "%c;", &caracter_principal);

		if(*leidos==1 && caracter_principal==POKEMON && personaje->pokemon_para_combatir->cantidad < CANT_MAX_POKE){

			agregar_pokemon_para_combatir(personaje, archivo_personaje, leidos);

		}else if(*leidos==1 && caracter_principal==POKEMON){

			agregar_pokemon_a_la_caja(personaje, archivo_personaje, leidos);

		}else if(*leidos==1 && caracter_principal!=POKEMON){    //El archivo es invalido
			
			*leidos = ERROR;

		}else{                                                  // Llegue al fin del archivo
			
			*leidos = 0;

		}
	}
}

/*
*
*/

int leer_personaje(personaje_t* personaje, FILE* archivo_personaje){

	char caracter_principal;
	int leidos = fscanf(archivo_personaje, "%c;", &caracter_principal);

	if(leidos!=1 || caracter_principal!=PERSONAJE) return ERROR;

	leidos = fscanf(archivo_personaje, LECTURA_PERSONAJE, personaje->nombre);

	if(leidos!=CANT_LEIDOS_PERSONAJE) return ERROR;

	personaje->pokemon_para_combatir = lista_crear(deestructor_pokemon);
	if(!personaje->pokemon_para_combatir) return ERROR;

	personaje->pokemon_en_caja = arbol_crear(comparador_pokemon, deestructor_pokemon);
	if(!personaje->pokemon_en_caja) return ERROR;
	
	agregar_pokemones(personaje, archivo_personaje, &leidos);

	if(leidos==ERROR) return ERROR;

	return EXITO;
}

/*
*
*/

personaje_t* crear_personaje(const char* ruta_archivo){

	FILE* archivo_personaje = fopen(ruta_archivo, "r");
	if(!archivo_personaje) return NULL;

	personaje_t* personaje_nuevo = calloc(1, sizeof(personaje_t));
	if(!personaje_nuevo) return NULL;

	if(leer_personaje(personaje_nuevo, archivo_personaje)==ERROR){
		personaje_destruir(personaje_nuevo);
		fclose(archivo_personaje);
		return NULL;
	}

	if(personaje_nuevo->pokemon_para_combatir->cantidad==0){
		personaje_destruir(personaje_nuevo);
		fclose(archivo_personaje);
		return NULL;
	}

	fclose(archivo_personaje);
	
	return personaje_nuevo;
}

/*
*
*/

void personaje_destruir(personaje_t* personaje){

	if(personaje){
		lista_destruir(personaje->pokemon_para_combatir);
		arbol_destruir(personaje->pokemon_en_caja);
	}

	free(personaje);
}

/*
*
*/

int intercambio_pokemon(personaje_t* personaje, size_t posicion_pokemon_en_party, pokemon_t* pokemon_a_buscar_en_caja){

	if(!personaje || !pokemon_a_buscar_en_caja) return ERROR;

	pokemon_t* pokemon_en_party = lista_elemento_en_posicion(personaje->pokemon_para_combatir, posicion_pokemon_en_party-1);
	if(!pokemon_en_party) return NO_SE_ENCONTRO;

	pokemon_t* pokemon_en_caja = arbol_buscar(personaje->pokemon_en_caja, pokemon_a_buscar_en_caja);
	if(!pokemon_en_caja) return NO_SE_ENCONTRO;

	pokemon_t* pokemon_en_party_aux = crear_pokemon(pokemon_en_party->nombre_pokemon, pokemon_en_party->velocidad, pokemon_en_party->ataque, pokemon_en_party->defensa);
	if(!pokemon_en_party_aux) return ERROR;

	pokemon_t* pokemon_en_caja_aux = crear_pokemon(pokemon_en_caja->nombre_pokemon, pokemon_en_caja->velocidad, pokemon_en_caja->ataque, pokemon_en_caja->defensa);
	if(!pokemon_en_caja_aux) return ERROR;

	if(lista_encolar(personaje->pokemon_para_combatir, pokemon_en_caja_aux)==ERROR) return ERROR;
	
	if(lista_borrar_de_posicion(personaje->pokemon_para_combatir, posicion_pokemon_en_party-1, deestructor_pokemon)== ERROR) return ERROR;

	if(arbol_borrar(personaje->pokemon_en_caja, pokemon_en_caja)==ERROR) return ERROR;

	if(arbol_insertar(personaje->pokemon_en_caja, pokemon_en_party_aux)==ERROR) return ERROR;

	return EXITO;
}

/*
*
*/

int tomar_pokemon(personaje_t* personaje, pokemon_t* pokemon){

	if(!personaje || !pokemon) return ERROR;

	pokemon_t* pokemon_aux = crear_pokemon(pokemon->nombre_pokemon, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
	if(!pokemon_aux) return ERROR;

	if(arbol_insertar(personaje->pokemon_en_caja, pokemon_aux)==ERROR) return ERROR;

	return EXITO;
}

/*
*
*/ 
bool mostrar_pokemon_para_combatir(void* pokemon, void* extra){
	extra=extra;
	if(!pokemon)
		return false;
	printf(VERDE "%i) %13s %8i %12i %9i\n", (*(int*)extra)++, ((pokemon_t*)pokemon)->nombre_pokemon, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa);

	return true;
}

/*
*
*/

bool mostrar_pokemon_en_caja(void* pokemon, void* extra){
	extra=extra;
	if(pokemon)
		printf(BLANCO "%8s %8i %12i %9i\n", ((pokemon_t*)pokemon)->nombre_pokemon, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa);
	return false;
}

/*
*
*/

void mostrar_personaje(personaje_t* personaje){
	printf(AMARILLO "\nPokemones para combatir:\n");
	printf(AMARILLO"========================\n");
	printf(VERDE "Pos. |  Pokemon  |  Velocidad  |  Ataque |  Defensa \n");
	int extra = 1;
	lista_con_cada_elemento(personaje->pokemon_para_combatir, mostrar_pokemon_para_combatir, &extra);
	printf(AMARILLO "\nPokemones en caja:\n");
	printf(AMARILLO"==================\n");
	printf(BLANCO "Pokemon  |  Velocidad  |  Ataque |  Defensa \n");
	abb_con_cada_elemento(personaje->pokemon_en_caja, 0, mostrar_pokemon_en_caja, NULL);
}

/*
*
*/

bool mejorar_pokemon_para_combatir(void* pokemon, void* extra){
	extra=extra;
	if(!pokemon)
		return false;

	if(((pokemon_t*)pokemon)->ataque<MAX_STAT) ((pokemon_t*)pokemon)->ataque +=1;
	if(((pokemon_t*)pokemon)->defensa<MAX_STAT) ((pokemon_t*)pokemon)->defensa +=1;
	if(((pokemon_t*)pokemon)->velocidad<MAX_STAT) ((pokemon_t*)pokemon)->velocidad +=1;

	return true;
}

/*
*
*/

bool mejorar_pokemon_en_caja(void* pokemon, void* extra){
	extra=extra;
	if(pokemon){
		if(((pokemon_t*)pokemon)->ataque<MAX_STAT) ((pokemon_t*)pokemon)->ataque +=1;
		if(((pokemon_t*)pokemon)->defensa<MAX_STAT) ((pokemon_t*)pokemon)->defensa +=1;
		if(((pokemon_t*)pokemon)->velocidad<MAX_STAT) ((pokemon_t*)pokemon)->velocidad +=1;
	}
	return false;
}

/*
*
*/

void mejorar_personaje(personaje_t* personaje){
	if(!personaje) return;
	int extra=1;
	lista_con_cada_elemento(personaje->pokemon_para_combatir, mejorar_pokemon_para_combatir, &extra);
	abb_con_cada_elemento(personaje->pokemon_en_caja, 0, mejorar_pokemon_en_caja, NULL);
}