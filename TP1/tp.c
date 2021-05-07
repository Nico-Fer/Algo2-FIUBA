#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "evento_pesca.h"

const int VELOCIDAD_MINIMA = 100;
const int MAX_VOCALES = 5;

const int ORDENES_MISTY = 5;
const int CANT_SELECCION = 5;

const char VOCAL_MINUSCULA1 = 'a';
const char VOCAL_MINUSCULA2 = 'e';
const char VOCAL_MINUSCULA3 = 'i';
const char VOCAL_MINUSCULA4 = 'o';
const char VOCAL_MINUSCULA5 = 'u';
const char VOCAL_MAYUSCULA1 = 'A';
const char VOCAL_MAYUSCULA2 = 'E';
const char VOCAL_MAYUSCULA3 = 'I';
const char VOCAL_MAYUSCULA4 = 'O';
const char VOCAL_MAYUSCULA5 = 'U';

static const int ERROR = -1;

#define POKEMON_A_NERFEAR "Meowtwo"
#define POKEMON_GRANDOTE "Snorlax"

#define COLOR_DE_BOKITA1 "azul"
#define COLOR_DE_BOKITA2 "amarillo"

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Devuelve true si el pokemon se llama Meowtwo y su velocidad es mayor o igual a VLOCIDAD_MINIMA, sino devuelve false.
*/

bool necesita_un_nerfeo(pokemon_t* pokemon){
	return(((*pokemon).velocidad>=VELOCIDAD_MINIMA)&&(strcmp((*pokemon).especie, POKEMON_A_NERFEAR)==0));
}	

/*
*pre: Recibe un caracter.
*post: Devuelve true si el caracter es una vocal.
*/

bool es_vocal(char letra){
	return(letra==VOCAL_MINUSCULA1||letra==VOCAL_MAYUSCULA1||letra==VOCAL_MINUSCULA2||letra==VOCAL_MAYUSCULA2||letra==VOCAL_MINUSCULA3||letra==VOCAL_MAYUSCULA3||letra==VOCAL_MINUSCULA4||letra==VOCAL_MAYUSCULA4||letra==VOCAL_MINUSCULA5||letra==VOCAL_MAYUSCULA5);
}	

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Devuelve true si la cantidad de vocales de la especie de el pokemon es menor o igual que MAX_VOCALES.
*/

bool muchas_vocales(pokemon_t* pokemon){
	int cant_letras= (int) strlen((*pokemon).especie);
	int cant_vocales=0;
	for (int i = 0; i < cant_letras; i++){
		if(es_vocal((*pokemon).especie[i])){
			cant_vocales++;
		}	
	}
	if(cant_vocales<=MAX_VOCALES){
		return true;
	}	
	else{
		return false;
	}	
}

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Devuelve true si el color del pokemon es amarillo o azul.
*/

bool es_poke_bostero(pokemon_t* pokemon){
	printf("es bostero\n");
	return((strcmp((*pokemon).color, COLOR_DE_BOKITA2))==0 ||(strcmp((*pokemon).color, COLOR_DE_BOKITA1))==0);
}	

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Devuelve true si la velocidad del pokemon es mayor o igual que la velocidad minima, sino devuelve false.
*/

bool es_poke_flash(pokemon_t* pokemon){
	return((*pokemon).velocidad>=VELOCIDAD_MINIMA);
}	

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Si el pokemon es snorlax devuelve true, sino false.
*/

bool es_snorlax_valido(pokemon_t* pokemon){
	if(strcmp((*pokemon).especie, POKEMON_GRANDOTE)==0){
		return true;
	}	
	else{
		return false;
	}	
}	

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Imprime por pantalla el pokemon.
*/

void mostrar_pokemon_normal(pokemon_t* pokemon){
	printf("|Especie: %s|Peso: %i|Velocidad: %i|Color: %s|\n", (*pokemon).especie, (*pokemon).peso, (*pokemon).velocidad, (*pokemon).color);
}	

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Imprime por pantalla el pokemon.
*/

void mostrar_pokemon_pergamino(pokemon_t* pokemon){
	printf("  _______________________________________\n");
	printf(" /\\                                    \\ \n");
	printf("|  |                                     |\n");
	printf(" \\|             %5s -- %5s              | \n", (*pokemon).especie, (*pokemon).color);
	printf("   |                                     |\n");
	printf("   |                                     |\n");
	printf("   |                                     |\n");
	printf("   |     Peso: %5i -- Velocidad: %5i     |\n", (*pokemon).peso, (*pokemon).velocidad);
	printf("   |                                     |\n");
	printf("   |                                     |\n");
	printf("   |                                     |\n");
	printf("   |   _______________________________________\n");
	printf("   |  /                                      /\n");
	printf("   |_/______________________________________/\n");
}	

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Imprime por pantalla el pokemon.
*/

