#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gimnasio.h"
#include "personaje_principal.h"
#include "juego.h"
#include "batallas.h"
#include "heap.h"
#include "utiles.h"

static const int EXITO = 1;
static const int ERROR = -1;

static const int GANO = 1;

static const int JUGANDO = 0;
static const int PERDIDO = -1;
static const int GANADO = 1;

static const int GIMNASIO_ACTUAL = 0;

static const char ENTRENADOR = 'E';
static const char GIMNASIO = 'G';
static const char SIMULAR = 'S';
static const char JUGAR = 'I';

static const char CAMBIAR_POKEMON = 'C';
static const char BATALLA = 'B';
static const char PROXIMO_COMBATE = 'N';
static const char PROXIMO_GIMNASIO = 'N';
static const char TOMAR_POKEMON = 'T';
static const char REINICIAR = 'R';
static const char FINALIZAR = 'F';

#define MAX_NOMBRE 100

#define CYAN "\x1b[36;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"

typedef int (*funcion_batalla)(void*,void*);

typedef struct busqueda_aux{
	char nombre_pokemon_en_caja[MAX_NOMBRE];
	pokemon_t* pokemon;
}busqueda_aux_t;

/*
* Crea un personaje reservando la memoria necesaria.
* Devuelve un puntero al juego creado o NULL en caso de error.
*/

juego_t* crear_juego(){

	juego_t* juego = calloc(1, sizeof(juego_t));
	if(!juego){
		printf("Error al crear juego\n");
		return NULL;
	}

	juego->estado = JUGANDO;

	return juego;
}

/*
*
*/

void mostrar_portada(){
	printf(ROJO"|--------------------------------------------------------------------------------------------------------------|\n");
	printf(ROJO"|"AMARILLO"     _____                      __                                       __                                   "ROJO"|\n");
	printf(ROJO"|"AMARILLO"    /  _  \\___  __ ____   _____/  |_ __ ______________    ______   ____ |  | __ ____   _____   ____   ____    "ROJO"|\n");
	printf(ROJO"|"AMARILLO"   /  /_\\  \\  \\/ // __ \\ /    \\   __\\  |  \\_  __ \\__  \\   \\____ \\ /  _ \\|  |/ // __ \\ /     \\ /  _ \\ /    \\   "ROJO"|\n");
	printf(ROJO"|"AMARILLO"  /    |    \\   /\\  ___/|   |  \\  | |  |  /|  | \\// __ \\_ |  |_> >  <_> )    <\\  ___/|  Y Y  (  <_> )   |  \\  "ROJO"|\n");
	printf(ROJO"|"AMARILLO"  \\____|__  /\\_/  \\___  >___|  /__| |____/ |__|  (____  / |   __/ \\____/|__|_ \\___  >__|_|  /\\____/|___|  /   "ROJO"|\n");
	printf(ROJO"|"AMARILLO"          \\/          \\/     \\/                       \\/  |__|               \\/    \\/      \\/            \\/   "ROJO"|\n");
	printf(ROJO"|--------------------------------------------------------------------------------------------------------------|\n");
	printf(NORMAL "Bienvenido a una nueva aventura pokemon!!\n");
}

/*
*
*/

void mostrar_opciones(){
	printf(NORMAL "Ingrese una de las siguientes opciones:\n");
	printf(".......................................\n");
	printf("-E) Ingrese el archivo del personaje principal.\n");
	printf("-G) Ingrese el archivo del gimnasio.\n");
	printf("-I) Comienza la partida.\n");
	printf("-S) Simula la partida.\n");
}

/*
*
*/

bool es_eleccion_inicio_correcta(char eleccion){
	return(eleccion==ENTRENADOR||eleccion==GIMNASIO||eleccion==SIMULAR||eleccion==JUGAR);
}

/*
* Muestra por pantalla el menu de inicio y le pide al usuario que ingrese una de las opciones mostradas.
* Devuelve el valor ingreaso por el usuario, siendo este ya validado.
*/

char menu_inicio(){
	char eleccion;

	mostrar_opciones();
	scanf(" %c", &eleccion);
	while(es_eleccion_inicio_correcta(eleccion)==false){
		mostrar_opciones();
		printf("Las unicas opciones validas son las mostradas por pantalla.\n");
		scanf(" %c", &eleccion);
	}

	return eleccion;
}

