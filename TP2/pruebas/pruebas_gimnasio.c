#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "gimnasio.h"
#include "heap.h"
#include "pa2mm.h"

void probar_creacion_gimnasio_normal(){

	heap_t* heap_gimnasio = crear_heap_gimnasio(NULL, "gym_normal");
	
	pa2m_afirmar(heap_gimnasio->vector[0]!=NULL, "Se pudo crear un gimnasio");

	pa2m_afirmar(((gimnasio_t*)(heap_gimnasio->vector[0]))->entrenadores->cantidad==3, "La cantidad de entrenadores es la esperada");

	pa2m_afirmar(strcmp(((entrenador_t*)(((gimnasio_t*)(heap_gimnasio->vector[0]))->entrenadores->nodo_inicio->elemento))->nombre_entrenador, "Nadador Luis")==0, "El entrenador es el esperado");
	pa2m_afirmar(strcmp(((entrenador_t*)(((gimnasio_t*)(heap_gimnasio->vector[0]))->entrenadores->nodo_fin->elemento))->nombre_entrenador, "Misty")==0, "El lider es el esperado");

	pa2m_afirmar(((entrenador_t*)(((gimnasio_t*)(heap_gimnasio->vector[0]))->entrenadores->nodo_fin->elemento))->pokemones->cantidad==2, "La cantidad de pokemones del lider es lo esperado");

	mostrar_gimnasio(heap_gimnasio->vector[0]);

	heap_destruir(heap_gimnasio);

	heap_t* gimnasio_pokemon_de_mas = crear_heap_gimnasio(NULL, "gym_pokemon_de_mas");

	pa2m_afirmar(gimnasio_pokemon_de_mas->vector[0]!=NULL, "Se puede crar un gimnasio con pokemones de mas");

	pa2m_afirmar(((entrenador_t*)(((gimnasio_t*)(gimnasio_pokemon_de_mas->vector[0]))->entrenadores->nodo_fin->elemento))->pokemones->cantidad==6, "La cantidad de pokemones del lider no supera los 6");

	heap_destruir(gimnasio_pokemon_de_mas);
}

void probar_creacion_varios_gims(){

	heap_t* heap_gimnasio = crear_heap_gimnasio(NULL, "varios_gyms");

	pa2m_afirmar(heap_gimnasio->vector[0]!=NULL && heap_gimnasio->vector[1]!=NULL && heap_gimnasio->vector[2]!=NULL, "Se pudo crear los gimnasios");

	pa2m_afirmar(strcmp(((gimnasio_t*)(heap_gimnasio->vector[0]))->nombre_gimnasio, "Gimnasio de Ciudad Algo 2")==0, "El primer gimnasio es el esperado");
	pa2m_afirmar(strcmp(((gimnasio_t*)(heap_gimnasio->vector[1]))->nombre_gimnasio, "Gimnasio de Ciudad Celeste")==0, "El segundo gimnasio es el esperado");
	pa2m_afirmar(strcmp(((gimnasio_t*)(heap_gimnasio->vector[2]))->nombre_gimnasio, "Gimnasio de Ciudad Nueva")==0, "El tercer gimnasio es el esperado");

	pa2m_afirmar(heap_gimnasio->cant_elementos == 3, "La cantidad de gimnasios es la esperada");

	heap_destruir(heap_gimnasio);
}

