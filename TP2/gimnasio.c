#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "gimnasio.h"
#include "heap.h"
#include "personaje_principal.h"

static const int MAYOR = 1;
static const int MENOR = -1;
static const int IGUAL = 0;

static const char GIMNASIO = 'G';
static const char ENTRENADOR = 'E';
static const char LIDER = 'L';
static const char POKEMON = 'P';

static const int CANT_LEIDOS_GIM = 3;
static const int CANT_LEIDOS_ENTRENADOR = 1;
static const int CANT_LEIDOS_POKEMON = 4;

static const int ID_FUNCION_MINIMA = 1;
static const int ID_FUNCION_MAXIMA = 5;

static const int PRIMER_GIMNASIO = 0;
static const int MAS_DE_UN_GIMNASIO = 1;
static const int NO_HAY_GIMNASIO = -1;

static const int EXITO = 0;
static const int ERROR = -1;

static const int CANT_MAX_POKE = 6;

#define CYAN "\x1b[36;1m"

/*
* Comparador de elementos. Recibe dos elementos del heap de gimnasios y devuelve
 * 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
*/

int comparador(void* gim1, void* gim2){
	if(!gim1 || !gim2) return IGUAL;

	int numero1 = ((gimnasio_t*)gim1)->dificultad;
	int numero2 = ((gimnasio_t*)gim2)->dificultad;

	if(numero1>numero2){
		return MAYOR;
	}
	else {
		return MENOR;
	}
}

/*
*
*/

void destructor_lista_entrenadores(void* entrenador){
	free((entrenador_t*)entrenador);
}

/*
*
*/

void destrcutor_lista_pokemones(void* pokemon){
	free((pokemon_t*)pokemon);
}

/*
*
*/

void destruir_cola_pokemones(nodo_t* entrenador){
	if(!entrenador) return;
	lista_destruir(((entrenador_t*)(entrenador->elemento))->pokemones);
	destruir_cola_pokemones(entrenador->siguiente);
}

/*
* Destructor de elementos. Cada vez que un elemento deja el heap
 * se invoca al destructor pasandole
 * el elemento.
*/

void destructor_gimnasio(void* gimnasio){
	if(((gimnasio_t*)(gimnasio))->entrenadores){ //En el gimnasio existe una lista de entrenadores
		destruir_cola_pokemones(((gimnasio_t*)gimnasio)->entrenadores->nodo_inicio);
		lista_destruir(((gimnasio_t*)gimnasio)->entrenadores);
	}
	free(gimnasio);
}

/*
*
*/

int quitar_gimnasio(heap_t* heap_gimnasio){

	return(extraer_raiz(heap_gimnasio));
}

/*
*
*/

int quitar_entrenador(gimnasio_t* gimnasio){

	if(!gimnasio) return ERROR;
	if(!gimnasio->entrenadores) return ERROR;
	if(!gimnasio->entrenadores->nodo_inicio) return ERROR;

	lista_destruir(((entrenador_t*)(gimnasio->entrenadores->nodo_inicio->elemento))->pokemones);
	/*
	destructor_lista_entrenadores(((entrenador_t*)(gimnasio->entrenadores->nodo_inicio->elemento)));
*/

	return(lista_desapilar(gimnasio->entrenadores));
}

/*
* Recibe un puntero a un gimnasio valido y el archivo de gimnasio/s.
* Se reserva la memoria necesaria para un entrenador.
* Se agrega a la pila de entrenadores el entrenador creado. 
* En caso de que haya un error, se modifica el valor de leidos.
*/

void apilar_entrenador(gimnasio_t* gimnasio, FILE* archivo_gimnasio, int* leidos){

	if(gimnasio->entrenadores->nodo_inicio)
		if(((entrenador_t*)(gimnasio->entrenadores->nodo_inicio->elemento))->pokemones->cantidad==0){

			*leidos = ERROR;
			return;

		} //El entrenador o Lider que esta en el tope de la pila no tiene pokemones

	char nombre_entrenador[MAX_NOMBRE];
	*leidos = fscanf(archivo_gimnasio, "%100[^\n]\n", nombre_entrenador);

	if(*leidos==CANT_LEIDOS_ENTRENADOR){

		entrenador_t* entrenador_aux = calloc(1, sizeof(entrenador_t));

		if(!entrenador_aux){
			*leidos = ERROR;
			return;
		}

		strcpy(entrenador_aux->nombre_entrenador, nombre_entrenador);

		if(lista_apilar(gimnasio->entrenadores, entrenador_aux)==ERROR) *leidos = ERROR; //No se pudo apilar al entrenador

		((entrenador_t*)(gimnasio->entrenadores->nodo_inicio->elemento))->pokemones = lista_crear(destrcutor_lista_pokemones);

		if(!entrenador_aux->pokemones) *leidos = ERROR; //No se pudo crear la cola de pokemones
	}
}

