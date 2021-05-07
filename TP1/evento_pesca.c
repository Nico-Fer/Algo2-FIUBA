#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "evento_pesca.h"


#define FORMATO_LECTURA "%100[^;];%i;%i;%100[^\n]\n"

#define MAX_ARCHIVO 100
#define MAX_EXTENSION 5

const int ERROR=-1;

const int CANT_LEIDOS = 4;

const int CANTIDAD_NULA = 0;

/*
*pre: Recibe un archivo y un puntero a pokemon.
*post: Devuelve la cantidad de elementos que se pudo leer del archivo.
*/

int leer_archivo(FILE * archivo_arrecife, pokemon_t* pokemon_aux){
	return fscanf(archivo_arrecife, FORMATO_LECTURA, (*pokemon_aux).especie, &((*pokemon_aux).velocidad), &((*pokemon_aux).peso), (*pokemon_aux).color);
}	

/*
*pre: Recibe un puntero a pokemon, la cantidad de pokemones que hay en el arrecife y un pokemon auxiliar, con todas sus estructuras validas.
*post: Devuelve un puntero a pokemon.
*/

pokemon_t* agregar_pokemon(pokemon_t* pokemones, int cant_pokemones, pokemon_t pokemon_aux){
	pokemon_t* pokemon_nuevo = realloc(pokemones, sizeof(pokemon_t)*((size_t)cant_pokemones));
	if(pokemon_nuevo==NULL)
		return pokemones;
	pokemones = pokemon_nuevo;
	pokemones[cant_pokemones-1]= pokemon_aux;
	return pokemones;
}	

/*
*
*
*/

arrecife_t* crear_arrecife(const char* ruta_archivo){
	char archivo_de_pokemones[MAX_ARCHIVO]= " ";
	char extension[MAX_EXTENSION]= " ";
	sscanf(ruta_archivo, "%[^.].%s", archivo_de_pokemones, extension);
	if (strcmp(extension, "txt")!=0){
		return NULL;
	}	
	FILE * archivo_arrecife = fopen(ruta_archivo, "r");
	if(archivo_arrecife==NULL){
		return NULL;
	}	
	pokemon_t pokemon_aux;
	int leidos = leer_archivo(archivo_arrecife, &pokemon_aux);
	if (leidos!=CANT_LEIDOS){
		fclose(archivo_arrecife);
		return NULL;
	}
	arrecife_t* nuevo_arrecife = malloc( sizeof(arrecife_t) );
	(*nuevo_arrecife).pokemon = NULL;
	(*nuevo_arrecife).cantidad_pokemon=0;
	bool lectura_valida = true;
	while(leidos==CANT_LEIDOS && lectura_valida==true){
		(*nuevo_arrecife).cantidad_pokemon++;
		(*nuevo_arrecife).pokemon = agregar_pokemon((*nuevo_arrecife).pokemon, (*nuevo_arrecife).cantidad_pokemon, pokemon_aux);
		if((*nuevo_arrecife).pokemon==NULL){
			free(nuevo_arrecife);
			nuevo_arrecife=NULL;
			lectura_valida=false;
		}	
		leidos = leer_archivo(archivo_arrecife, &pokemon_aux);
	}	
	fclose(archivo_arrecife);
	return nuevo_arrecife;
}	

/*
*
*
*/

void liberar_arrecife(arrecife_t* arrecife){
	if ((*arrecife).cantidad_pokemon>0){
		free((*arrecife).pokemon);
	}
	free(arrecife);
}	

/*
*
*
*/

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
	if ((*arrecife).pokemon!=NULL){
		for (int i = 0; i < (*arrecife).cantidad_pokemon; i++){
			mostrar_pokemon(&((*arrecife).pokemon[i]));
		}
	}
}	

/*
*pre:Recibe un vector de punteros, donde apunta a los pokemones que hay que agregar al acuario.
     Recibe un puntero a acuario, con todas sus estructuras validadas y la cantidad de pokemones
     que hay que agregar.
*post:Devuelve un puntero a un acuario de mayor tamaño.
*/