/*
*
*/

void mostrar_portada_personaje(){
	printf(CYAN"__________                                             __        \n");
	printf("\\______   \\ ___________  __________   ____ _____      |__| ____  \n");
	printf(" |     ___// __ \\_  __ \\/  ___/  _ \\ /   \\ \\__  \\     |  |/ __ \\ \n");
	printf(" |    |   \\  ___/|  | \\/\\___ (  <_> )   |  \\/ __ \\_   |  \\  ___/ \n");
	printf(" |____|    \\___  >__|  /____  >____/|___|  (____  /\\__|  |\\___  >\n");
	printf("               \\/           \\/           \\/     \\/\\______|    \\/\n");
	printf(NORMAL "Bienvenido al creador del personaje. Ingrese un archivo con el entrenador principal y sus pokemones:\n");
}

/*
* Pide el archivo de personaje al usuario.
* Si hay un error devuelve true, indicando que hay un error.
* Sino, agrego el personaje al juego y devuelvo false, indicando que no hay error.
*/

bool pedir_personaje(juego_t* juego){

	mostrar_portada_personaje();

	char ruta_archivo[MAX_NOMBRE];
	scanf("%s", ruta_archivo);

	personaje_t* personaje_nuevo = crear_personaje(ruta_archivo);
	if(!personaje_nuevo){
		printf(ROJO "Error al crear el personaje.\n");
		return true;
	}

	printf(VERDE "Personaje creado con exito\n");
	juego->personaje = personaje_nuevo;

	return false;
}

/*
*
*/

void mostrar_portada_gimnasio(){
	printf(CYAN "  ________.__                             .__        \n");
	printf(" /  _____/|__| _____   ____ _____    _____|__| ____  \n");
	printf("/   \\  ___|  |/     \\\\ /    \\__  \\  /  ___/  |/  _ \\ \n");
	printf("\\    \\_\\  \\  |  Y Y  \\   |  \\/ __ \\_\\___ \\|  (  <_> )\n");
	printf(" \\______  /__|__|_|  /___|  (____  /____  >__|\\____/ \n");
	printf("        \\/         \\/     \\/     \\/     \\/           \n");
	printf(NORMAL "Bienvenido al creador de gimnasio. Ingrese el archivo del gimnasio:\n");
}

/*
* Muestra la portada del creador de gimnasio por pantalla y le pide al usuario que ingrese el archivo.
* Si no hay ningun heap creado, invoco a la funcion crear_heap_gimnasio mandandole NULL y el archivo.
* Si ya hay un heap existente, invoco a la funcion crear_heap_gimnasio mandandole el heap existente y el archivo.
* Si este gimnasio se pudo crear devuelvo false, sino devuelvo true.
*/

bool pedir_gimnasio(juego_t* juego){

	mostrar_portada_gimnasio();

	char ruta_archivo[MAX_NOMBRE];
	scanf("%s", ruta_archivo);

	if(!juego->heap_gimnasio){
		heap_t* gim_nuevo = crear_heap_gimnasio(NULL, ruta_archivo);
		if(!gim_nuevo){
			printf(ROJO "Error al crear el gimnasio.\n");
			return true;
		}
		juego->heap_gimnasio = gim_nuevo;
	}
	else{
		juego->heap_gimnasio = crear_heap_gimnasio(juego->heap_gimnasio, ruta_archivo);
		if(!juego->heap_gimnasio){
			printf(ROJO "Error al crear el gimnasio.\n");
			return true;
		}
	}

	printf(VERDE "Gimnasio creado con exito\n");

	return false;	
}

/*
* Esta es la primera parte del juego. Donde se pide al usuario que opcion ingresar.
* Siendo estas opciones cargar el personaje, cargar el gimnasio, jugar la partida o simularla. 
*/