void probar_gimnasios_invalidos(){
	heap_t* heap_gimnasio_vacio = crear_heap_gimnasio(NULL, "gym_vacio");

	pa2m_afirmar(heap_gimnasio_vacio==NULL, "No se puede crear un gimnasio con un archivo vacio");

	heap_destruir(heap_gimnasio_vacio);

	heap_t* heap_gimnasio_entrenadores_sin_poke = crear_heap_gimnasio(NULL, "gym_entrenador_sin_pokemon");

	pa2m_afirmar(heap_gimnasio_entrenadores_sin_poke==NULL, "No se puede crear un gimnasio con entrenadores sin pokemon");

	heap_destruir(heap_gimnasio_entrenadores_sin_poke);

	heap_t* entrenadores_sin_gimnasio = crear_heap_gimnasio(NULL, "entrenadores_sin_gym");

	pa2m_afirmar(entrenadores_sin_gimnasio==NULL, "No se puede crear un gimnasio sin gimnasio");

	heap_destruir(entrenadores_sin_gimnasio);

	heap_t* gimnasio_lider_sin_pokemon = crear_heap_gimnasio(NULL, "gym_lider_sin_pokemon");

	pa2m_afirmar(gimnasio_lider_sin_pokemon==NULL, "No se puede crear un gimnasio sin gimnasio");

	heap_destruir(gimnasio_lider_sin_pokemon);

	heap_t* gimnasio_id_funcion_grande = crear_heap_gimnasio(NULL, "gym_id_func_grande");

	pa2m_afirmar(gimnasio_id_funcion_grande==NULL, "No se puede crear un gimnasio con un ide_funcion mayor a los validos");

	heap_destruir(gimnasio_id_funcion_grande);

	heap_t* gimnasio_id_funcion_negativo = crear_heap_gimnasio(NULL, "gym_id_func_negativo");

	pa2m_afirmar(gimnasio_id_funcion_negativo==NULL, "No se puede crear un gimnasio con un ide_funcion menor a los validos");

	heap_destruir(gimnasio_id_funcion_negativo);

	heap_t* gimnasio_sin_lider = crear_heap_gimnasio(NULL, "gym_sin_lider");

	pa2m_afirmar(gimnasio_sin_lider==NULL, "No se puede crear un gimnasio sin lider");

	heap_destruir(gimnasio_sin_lider);

	heap_t* gimnasio_mal_formato = crear_heap_gimnasio(NULL, "gym_mal_formato");

	pa2m_afirmar(gimnasio_mal_formato==NULL, "No se puede crear un gimnasio con mal formato");

	heap_destruir(gimnasio_mal_formato);
}

void probar_quitar_entrenador(){

	heap_t* gimnasio = crear_heap_gimnasio(NULL, "varios_gyms");

	pa2m_afirmar(quitar_entrenador(gimnasio->vector[2])==0, "Se pudo quitar el entrenador");
	pa2m_afirmar(quitar_entrenador(gimnasio->vector[2])==0, "Se pudo quitar el entrenador");
	pa2m_afirmar(quitar_entrenador(gimnasio->vector[2])==0, "Se pudo quitar el lider");
	pa2m_afirmar(quitar_entrenador(gimnasio->vector[2])==-1, "No hay mas entrenadores para quitar");

	heap_destruir(gimnasio);
}

void probar_quitar_gim(){

	heap_t* gimnasio = crear_heap_gimnasio(NULL, "varios_gyms");

	pa2m_afirmar(quitar_gimnasio(gimnasio)==0, "Se pudo quitar el gimnasio");
	pa2m_afirmar(quitar_gimnasio(gimnasio)==0, "Se pudo quitar el gimnasio");
	pa2m_afirmar(quitar_gimnasio(gimnasio)==0, "Se pudo quitar el gimnasio");
	pa2m_afirmar(quitar_gimnasio(gimnasio)==-1, "No hay mas gimnasios para quitar");

	heap_destruir(gimnasio);
}

int main(){

	pa2m_nuevo_grupo("Pruebas creacion gimnasio normal");
	probar_creacion_gimnasio_normal();

	pa2m_nuevo_grupo("Pruebas creacion varios gimnasios normales");
	probar_creacion_varios_gims();

	pa2m_nuevo_grupo("Pruebas con gimnasios invalidos");
	probar_gimnasios_invalidos();

	pa2m_nuevo_grupo("Pruebas quitar entrenador");
	probar_quitar_entrenador();

	pa2m_nuevo_grupo("Probar quitar gimnasio");
	probar_quitar_gim();

	return 0;
}
