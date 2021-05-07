#include "gimnasio.h"
#include "batallas.h"
#include "personaje_principal.h"
#include <string.h>

static const int GANA_POKEMON1 = 1;
static const int GANA_POKEMON2 = -1;

static const int VELOCIDAD_MINIMA_POKE_RAPIDO = 50;
static const int DEFENSA_MINIMA_POKE_TANQUE = 40;

/*
* Gana el pokemon con nombre mas largo.
*/

int funcion_batalla_1(void* pkm_1, void* pkm_2){

	size_t nombre1 = strlen(((pokemon_t*)pkm_1)->nombre_pokemon);
	size_t nombre2 = strlen(((pokemon_t*)pkm_2)->nombre_pokemon);

	return((nombre1>=nombre2)?GANA_POKEMON1:GANA_POKEMON2);
}

/*
* Gana el pokemon con nombre mayor alfabeticamente.
*/

int funcion_batalla_2(void* pkm_1, void* pkm_2){

	return((strcmp(((pokemon_t*)pkm_1)->nombre_pokemon, ((pokemon_t*)pkm_2)->nombre_pokemon)>=0)?GANA_POKEMON1:GANA_POKEMON2);
}

/*
* Gana el pokemon con mayor ataque o menor defensa.
*/

int funcion_batalla_3(void* pkm_1, void* pkm_2){

return((((pokemon_t*)pkm_1)->ataque>=((pokemon_t*)pkm_2)->ataque || ((pokemon_t*)pkm_1)->defensa<=((pokemon_t*)pkm_2)->defensa)?GANA_POKEMON1:GANA_POKEMON2);
}

/*
* Gana el pokemon mas fuerte.
*/

int funcion_batalla_4(void* pkm_1, void* pkm_2){

	int puntos=0;

	if(((pokemon_t*)pkm_1)->ataque>=((pokemon_t*)pkm_2)->ataque) puntos++;

	if(((pokemon_t*)pkm_1)->defensa>=((pokemon_t*)pkm_2)->defensa) puntos++;

	if(((pokemon_t*)pkm_1)->velocidad>=((pokemon_t*)pkm_2)->velocidad) puntos++;

	return((puntos>=2)?GANA_POKEMON1:GANA_POKEMON2);
}

/*
* Gana el pokemon1 si tiene la velocidad y defensa para aguantar el ataque enemigo, y si tiene la suficiente fuerza para vencerlo.
*/

int funcion_batalla_5(void* pkm_1, void* pkm_2){

	return((((pokemon_t*)pkm_1)->velocidad>=VELOCIDAD_MINIMA_POKE_RAPIDO && ((pokemon_t*)pkm_1)->defensa>=DEFENSA_MINIMA_POKE_TANQUE && ((pokemon_t*)pkm_1)->ataque>=((pokemon_t*)pkm_2)->ataque)?GANA_POKEMON1:GANA_POKEMON2);
}
