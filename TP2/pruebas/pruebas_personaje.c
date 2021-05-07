#include "pa2mm.h"
#include "gimnasio.h"
#include "personaje_principal.h"
#include "lista.h"
#include "abb.h"
#include <string.h>

void probar_creacion_personaje(){
	personaje_t* personaje = crear_personaje("Ash_personaje");

	pa2m_afirmar(personaje, "Se pudo crear un personaje");

	pa2m_afirmar(strcmp(personaje->nombre, "Ash")==0, "El personaje es el esperado");

	pa2m_afirmar(personaje->pokemon_para_combatir->cantidad==6, "La cantidad de pokemones para combatir es la esperada");

	pa2m_afirmar(strcmp(((pokemon_t*)(personaje->pokemon_en_caja->nodo_raiz->elemento))->nombre_pokemon, "Krabby")==0, "El pokemon en la caja es el esperado");

	mostrar_personaje(personaje);

	personaje_destruir(personaje);
}

void probar_personaje_invalido(){
	personaje_t* personaje = crear_personaje("personaje_sin_pokemon");

	pa2m_afirmar(!personaje, "No se puede crear un personaje sin pokemon");

	personaje_destruir(personaje);

	personaje_t* personaje_sin_personaje = crear_personaje("personaje_sin_personaje");

	pa2m_afirmar(!personaje_sin_personaje, "No se puede crear un personaje sin un personaje");

	personaje_destruir(personaje_sin_personaje);

	personaje_t* personaje_vacio = crear_personaje("personaje_vacio");

	pa2m_afirmar(!personaje_vacio, "No se puede crear un personaje con un archivo vacio");

	personaje_destruir(personaje_vacio);
}

void probar_intercambio(){

	personaje_t* personaje = crear_personaje("Ash_personaje");

	pa2m_afirmar(intercambio_pokemon(personaje, 1, ((pokemon_t*)(personaje->pokemon_en_caja->nodo_raiz->elemento)))==1, "Se pudo realizar un intercambio");

	pa2m_afirmar(strcmp(((pokemon_t*)(personaje->pokemon_para_combatir->nodo_fin->elemento))->nombre_pokemon, "Krabby")==0, "Los pokemones son los esperados");

	personaje_destruir(personaje);
}

int main(){

	pa2m_nuevo_grupo("Pruebas creacion personaje");
	probar_creacion_personaje();

	pa2m_nuevo_grupo("Pruebas personaje invalido");
	probar_personaje_invalido();

	pa2m_nuevo_grupo("Pruebas intercambio pokemon");
	probar_intercambio();

	return 0;
}