/*
* Inicializa los campos de mi pokemon, respecto a lo leido del archivo.
*/

void inicializar_pokemon(pokemon_t* pokemon_aux, char nombre_pokemon[MAX_NOMBRE], int velocidad, int ataque, int defensa){
	strcpy(pokemon_aux->nombre_pokemon, nombre_pokemon);
	pokemon_aux->velocidad = velocidad;
	pokemon_aux->ataque = ataque;
	pokemon_aux->defensa = defensa;
}

/*
* Recibe un puntero a un gimnasio valido y el archivo de gimnasio/s.
* Se reserva la memoria necesaria para un pokemon.
* Se agrega a la lista de pokemones el pokemon creado. 
* En caso de que no se puedan agregar mas pokemones al entrenador, el pokemoon se destruye.
* En caso de que haya un error, se modifica el valor de leidos.
*/

void encolar_pokemones(gimnasio_t* gimnasio ,FILE* archivo_gimnasio, int* leidos){

	if(!gimnasio->entrenadores){ //No hay entrenadores en el gimnasio
		*leidos = ERROR;
		return;
	}

	char nombre_pokemon[MAX_NOMBRE];
	int velocidad, ataque, defensa;

	*leidos = fscanf(archivo_gimnasio, "%100[^;];%i;%i;%i\n", nombre_pokemon, &velocidad, &ataque, &defensa);

	if(*leidos==CANT_LEIDOS_POKEMON){ 

		pokemon_t* pokemon_aux = calloc(1, sizeof(pokemon_t));

		if(!pokemon_aux){ //No pude reservar la memoria para el pokemon
			*leidos = ERROR;
			return;
		}

		inicializar_pokemon(pokemon_aux, nombre_pokemon, velocidad, ataque, defensa);

		if(((entrenador_t*)(gimnasio->entrenadores->nodo_inicio->elemento))->pokemones->cantidad < CANT_MAX_POKE){

			int pudo_encolar = lista_encolar(((entrenador_t*)(gimnasio->entrenadores->nodo_inicio->elemento))->pokemones, pokemon_aux);

			if(pudo_encolar==ERROR)	*leidos = ERROR;

		}else{ //El entrenador tiene mas de 6 pokemones

			free(pokemon_aux);
		}

	}else{
		*leidos = ERROR;
	}
}

/*
* Recibe un puntero a un gimnasio valido y el archivo de gimnasio/s.
* En base a lo que se lea, se invocaran a sus respectivas funciones.
*/

void llenar_gimnasio(gimnasio_t* gimnasio ,FILE* archivo_gimnasio, int* leidos, int* hay_gimnasio, char* caracter_principal){

	while(*leidos!=0 && *leidos!=ERROR){

		*leidos = fscanf(archivo_gimnasio, "%c;", caracter_principal);

		if(*leidos==1 && *caracter_principal==GIMNASIO){ // Hay mas de un gimnasio

			*hay_gimnasio = MAS_DE_UN_GIMNASIO;
			*leidos = 0;

		}else if(gimnasio->entrenadores->cantidad==0 && *caracter_principal!=LIDER){ // El gim no tiene lider

			*leidos=ERROR;

		}else if((*leidos==1 && *caracter_principal == LIDER) || (*leidos==1 && *caracter_principal == ENTRENADOR)){ // El gim tiene entrenador

			apilar_entrenador(gimnasio, archivo_gimnasio, leidos);

		}else if(*leidos==1 && *caracter_principal == POKEMON){ //El gim tiene pokemon

			encolar_pokemones(gimnasio, archivo_gimnasio, leidos);

		}else if(*leidos==1 && *caracter_principal != POKEMON && *caracter_principal != LIDER && *caracter_principal != ENTRENADOR){ // El archivo viene con un mal formato

			*leidos=ERROR;

		}else{ //Llegue al fin del archivo
			*hay_gimnasio = NO_HAY_GIMNASIO;
			*leidos = 0;
		}
	}
}