void introduccion_juego(juego_t* juego, char* eleccion, bool* hay_error){

	while(*eleccion!=JUGAR && *eleccion!=SIMULAR && !(*hay_error)){

		*eleccion = menu_inicio();
		system("clear");

		if(*eleccion==ENTRENADOR && !juego->personaje){
			*hay_error = pedir_personaje(juego);
		}
		else if(*eleccion==ENTRENADOR && juego->personaje){
			printf("Ya hay un personaje existente\n");
		}
		else if(*eleccion == GIMNASIO){
			*hay_error = pedir_gimnasio(juego);
		}
		else if((*eleccion==JUGAR || *eleccion==SIMULAR) && (!juego->personaje || !juego->heap_gimnasio)){

			if(!juego->personaje) printf(ROJO "No se pude jugar sin un personaje.\n");
			if(!juego->heap_gimnasio) printf(ROJO "No se puede jugar sin un gimnasio\n");

			*eleccion = ENTRENADOR; //Solamente para mantenerse dentro del while
		}else{
			*eleccion = *eleccion;
		}
	}	
}

/*
*
*/

bool es_eleccion_gimnasio_correcta(char eleccion){
	return(eleccion==ENTRENADOR||eleccion==GIMNASIO||eleccion==BATALLA||eleccion==CAMBIAR_POKEMON);
}

/*
*
*/

void mostrar_introduccion_gimnasio(){
	printf(NORMAL "Seleccione una de las siguientes opciones:\n");
	printf("-E) Muestra el entrenador principal junto sus pokemon\n");
	printf("-G) Muestra la informacion del gimnasio actual.\n");
	printf("-C) Permite cambiar los pokemones de batalla\n");
	printf("-B) Realiza la proxima batalla planificada\n");
}

/*
* Muestra el mennu del gimnasio por pantalla y le pide al usuario que ingrese una de las opciones mostradas.
* Devuelve el valor ingresado por el usuario, siendo este ya validado.
*/

char menu_gimnasio(juego_t* juego){
	mostrar_introduccion_gimnasio();
	char eleccion;
	scanf(" %c", &eleccion);
	while(es_eleccion_gimnasio_correcta(eleccion)==false){
		mostrar_introduccion_gimnasio();
		printf(NORMAL "Las opciones correctas son las mostradas por pantalla.\n");
		scanf(" %c", &eleccion);
	}
	return eleccion;
}

/*
* Funcion para el iterador interno del arbol.
* Si se encuentra el pokemon devuelve true, sino devuelve false.
*/

bool funcion_aux(void* pokemon, void* extra){
	if(pokemon){
		if(strcmp(((pokemon_t*)pokemon)->nombre_pokemon, ((busqueda_aux_t*)(extra))->nombre_pokemon_en_caja)==0){
			((busqueda_aux_t*)(extra))->pokemon = (pokemon_t*)pokemon;
			return true;
		}
	}	
	return false;
}

/*
* Le pide al usuario el nombre del pokemon en la caja que quiere agregar al party.
* Este se le asigna a una estructura auxiliar para invocar al iterador interno y buscarlo.
*/

void buscar_pokemon_en_caja(juego_t* juego, busqueda_aux_t* busqueda){
	printf(NORMAL "Ingrese el nombre del pokemon que se encuentra en la caja y lo quiere intercambiar:\n");
	scanf("%s",busqueda->nombre_pokemon_en_caja);
	abb_con_cada_elemento(juego->personaje->pokemon_en_caja, 0, funcion_aux, busqueda);
	while(busqueda->pokemon == NULL){
		printf(ROJO "No se encontro el pokemon ingresado. Por favor, escribalo devuelta\n");
		scanf("%s", busqueda->nombre_pokemon_en_caja);
		abb_con_cada_elemento(juego->personaje->pokemon_en_caja, 0, funcion_aux, busqueda);
	}
}

/*
* Le pide al usuario la posicion del pokemon en el party que quiere cambiar.
* Si esta posicion es valida, invoco a la funcion intercambiar_pokemon, mandandole la posicion ingresada.
*/

void buscar_pokemon_en_combatir(juego_t* juego, busqueda_aux_t busqueda, size_t* posicion_pokemon_combatir, int* pudo_intercambiar, bool* hay_error){
	printf(NORMAL "Ingrese la posicion del pokemon en la lista de combatir\n");
	scanf("%zu", posicion_pokemon_combatir);

	while(*posicion_pokemon_combatir > juego->personaje->pokemon_para_combatir->cantidad){
		printf("La posicion del pokemon debe estar dentro del rango\n");
		scanf("%zu", posicion_pokemon_combatir);
	}

	*pudo_intercambiar = intercambio_pokemon(juego->personaje, *posicion_pokemon_combatir, (busqueda.pokemon));
	if(*pudo_intercambiar==ERROR) *hay_error = true;
}

