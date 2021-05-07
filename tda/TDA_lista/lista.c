#include <stdlib.h>
#include "lista.h"

const int CANT_MINIMA_LISTA = 1;

const int ERROR = -1;
const int EXITO = 0;

const int POSICION_PRINCIPIO = 0;
const int POSICION_LUEGO_PRINCIPIO = 1;

const int CANTIDAD_NULA = 0;
const int CANT_NODOS_MINIMA = 2;
const int UN_ELEMENTO = 1;

/*
*
*/

lista_t* lista_crear(lista_liberar_elemento destructor){
	lista_t* lista_nueva = calloc((size_t)CANT_MINIMA_LISTA ,sizeof(lista_t));

	if(!lista_nueva) return NULL;

	lista_nueva->destructor = destructor;

	return lista_nueva;
}

/*
* Recibe una lista vacia y le inserta su primer elemento.
*/

void instertar_en_lista_vacia(lista_t* lista, nodo_t* nodo_nuevo, void* elemento){
	(*nodo_nuevo).siguiente = NULL;
	(*nodo_nuevo).elemento = elemento;
	(*lista).nodo_inicio = nodo_nuevo;
	(*lista).nodo_fin = nodo_nuevo;
}	

/*
*
*/

int lista_insertar(lista_t* lista, void* elemento){
	if(!lista)
		return ERROR;

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if(!nodo_nuevo)
		return ERROR;

	if((*lista).cantidad == CANTIDAD_NULA){
		instertar_en_lista_vacia(lista, nodo_nuevo, elemento);
	}else{
		(*nodo_nuevo).siguiente = NULL;
		(*nodo_nuevo).elemento = elemento;
		(*(*lista).nodo_fin).siguiente = nodo_nuevo;
		(*lista).nodo_fin = nodo_nuevo;
	}
	(*lista).cantidad++;
	return 0;
}

/*
*Recibe una lista valida.
*Inserta un elemento al principio de la lista.
*Devuelve 0 si pudo insertarto y -1 en caso de error.
*/

int lista_insertar_principio(lista_t* lista, void* elemento){
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if(!nodo_nuevo)
		return ERROR;

	if((*lista).cantidad == CANTIDAD_NULA){
		instertar_en_lista_vacia(lista, nodo_nuevo, elemento);
	}else{
		(*nodo_nuevo).siguiente = (*lista).nodo_inicio;
		(*nodo_nuevo).elemento = elemento;
		(*lista).nodo_inicio = nodo_nuevo;
	}

	(*lista).cantidad++;
	return EXITO;
}

/*
*Recibe una lista valida.
*Inserta un elemento en la posicion indicada de la lista.
*Devuelve 0 si pudo insertarto y -1 en caso de error.
*/

int lista_insertar_posicion(lista_t* lista, void* elemento, size_t posicion){
	nodo_t* nodo_aux = malloc(sizeof(nodo_t));
	if(!nodo_aux)
		return ERROR;
	(*nodo_aux).elemento = elemento;
	nodo_t* nodo_a_buscar = (*lista).nodo_inicio;
	int contador = 0;
	while(contador < posicion-1){
		nodo_a_buscar = (*nodo_a_buscar).siguiente;
		contador++;
	}	
	(*nodo_aux).siguiente = (*nodo_a_buscar).siguiente;
	(*nodo_a_buscar).siguiente = nodo_aux;
	(*lista).cantidad++;
	return EXITO;
}

/*
*
*/

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista)
		return ERROR;

	if(posicion == POSICION_PRINCIPIO){
		return lista_insertar_principio(lista, elemento);
	}else if(posicion < POSICION_PRINCIPIO || posicion >= (*lista).cantidad){	
		return lista_insertar(lista, elemento);
	}else{	
		return lista_insertar_posicion(lista, elemento, posicion);
	}	
}	

/*
*Devuelve un puntero al nodo anterior de nodo_a_buscar.
*/

nodo_t* buscar_nodo(nodo_t* nodo_actual, nodo_t* nodo_a_buscar){
	if((*nodo_actual).siguiente != nodo_a_buscar){
		return buscar_nodo((*nodo_actual).siguiente, nodo_a_buscar);
	}	
	return nodo_actual;
}	

/*
*
*/

void borrar_unico_elemento_en_lista(lista_t* lista){
	/*
	(*(*lista).nodo_fin).siguiente = NULL;
	*/
	(*lista).nodo_fin = NULL;
	free((*lista).nodo_inicio);
	(*lista).nodo_inicio = NULL;
	(*lista).cantidad--;
}	

/*
*
*/

int lista_borrar(lista_t* lista){
	if(!lista || (*lista).cantidad==CANTIDAD_NULA)
		return ERROR;
	if((*lista).cantidad==UN_ELEMENTO){
		borrar_unico_elemento_en_lista(lista);
		return EXITO;
	}	
	nodo_t* nodo_a_designar = buscar_nodo((*lista).nodo_inicio, (*lista).nodo_fin);
	free((*lista).nodo_fin);
	(*lista).nodo_fin = nodo_a_designar;
	(*(*lista).nodo_fin).siguiente = NULL;
	(*lista).cantidad--;
	return EXITO;
}

/*
* Recibe un puntero a una lista con sus estrucaturas validas.
* Elimino el primer nodo de la lista.
*/

