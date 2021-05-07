#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>

/*
 * Comparador de elementos. Recibe dos elementos del heap binario y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
*/

typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);


typedef struct heap{
	void** vector;
	heap_comparador comparador;
	heap_liberar_elemento destructor;
	int cant_elementos;
}heap_t;

/*
 * Crea el heap y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del heap,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al heap creado o NULL en caso de error.
*/

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
 * Inserta un elemento en el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El heap admite elementos con valores repetidos.
*/

int heap_insertar(heap_t* heap, void* elemento);

/*
 *Borra del heap a la raiz.
 *Devuelve la nueva raiz en caso de que lo haya. Sino devuelve NULL.
*/

int extraer_raiz(heap_t* heap);

/*
 *Devuelve la raiz del heap.
 * En caso de que no exista, devuelve NULL.
*/

void* heap_raiz(heap_t* heap);

/*
 * Destruye el heap liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el heap.
*/

void heap_destruir(heap_t* heap);

#endif /*__HEAP_H__*/