/*
* Intercambia entre un pokemon en el party y otro en la caja.
* Se utiliza una estructura auxiliar para la busqueda del pokemon en la caja.
*/

void cambiar_pokemon_personaje(juego_t* juego, bool* hay_error){
	size_t posicion_pokemon_combatir;
	busqueda_aux_t busqueda;
	busqueda.pokemon = NULL;
	buscar_pokemon_en_caja(juego, &busqueda);
	int pudo_intercambiar;
	buscar_pokemon_en_combatir(juego, busqueda, &posicion_pokemon_combatir, &pudo_intercambiar, hay_error);
	if(pudo_intercambiar==ERROR){
		printf(ROJO "Error al intercambiar pokemon\n");
		*hay_error = true;
		return;
	}
	if(pudo_intercambiar==EXITO) printf(VERDE "Se pudo realizar el intercambio\n");
}

/*
*
*/

void mostrar_portada_pelea(){
	printf(ROJO "                _______  _______  _        _______  _______  _  _ \n");
	printf("              (  ____ )(  ____ \\( \\      (  ____ \\(  ___  )( )( )\n");
	printf("              | (    )|| (    \\/| (      | (    \\/| (   ) || || |\n");
	printf("              | (____)|| (__    | |      | (__    | (___) || || |\n");
	printf("              |  _____)|  __)   | |      |  __)   |  ___  || || |\n");
	printf("              | (      | (      | |      | (      | (   ) |(_)(_)\n");
	printf("              | )      | (____/\\| (____/\\| (____/\\| )   ( | _  _ \n");
	printf("              |/       (_______/(_______/(_______/|/     \\|(_)(_)\n");
	printf("\n");
	printf("\n");
}

/*
*
*/

void mostrar_batalla(pokemon_t* poke1, pokemon_t* poke2){
	printf(AMARILLO"                                   _______                 \n");
	printf("                         |\\     /|(  ____ \\              \n");
	printf("                         | )   ( || (    \\/               \n");
	printf(CYAN"%5s"AMARILLO"                  | |   | || (_____                 "CYAN"%5s\n", poke1->nombre_pokemon, poke2->nombre_pokemon);
	printf(CYAN"Ataque:%5i"AMARILLO"             ( (   ) )(_____  )                 "CYAN"Ataque:%5i\n", poke1->ataque, poke2->ataque);
	printf(CYAN"Defensa:%5i"AMARILLO"             \\ \\_/ /       ) |                "CYAN"Defensa:%5i\n", poke1->defensa, poke2->defensa);
	printf(CYAN"Velocidad:%5i"AMARILLO"            \\   /  /\\____) | _              "CYAN"Velocidad:%5i\n", poke1->velocidad, poke2->velocidad);
	printf(AMARILLO"                            \\_/   \\_______)(_)           \n");
	printf("                                                         \n");
}

/*
*
*/

bool es_eleccion_batalla_correcta(char eleccion){
	return(eleccion==PROXIMO_COMBATE);
}

/*
* Le pide al usuario que ingrese el valor pedido para avanzar a la siguiente batalla.
*/

void mostrar_menu_batalla(){
	char eleccion;
	printf(NORMAL "Pulse N para pasar al proximo combate\n");
	scanf(" %c", &eleccion);
	while(es_eleccion_batalla_correcta(eleccion)==false){
		printf("Por favor, pulse N\n");
		scanf(" %c", &eleccion);
	}
}

/*
*
*/

void mostrar_portada_menu_victoria(){
	printf(VERDE"  ________.__                              .__                                          .___    ._._.\n");
	printf(" /  _____/|__| _____   ____   ___________  |__| ____      _________    ____ _____     __| _/____| | |\n");
	printf("/   \\  ___|  |/     \\ /    \\ /  ___/\\__  \\ |  |/  _ \\    / ___\\__  \\  /    \\__  \\   / __ |/  _ \\ | |\n");
	printf("\\    \\_\\  \\  |  Y Y  \\   |  \\___ \\  / __ \\|  (  <_> )  / /_/  > __ \\|   |  \\/ __ \\_/ /_/ (  <_> )|\\|\n");
	printf(" \\______  /__|__|_|  /___|  /____  >(____  /__|\\____/   \\___  (____  /___|  (____  /\\____ |\\____/____\n");
	printf("        \\/         \\/     \\/     \\/      \\/            /_____/     \\/     \\/     \\/      \\/      \\/\\/\n");
	printf("\n");
}