void lista_borrar_principio(lista_t* lista){
	if((*lista).cantidad==UN_ELEMENTO){
		borrar_unico_elemento_en_lista(lista);
		return ;
	}
	nodo_t* nodo_aux = (*(*lista).nodo_inicio).siguiente;
	free((*lista).nodo_inicio);
	(*lista).nodo_inicio= nodo_aux;
	(*lista).cantidad--;
}	

/*
*
*/

void borrar_en_posicion(lista_t* lista, size_t posicion){
	nodo_t* nodo_aux = (*lista).nodo_inicio;
	int contador=0;
	while(contador<posicion-1){
		nodo_aux = (*nodo_aux).siguiente;
		contador++;
	}
	nodo_t* nodo_a_borrar = (*nodo_aux).siguiente;
	(*nodo_aux).siguiente = (*nodo_a_borrar).siguiente;
	free(nodo_a_borrar);
	(*lista).cantidad--;
	if((*lista).cantidad==UN_ELEMENTO)
		(*lista).nodo_fin = (*lista).nodo_inicio;
}	

/*
*
*/

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(!lista || (*lista).cantidad==CANTIDAD_NULA)
		return ERROR;
	if(posicion<CANTIDAD_NULA || posicion>=(*lista).cantidad){
		lista_borrar(lista);
	}else if(posicion==POSICION_PRINCIPIO){
		lista_borrar_principio(lista);
	}else{	
		borrar_en_posicion(lista, posicion);
	}
	return EXITO;	
}

/*
*
*/

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!lista || posicion>=(*lista).cantidad || posicion<CANTIDAD_NULA)
		return NULL;
	nodo_t* nodo_a_buscar = (*lista).nodo_inicio;
	int contador=0;
	while(contador<posicion){
		nodo_a_buscar = (*nodo_a_buscar).siguiente;
		contador++;
	}	
	return (*nodo_a_buscar).elemento;
}	

/*
*
*/

void* lista_ultimo(lista_t* lista){
	if(!lista || (*lista).cantidad==CANTIDAD_NULA)
		return NULL;
	return (*(*lista).nodo_fin).elemento;
}	

/*
*
*/

bool lista_vacia(lista_t* lista){
	if(!lista || (*lista).cantidad==CANTIDAD_NULA)
		return true;
	return false;
}	

/*
*
*/

size_t lista_elementos(lista_t* lista){
	if(!lista)
		return 0;
	return (*lista).cantidad;
}	

/*
*
*/

int lista_apilar(lista_t* lista, void* elemento){
	if(!lista)
		return ERROR;
	return lista_insertar_principio(lista, elemento);
}	

/*
*
*/

int lista_desapilar(lista_t* lista){
	if(!lista)
		return ERROR;
	lista_borrar_principio(lista);
	return EXITO;
}	

/*
*
*/

void* lista_tope(lista_t* lista){
	if(!lista || (*lista).cantidad==CANTIDAD_NULA)
		return NULL;
	return (*(*lista).nodo_inicio).elemento;
}

/*
*
*/

int lista_encolar(lista_t* lista, void* elemento){
	if(!lista)
		return ERROR;
	return lista_insertar(lista, elemento);
}	

/*
*
*/

int lista_desencolar(lista_t* lista){
	if(!lista)
		return ERROR;
	lista_borrar_principio(lista);
	return EXITO;
}	

/*
*
*/

void* lista_primero(lista_t* lista){
	if(!lista || (*lista).cantidad==CANTIDAD_NULA)
		return NULL;
	return (*(*lista).nodo_inicio).elemento;
}

/*
*
*/

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista)
		return NULL;
	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;
	(*iterador).lista = lista;
	(*iterador).corriente = (*lista).nodo_inicio;
	return iterador;
}	

/*
*
*/

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador)
		return NULL;
	if((*iterador).corriente==NULL)
		return NULL;
	return (*(*iterador).corriente).elemento;
}	

/*
*
*/

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador || (*(*iterador).lista).cantidad == CANTIDAD_NULA || (*iterador).corriente==NULL)
		return false;
	return true;
}	

/*
*
*/

bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!iterador)
		return false;
	if(lista_iterador_tiene_siguiente(iterador)==true){
		(*iterador).corriente = (*(*iterador).corriente).siguiente;
		if((*iterador).corriente!=NULL){
			return true;
		}
	}	
	return false;
}	

/*
*
*/

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	if( lista_vacia(lista)==true || !funcion)
		return 0;
	nodo_t* nodo_actual = (*lista).nodo_inicio;
	size_t cantidad_elementos = 0;
	while(nodo_actual!=NULL && funcion((*nodo_actual).elemento, contexto)==true){
		cantidad_elementos++;
		nodo_actual = (*nodo_actual).siguiente;
	}	
	return cantidad_elementos;
}	

/*
*
*/

void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}	

/*
*
*/

void liberar_nodos(nodo_t* nodo, lista_liberar_elemento destructor){
	if((*nodo).siguiente)
		liberar_nodos((*nodo).siguiente);

	if(destructor)
		destructor(nodo->elemento);

	free(nodo);
}	

/*
*
*/

void lista_destruir(lista_t* lista){
	if(!lista)
		return;
	if((*lista).nodo_inicio){
		liberar_nodos((*lista).nodo_inicio, lista->destructor);
	}	
	free(lista);
}	