void mostrar_pokemon_tablero(pokemon_t* pokemon){
	printf(" _| |_______________________________| |_\n");
	printf("(_  ________________________________   _)\n");
	printf("  | |         %5s -- %5s            | |\n", (*pokemon).especie, (*pokemon).color);
	printf("  | |                               | |\n");
	printf("  | |                               | |\n");
	printf("  | |  Peso: %5i -- Velocidad: %5i  | |\n", (*pokemon).peso, (*pokemon).velocidad);
	printf(" _| |_______________________________| |_\n");
	printf("(_  ________________________________   _)\n");
	printf("  | |                               | | \n");
}

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Imprime por pantalla el pokemon.
*/

void mostrar_pokemon_etiqueta(pokemon_t* pokemon){
	printf(" _____________________________________\n");
	printf("|                                     \\ \n");
	printf("|           %5s -- %5s                 \\ \n", (*pokemon).especie, (*pokemon).color);
	printf("|                                       \\ \n");
	printf("|                                 //\\   \\ \n");
	printf("|                                 \\//   //\n");
	printf("|                                       // \n");
	printf("|    Peso: %5i -- Velocidad: %5i       // \n", (*pokemon).peso, (*pokemon).velocidad);
	printf("|                                     //\n");
	printf("|____________________________________//\n");
}

/*
*pre: Recibe uu puntero a un pokemon, con sus estructuras ya validadas.
*post: Imprime por pantalla el pokemon.
*/

void mostrar_pokemon_ordenado(pokemon_t* pokemon){
	printf("{%12s}{%12i}{%12i}{%12s}\n", (*pokemon).especie, (*pokemon).peso, (*pokemon).velocidad, (*pokemon).color);
}

/*
*pre: 
*post: 
*/

void asignar_mostrar_pokemones(void (*mostrar_pokemones[ORDENES_MISTY])(pokemon_t*)){
	mostrar_pokemones[0]= mostrar_pokemon_normal;
	mostrar_pokemones[1]= mostrar_pokemon_pergamino;
	mostrar_pokemones[2]= mostrar_pokemon_etiqueta;
	mostrar_pokemones[3]= mostrar_pokemon_ordenado;
	mostrar_pokemones[4]= mostrar_pokemon_tablero;
}	

/*
*pre: 
*post: 
*/

void asignar_trasladar_pokemones(bool (*seleccion_pokemones[ORDENES_MISTY]) (pokemon_t*)){
	seleccion_pokemones[0] = es_snorlax_valido;
	seleccion_pokemones[1] = es_poke_flash;
	seleccion_pokemones[2] = es_poke_bostero;
	seleccion_pokemones[3] = muchas_vocales;
	seleccion_pokemones[4] = necesita_un_nerfeo;
}	


int main(int argc, char* argv[]){
	arrecife_t* arrecife = crear_arrecife(argv[1]);
	if(arrecife==NULL){
		printf("Error al crear el arrecife.\n");
		return ERROR;
	}	
	acuario_t* acuario = crear_acuario();
	if(acuario==NULL){
		printf("Error al crear el acuario.\n");
		return ERROR;
	}
	bool (*seleccion_pokemones[ORDENES_MISTY]) (pokemon_t*);
	asignar_trasladar_pokemones(seleccion_pokemones);
	void (*mostrar_pokemones[ORDENES_MISTY])(pokemon_t*);
	asignar_mostrar_pokemones(mostrar_pokemones);
	int i = 0;
	int se_pudo_trasladar=0;
	while(i<ORDENES_MISTY && se_pudo_trasladar!=ERROR){
		se_pudo_trasladar = trasladar_pokemon(arrecife, acuario, seleccion_pokemones[i], CANT_SELECCION);
		censar_arrecife(arrecife, mostrar_pokemones[i]);
		i++;
	}	
	if(se_pudo_trasladar!=ERROR){
		guardar_datos_acuario(acuario, argv[2]);
		liberar_arrecife(arrecife);	
		liberar_acuario(acuario);
	}
	else{
		printf("Error al trasladar pokemones.\n");
		liberar_arrecife(arrecife);	
		liberar_acuario(acuario);
		return ERROR;
	}
	return 0;  
}