/*
*
*/

void mostrar_menu_victoria(){
	printf("Felicidades! Ganaste un gimnsaio y falta menos para ser un maestro pokemon.\n");
	printf("Pero antes de seguir luchando, hay que tomarse un descanso y pensar una estrategia.\n");
	printf("-T) Permite tomar un pokemon del lider y guardarlo en la caja\n");
	printf("-C) Permite cambiar los pokemon de batalla\n");
	printf("-N) Avanza al siguiente gimnasio\n");
}

/*
*
*/

bool es_eleccion_victoria_valida(char eleccion){
	return(eleccion==TOMAR_POKEMON||eleccion==PROXIMO_GIMNASIO||eleccion==CAMBIAR_POKEMON);
}

/*
* Funcion para lista_con_cada_elemento() que muestra los pokemones del lider.
*/ 

bool mostrar_pokemon_entrenador(void* pokemon, void* extra){
	extra=extra;
	if(!pokemon)
		return false;
	printf(VERDE "%i) %13s %8i %12i %9i\n", (*(int*)extra)++, ((pokemon_t*)pokemon)->nombre_pokemon, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa);

	return true;
}

/*
* Muestra los pokemones del lider, sus estadisticas y la posicion en la que se encuentran.
* Le pide al usario la posicion del pokemon que quiere tomar.
* Si esta es valida, toma el pokemon del lider y lo guarda en la caja del personaje.
*/