/*
* Crea un gimnasio reservando la memoria necesaria.
* Devuelve un puntero al gimnasio creado o NULL en caso de error.
*/

gimnasio_t* crear_gimnasio(FILE* archivo_gimnasio, int* hay_gimnasio, int* leidos, char* caracter_principal){

	gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
	if(!gimnasio) return NULL;

	gimnasio->entrenadores = lista_crear(destructor_lista_entrenadores);
	if(!gimnasio->entrenadores) return NULL; 

	if(*hay_gimnasio==PRIMER_GIMNASIO)
		*leidos = fscanf(archivo_gimnasio, "%c;", caracter_principal);

	if(*leidos==1 && *caracter_principal == GIMNASIO)
			*leidos = fscanf(archivo_gimnasio, "%100[^;];%i;%i\n", gimnasio->nombre_gimnasio, &(gimnasio->dificultad), &(gimnasio->id_puntero_funcion));
	
	if(*leidos!= CANT_LEIDOS_GIM || gimnasio->id_puntero_funcion < ID_FUNCION_MINIMA || gimnasio->id_puntero_funcion > ID_FUNCION_MAXIMA){
		destructor_gimnasio(gimnasio);
		return NULL;
	} 

	llenar_gimnasio(gimnasio, archivo_gimnasio, leidos, hay_gimnasio, caracter_principal);

	if(*leidos==ERROR){
		destructor_gimnasio(gimnasio);
		return NULL;
	}

	return gimnasio;
}

/*
*
*/

int rellenar_heap(heap_t* heap_gimnasio, FILE* archivo_gimnasio){
	int hay_gimnasio = PRIMER_GIMNASIO;

	int pudo_insertar_gim = EXITO;

	char caracter_principal;

	while((hay_gimnasio==PRIMER_GIMNASIO || hay_gimnasio==MAS_DE_UN_GIMNASIO) && pudo_insertar_gim==EXITO){
		
		int leidos = 1;
		gimnasio_t* gim_nuevo = crear_gimnasio(archivo_gimnasio, &hay_gimnasio, &leidos, &caracter_principal);
		
		if(gim_nuevo){
			
			pudo_insertar_gim = heap_insertar(heap_gimnasio, gim_nuevo);
	
		}else{
			pudo_insertar_gim = ERROR;
		}	
	}
	return pudo_insertar_gim;
}

/*
*
*/

heap_t* crear_heap_gimnasio(heap_t* heap_gimnasio, const char* ruta_archivo){

	if(!heap_gimnasio){
		heap_t* heap_nuevo = heap_crear(comparador, destructor_gimnasio);
		if(!heap_nuevo) return NULL;
		heap_gimnasio =heap_nuevo;
	}

	FILE* archivo_gimnasio = fopen(ruta_archivo, "r");
	if(!archivo_gimnasio){
		heap_destruir(heap_gimnasio);
		return NULL;
	}	

	int pudo_insertar_gim = rellenar_heap(heap_gimnasio, archivo_gimnasio);

	fclose(archivo_gimnasio);

	if(pudo_insertar_gim==ERROR){
		heap_destruir(heap_gimnasio);
		return NULL;
	}

	return heap_gimnasio; 
}

/*
*
*/ 

bool mostrar_entrenadores(void* entrenador, void* extra){
	extra=extra;
	if(!entrenador)
		return false;
	printf(CYAN "%s\n", ((entrenador_t*)entrenador)->nombre_entrenador);
	printf("Pokemones: %i\n", (int)(((entrenador_t*)entrenador)->pokemones->cantidad));

	return true;
}

/*
*
*/

void mostrar_gimnasio(gimnasio_t* gimnasio){
	printf(CYAN "*%s*\n", gimnasio->nombre_gimnasio);
	printf(CYAN"| Dificultad : %i | Batalla: %i |\n", gimnasio->dificultad, gimnasio->id_puntero_funcion);
	printf(CYAN"ENTRENADORES\n");
	int extra = 1;
	lista_con_cada_elemento(gimnasio->entrenadores, mostrar_entrenadores, &extra);
}