acuario_t* agrandar_acuario(acuario_t* acuario, int cant_seleccion, int posiciones_pokemones_a_trasladar[cant_seleccion], arrecife_t* arrecife){
	int i=0;
	bool es_puntero_valido = true;
	while(i < cant_seleccion && es_puntero_valido){
		(*acuario).cantidad_pokemon++;
		pokemon_t* ptr_pokemon_aux =agregar_pokemon((*acuario).pokemon, (*acuario).cantidad_pokemon, (*arrecife).pokemon[posiciones_pokemones_a_trasladar[i]]);
		if(ptr_pokemon_aux == NULL){
			es_puntero_valido = false;
		}
		(*acuario).pokemon = ptr_pokemon_aux;
		i++;	
	}
	return acuario;
}	

/*
*pre: Recibe un entero, donde este representa la posicion del pokemon a quitar.
      Recibe un puntero a arrecife, con todas sus estructuras validadas y la cantidad de pokemones
      que hay que quitar.
*post: Devuelve true si se pudo quitar el pokemon y el puntero a pokemon no apunte a NULL, sino devuelve false.
*/


bool quitar_pokemon(arrecife_t* arrecife, int posicion_pokemon){
	if (posicion_pokemon != (*arrecife).cantidad_pokemon-1){
		(*arrecife).pokemon[posicion_pokemon] = (*arrecife).pokemon[(*arrecife).cantidad_pokemon-1];
	}
	(*arrecife).cantidad_pokemon--;
	pokemon_t* ptr_pokemon_aux = realloc((*arrecife).pokemon, sizeof(pokemon_t)*(size_t)((*arrecife).cantidad_pokemon));
	if (ptr_pokemon_aux==NULL){
		return false;
	}
	else if(ptr_pokemon_aux==NULL && (*arrecife).cantidad_pokemon!=CANTIDAD_NULA){
		(*arrecife).pokemon = ptr_pokemon_aux;
		return false;
	}	
	else{
		(*arrecife).pokemon = ptr_pokemon_aux;
		return true;
	}
}	

/*
*
*
*/

int achicar_arrecife(arrecife_t* arrecife,  int cant_seleccion ,int posiciones_pokemones_a_trasladar[cant_seleccion]){
	int j=0;
	bool se_pudo_achicar = true;
	while(j< cant_seleccion && se_pudo_achicar){
		se_pudo_achicar=quitar_pokemon(arrecife, posiciones_pokemones_a_trasladar[(cant_seleccion-1)-j]);
		if (se_pudo_achicar){
			j++;
		}	
	}
	if(se_pudo_achicar == false && (*arrecife).cantidad_pokemon!=CANTIDAD_NULA){
		return ERROR;
	}
	return 0;
}	

/*
*
*
*/

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
	if(cant_seleccion == CANTIDAD_NULA)
		return 0;
	int cant_a_mover = 0;
	int posiciones_pokemones_a_trasladar[cant_seleccion];
	for (int i = 0; i < (*arrecife).cantidad_pokemon; i++){
		if (seleccionar_pokemon(&((*arrecife).pokemon[i])) && cant_a_mover<=cant_seleccion){
			cant_a_mover++;
			posiciones_pokemones_a_trasladar[cant_a_mover-1] = i;
		}
	}
	if(cant_a_mover<cant_seleccion){
		return ERROR;
	}	
	acuario = agrandar_acuario(acuario, cant_seleccion, posiciones_pokemones_a_trasladar, arrecife);
	if((*acuario).pokemon == NULL)
		return ERROR;
	int achicar = achicar_arrecife(arrecife, cant_seleccion, posiciones_pokemones_a_trasladar);
	if(achicar == ERROR)
		return ERROR;
	return 0;		
}	

/*
*
*
*/

acuario_t* crear_acuario(){
	acuario_t* nuevo_acuario = malloc(sizeof(acuario_t));
	(*nuevo_acuario).pokemon = NULL;
	(*nuevo_acuario).cantidad_pokemon=0;
	return nuevo_acuario;
}	

/*
*
*
*/

void liberar_acuario(acuario_t* acuario){
	if((*acuario).pokemon>0){
		free((*acuario).pokemon);
	}
	free(acuario);
}	

/*
*
*
*/

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	FILE * archivo_acuario = fopen("w", nombre_archivo);
	if(nombre_archivo==NULL){
		return ERROR;
	}
	for (int i = 0; i < (*acuario).cantidad_pokemon; i++){
		fprintf(archivo_acuario, "%s;%i;%i;%s\n", (*acuario).pokemon[i].especie, (*acuario).pokemon[i].velocidad, (*acuario).pokemon[i].peso, (*acuario).pokemon[i].color);
	}
	fclose(archivo_acuario);
	return 0;
}	