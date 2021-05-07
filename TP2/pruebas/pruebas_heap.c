#include <stdlib.h>
#include "heap.h"
#include "pa2mm.h"

static const int MAYOR = 1;
static const int MENOR = -1;
static const int IGUAL = 0;

static const int EXITO = 0;
static const int ERROR = -1;


int comparador(void* num1, void* num2){
	if(!num1 || !num2) return IGUAL;

	int numero1 = *(int*)num1;
	int numero2 = *(int*)num2;

	if(numero1>numero2){
		return MAYOR;
	}
	else if(numero1<numero2){
		return MENOR;
	}
	else{
		return IGUAL;
	}
}

void destructor(void* elemento){
	free(elemento);
}

int* crear_elemento(int clave){
	int* elemento = malloc(sizeof(int));
	if(elemento)
		*elemento = clave;
	return elemento;
}

void probar_creacion_heap(){

	heap_t* heap = heap_crear(comparador, destructor);

	pa2m_afirmar(heap, "Se pudo crear un heap");
	pa2m_afirmar(heap->comparador && heap->destructor, "El heap creado tiene un comparador y un destructor");
	pa2m_afirmar(heap->cant_elementos==0, "La cantidad de elementos del heap es nula");

	heap_t* heap2 = heap_crear(NULL, destructor);
	heap_t* heap3 = heap_crear(comparador, NULL);

	pa2m_afirmar(!heap2, "No se puede crear un heap sin comparador");
	pa2m_afirmar(heap3, "Se puede crear un heap sin destructor");

	heap_destruir(heap);
	heap_destruir(heap3);
}

void probar_insercion_heap(){
	heap_t* heap = heap_crear(comparador, destructor);

	int* elemento1 = crear_elemento(3);

	pa2m_afirmar(heap_insertar(heap, (void*)elemento1)==EXITO, "Se pudo insertar un elemento");
	pa2m_afirmar(*(int*)heap->vector[0]== *elemento1, "El elemento insertado es el esperado");
	pa2m_afirmar(heap->cant_elementos==1, "La cantidad de elementos es la esperada");

	int* elemento2 = crear_elemento(5);
	int* elemento3 = crear_elemento(4);
	pa2m_afirmar(heap_insertar(heap, (void*)elemento2)==EXITO, "Se pudo insertar un elemento");
	pa2m_afirmar(heap_insertar(heap, (void*)elemento3)==EXITO, "Se pudo insertar un elemento");
	pa2m_afirmar(*(int*)heap->vector[1]== *elemento2, "El elemento insertado es el esperado");
	pa2m_afirmar(*(int*)heap->vector[2]== *elemento3, "El elemento insertado es el esperado");

	int* elemento4 = crear_elemento(2);
	pa2m_afirmar(heap_insertar(heap, (void*)elemento4)==EXITO, "Se pudo insertar un elemento");
	pa2m_afirmar(*(int*)heap->vector[0]== *elemento4, "El elemento insertado es la raiz");

	pa2m_afirmar(heap_insertar(NULL, NULL)==ERROR, "No se puede insertar en un heap no existente");

	heap_destruir(heap);
}

void probar_extraccion_raiz(){
	heap_t* heap = heap_crear(comparador, destructor);

	int* elemento1 = crear_elemento(3);
	int* elemento2 = crear_elemento(5);
	int* elemento3 = crear_elemento(4);
	int* elemento4 = crear_elemento(2);

	heap_insertar(heap, elemento1);
	heap_insertar(heap, elemento2);
	heap_insertar(heap, elemento3);
	heap_insertar(heap, elemento4);

	pa2m_afirmar(extraer_raiz(heap)==EXITO, "Se pudo extraer la raiz del heap");
	pa2m_afirmar(*(int*)heap_raiz(heap)== *elemento1, "La nueva raiz es la esperada");
	pa2m_afirmar(heap->cant_elementos==3, "La cantidad de elementos es la esperada");

	pa2m_afirmar(extraer_raiz(heap)==EXITO, "Se pudo extraer la raiz del heap");
	pa2m_afirmar(*(int*)heap_raiz(heap)== *elemento3, "La nueva raiz es la esperada");
	pa2m_afirmar(heap->cant_elementos==2, "La cantidad de elementos es la esperada");
	pa2m_afirmar(extraer_raiz(heap)==EXITO, "Se pudo extraer la raiz del heap");
	pa2m_afirmar(*(int*)heap_raiz(heap)== *elemento2, "La nueva raiz es la esperada");
	pa2m_afirmar(heap->cant_elementos==1, "La cantidad de elementos es la esperada");

	pa2m_afirmar(extraer_raiz(heap)==EXITO, "Se pudo extraer el unico elemento del heap");
	pa2m_afirmar(heap_raiz(heap)== NULL, "Un heap sin elementos no tiene raiz");
	pa2m_afirmar(heap->cant_elementos==0, "La cantidad de elementos es nula");

	pa2m_afirmar(extraer_raiz(NULL)==ERROR, "No se puede extraer la raiz de un heap no valido");

	heap_destruir(heap);

}

int main(){

	pa2m_nuevo_grupo("Pruebas creacion heap");
	probar_creacion_heap();

	pa2m_nuevo_grupo("Pruebas insercion heap");
	probar_insercion_heap();

	pa2m_nuevo_grupo("Pruebas extraccion raiz");
	probar_extraccion_raiz();

	return 0;
}