void tomar_pokemon_lider(juego_t* juego, bool* hay_error, int* tomo_pokemon){

	int extra = 1;
	lista_con_cada_elemento(((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones, mostrar_pokemon_entrenador, &extra);

	printf("Ingrese la posicion del pokemon que quiere tomar\n");
	size_t eleccion_pokemon;
	scanf("%zu", &eleccion_pokemon);

	while(eleccion_pokemon>((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones->cantidad){
		printf("La posicion del pokemon debe estar dentro del rango\n");
		scanf("%zu", &eleccion_pokemon);
	}

	*tomo_pokemon = tomar_pokemon(juego->personaje, lista_elemento_en_posicion(((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones, eleccion_pokemon-1));

	if(*tomo_pokemon==ERROR){
		printf("Error al tomar pokemon\n");
		*hay_error = true;
	} 

	printf(VERDE "Se pudo tomar el pokemon\n");
}

/*
* Muestra por pantalla el menu de victoria y le pide al usuario que ingrese una de las opciones mostradas.
*/

void menu_victoria(juego_t* juego, bool* hay_error){
	int tomo_pokemon = 0;
	char eleccion = ENTRENADOR;
	while(eleccion!=PROXIMO_GIMNASIO && !(*hay_error)){
		system("clear");
		mostrar_portada_menu_victoria();
		mostrar_menu_victoria();
		scanf(" %c", &eleccion);
		while(es_eleccion_victoria_valida(eleccion)==false){
			system("clear");
			mostrar_menu_victoria();
			printf("Las unicas opciones validas son las mostradas por pantalla\n");
			scanf(" %c", &eleccion);
		}

		if(eleccion==CAMBIAR_POKEMON) cambiar_pokemon_personaje(juego, hay_error);

		if(eleccion==TOMAR_POKEMON && tomo_pokemon==0){
			tomar_pokemon_lider(juego, hay_error, &tomo_pokemon);
		}
		else if(eleccion==TOMAR_POKEMON && tomo_pokemon==EXITO){
			printf("Ya tomo un pokemon del lider\n");
		} 
	}

}

/*
* Recorre los entrenadres del gimnasio y los pokemones de cada entrenador.
* Invoca a la funcion batalla con cada pokemon.
* Si el usuario pierde se modifica el estado del juego.
* Si el usuario gana el gimnasio, le aparecera el menu de victoria.
*/

void batalla(juego_t* juego, bool* hay_error, funcion_batalla funcion_batalla, char modo_de_juego){

	int resultado_pelea;

	while(juego->estado==JUGANDO && ((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->cantidad>0 && !(*hay_error)){

		size_t posicion_poke_personaje = 0;
		size_t posicion_poke_entrenador= 0;

		while(juego->estado==JUGANDO && posicion_poke_personaje<juego->personaje->pokemon_para_combatir->cantidad && posicion_poke_entrenador < ((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones->cantidad && !(*hay_error)){

			system("clear");
			if(modo_de_juego==JUGAR){

				mostrar_portada_pelea();
			mostrar_batalla(lista_elemento_en_posicion(juego->personaje->pokemon_para_combatir, posicion_poke_personaje), lista_elemento_en_posicion(((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones, posicion_poke_entrenador));
			}

			resultado_pelea = funcion_batalla(lista_elemento_en_posicion(juego->personaje->pokemon_para_combatir, posicion_poke_personaje), lista_elemento_en_posicion(((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones, posicion_poke_entrenador));

			if(resultado_pelea==GANO){

				if(modo_de_juego == JUGAR) printf(VERDE "Ganaste la pelea\n");
				mejorar_personaje(juego->personaje);
				posicion_poke_entrenador++;

			}else{

				if(modo_de_juego == JUGAR) printf(ROJO "Perdiste la pelea\n");
				posicion_poke_personaje++;
			}
			if(modo_de_juego==JUGAR) mostrar_menu_batalla();
		}

		if(posicion_poke_personaje >= juego->personaje->pokemon_para_combatir->cantidad){
			juego->estado = PERDIDO;
		}
		if(posicion_poke_entrenador >= ((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->pokemones->cantidad){

			if(modo_de_juego==JUGAR){
				printf(VERDE "Has vencido al entrenador %s\n", ((entrenador_t*)(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->nodo_inicio->elemento))->nombre_entrenador);
				detener_el_tiempo(1);
			}	

			if(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->cantidad==1 && modo_de_juego==JUGAR){
				menu_victoria(juego, hay_error);
			}
			quitar_entrenador((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]));
		}
	}
}

/*
*
*/

void mostrar_portada_derrota(){
	printf(ROJO "______            _ _     _            __\n");
	printf("| ___ \\          | (_)   | |        _ / /\n");
	printf("| |_/ /__ _ __ __| |_ ___| |_ ___  (_) | \n");
	printf("|  __/ _ \\ '__/ _` | / __| __/ _ \\   | | \n");
	printf("| | |  __/ | | (_| | \\__ \\ ||  __/  _| | \n");
	printf("\\_|  \\___|_|  \\__,_|_|___/\\__\\___| (_) | \n");
	printf("                                      \\_\\\n");
	printf("\n");
}

/*
*
*/

void mostrar_menu_derrota(){
	printf(AMARILLO "Has perdido la partida :(\n");
	printf("Porfavor ingrese una de las siguientes opciones: \n");
	printf("-C) Permite cambiar los pokemon de batalla\n");
	printf("-R) Reintenta el gimnasio\n");
	printf("-F) Finaliza el gimnasio\n");
}

/*
*
*/

bool es_eleccion_derrota_correcta(char eleccion){
	return(eleccion==CAMBIAR_POKEMON||eleccion==REINICIAR||eleccion==FINALIZAR);
}

/*
* Muestra por pantalla al menu de derrota y le pide al usuario que ingrese una de las opciones mostradas.
* Devuelve el valor ingresado por el usuario, siendo este valido.
*/

char menu_derrota(juego_t* juego, bool* hay_error){
	
	char eleccion = ENTRENADOR; // Solo para inicializar la variable
	while(eleccion!=FINALIZAR && eleccion!=REINICIAR && !(*hay_error)){
		system("clear");
		mostrar_portada_derrota();
		mostrar_menu_derrota();
		scanf(" %c", &eleccion);
		while(es_eleccion_derrota_correcta(eleccion)==false){
			system("clear");
			mostrar_menu_derrota();
			printf("Las unicas opciones correctas son las mostradas por pantalla\n");
			scanf(" %c", &eleccion);
		}
		if(eleccion==CAMBIAR_POKEMON) cambiar_pokemon_personaje(juego, hay_error);
	}
	return eleccion;
}

/*
* Determina que funcion batalla invocar segun el id recibido.
*/

funcion_batalla determinar_funcion_batalla(int id_puntero_funcion){
	funcion_batalla funcion_batalla;
	if(id_puntero_funcion==1){
		funcion_batalla = funcion_batalla_1;
	}else if(id_puntero_funcion==2){
		funcion_batalla = funcion_batalla_2;
	}else if(id_puntero_funcion==3){
		funcion_batalla = funcion_batalla_3;
	}else if(id_puntero_funcion==4){
		funcion_batalla = funcion_batalla_4;
	}else{
		funcion_batalla = funcion_batalla_5;
	}
	return funcion_batalla;
}

/*
*
*/

void mostrar_portada_victoria(){
	system("clear");
	printf(CYAN" _   _ _      _             _         __  \n");
	printf("| | | (_)    | |           (_)        \\ \\ \n");
	printf("| | | |_  ___| |_ ___  _ __ _  __ _  (_) |\n");
	printf("| | | | |/ __| __/ _ \\| '__| |/ _` |   | |\n");
	printf("\\ \\_/ / | (__| || (_) | |  | | (_| |  _| |\n");
	printf(" \\___/|_|\\___|\\__\\___/|_|  |_|\\__,_| (_) |\n");
	printf("                                      /_/ \n");
	printf("\n");
	printf("Felicidades!! Ganaste en todos los gimnasios. Ahora eres un maestro pokemon.\n");
}

/*
* Recibe un juego ya validado, un valor booleano inicializado que indica si hay un error y el modo de juego.
* Juega el juego indicando en todo momento al usuario en donde esta.
*/

void jugar_juego(juego_t* juego, bool* hay_error, char modo_de_juego){
	system("clear");
	char eleccion;

	while((juego->estado) == JUGANDO && !(*hay_error)){
		
		if(modo_de_juego == SIMULAR){
			eleccion = BATALLA;
		}else{
			eleccion = menu_gimnasio(juego);
		}

		if(eleccion==ENTRENADOR && modo_de_juego==JUGAR){
			system("clear");
			mostrar_personaje(juego->personaje);
		}
		else if(eleccion==GIMNASIO && modo_de_juego==JUGAR){
			system("clear");
			mostrar_gimnasio((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]));
		}
		else if(eleccion==CAMBIAR_POKEMON && modo_de_juego==JUGAR){
			cambiar_pokemon_personaje(juego, hay_error);
		}
		else{

			funcion_batalla funcion_batalla = determinar_funcion_batalla(((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->id_puntero_funcion);
			batalla(juego, hay_error, funcion_batalla, modo_de_juego);

			if(juego->estado==JUGANDO && ((gimnasio_t*)(juego->heap_gimnasio->vector[GIMNASIO_ACTUAL]))->entrenadores->cantidad==0){
				quitar_gimnasio(juego->heap_gimnasio);
			}
			if(juego->estado==JUGANDO && juego->heap_gimnasio->cant_elementos==0){
				mostrar_portada_victoria();
				juego->estado = GANADO;
			}
			if(juego->estado == PERDIDO){

				eleccion = menu_derrota(juego, hay_error);

				if(eleccion == REINICIAR){
					juego->estado = JUGANDO;
				}
			}
		}
	}
}

/*
* Recibe un puntero a un juego y libera la memoria.
*/

void juego_destruir(juego_t* juego){

	personaje_destruir(juego->personaje);
	heap_destruir(juego->heap_gimnasio);

	free(juego);
}

int main(){

	juego_t* juego = crear_juego();
	if(!juego) return ERROR;

	mostrar_portada();
	char eleccion = ENTRENADOR;  //Le asigno este valor solamente para inicializar la variable
	bool hay_error = false;

	introduccion_juego(juego, &eleccion, &hay_error);
	if(hay_error) {
		juego_destruir(juego);
		return ERROR;
	}

	if(eleccion==JUGAR){
		jugar_juego(juego, &hay_error, JUGAR);
	}else{
		jugar_juego(juego, &hay_error, SIMULAR);
	}

	if(hay_error==true){
		juego_destruir(juego);
		return ERROR;
	}

	juego_destruir(juego);
	return 0;
}