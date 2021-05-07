#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

static const int ERROR = -1;
static const int EXITO = 0;
static const int POSICION_RAIZ = 0;

/*
*
*/

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){

	if(!comparador) return NULL;

	heap_t* nuevo_heap = calloc(1, sizeof(heap_t));
	if(!nuevo_heap) return NULL;

	nuevo_heap->comparador = comparador;
	nuevo_heap->destructor = destructor;

	return nuevo_heap;
}

/*
* Recibe la posicion del elemento del heap.
* Devuelve la posicion de su padre.
*/

int posicion_padre(int posicion_vector){
	return((posicion_vector-1)/2);
}

/*
*Cambia las posiciones de los elementos deseados en el heap.
*/

void swap(void** vector, int i, int j){
	void* aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

/*
* Compara el elemento que quiero ordenar con su padre invocando al comparador.
* Si el elemento es menor a su padre, invoco a la funcion swap.
* Si la posicion de mmi elemento es la posicion de mi raiz, no hago nada.
* Ya que es el unico elemento del heap.
*/

void sift_up(heap_t* heap, int posicion_vector){
	if(posicion_vector == POSICION_RAIZ) return;

	int padre = posicion_padre(posicion_vector);

	if(heap->comparador(heap->vector[posicion_vector], heap->vector[padre]) == -1){
		swap(heap->vector, posicion_vector, padre);
		sift_up(heap, padre);
	}
}

/*
*
*/

int heap_insertar(heap_t* heap, void* elemento){

	if(!heap) return ERROR;

	void** vector_aux = realloc(heap->vector, sizeof(elemento)*(size_t)(heap->cant_elementos+1));
	if(!vector_aux) return ERROR;

	heap->cant_elementos++;
	heap->vector = vector_aux;

	heap->vector[heap->cant_elementos - 1] = elemento;

	sift_up(heap, heap->cant_elementos-1);

	return EXITO; 
}

/*
* Compara el elemento que quiero ordenar con su padre invocando al comparador.
* Si hay un unico elemento, la funcion no hace nada.
* Si mi elemento tiene derecho e izquierdo, invoco al comparador para ver cual es el menor.
* Y llamo a la funcion swap.
*/

void sift_down(heap_t* heap, int posicion_vector){
	int pos_der = (2*posicion_vector)+2;
	int pos_izq = (2*posicion_vector)+1;
	int posicion_menor = pos_izq;

	if(pos_izq>=heap->cant_elementos) return;

	if(pos_der<heap->cant_elementos) posicion_menor = (pos_der>pos_izq)?pos_izq:pos_der;

	if(heap->comparador(heap->vector[posicion_vector], heap->vector[posicion_menor])==1){
		swap(heap->vector, posicion_vector, posicion_menor);
		sift_down(heap, posicion_menor);
	}
}

/*
*
*/

int extraer_raiz(heap_t* heap){
	if(!heap || heap->cant_elementos == 0) return ERROR;

	void* aux = heap->vector[POSICION_RAIZ];

	heap->vector[POSICION_RAIZ] = heap->vector[heap->cant_elementos-1];
	heap->cant_elementos--; 

	if(heap->cant_elementos != 0){
		sift_down(heap, POSICION_RAIZ);

		void** vector_aux = realloc(heap->vector, sizeof(heap->vector[POSICION_RAIZ])*(size_t)heap->cant_elementos);
		if(!vector_aux) return ERROR;

		heap->vector = vector_aux;
	}

	heap->destructor(aux);

	return EXITO;
}

/*
*
*/

void* heap_raiz(heap_t* heap){

	if(!heap || heap->cant_elementos==0) return NULL;

	return heap->vector[POSICION_RAIZ];
}

/*
*
*/

void heap_destruir(heap_t* heap){
	if(heap){
		if(heap->destructor && heap->cant_elementos > 0){
			for(int i = 0; i<heap->cant_elementos; i++)
				heap->destructor(heap->vector[i]);
		}
		free(heap->vector);
	}
	free(heap);
}