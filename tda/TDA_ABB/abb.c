#include "abb.h"
#include <stdio.h>

#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2

const int EXITO = 0;
const int ERROR = -1;



/*
*
*/

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(!comparador)
		return NULL;
	
	abb_t* arbol_nuevo = malloc(sizeof(abb_t));

	if(!arbol_nuevo)
		return NULL;

	(*arbol_nuevo).nodo_raiz = NULL;
	(*arbol_nuevo).comparador = comparador;
	(*arbol_nuevo).destructor = destructor;

	return arbol_nuevo;
}

/*
* Recorre el arbol de forma postorden, donde ,en cada nodo, invoco, si es necesario, a mi destructor y borro el nodo d3el arbol.
*/

void borrar_nodos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	if(!nodo)
		return;
	borrar_nodos((*nodo).izquierda, destructor);
	borrar_nodos((*nodo).derecha, destructor);
	if(destructor)
		destructor((*nodo).elemento);
	free(nodo);
}

/*
*
*/

void arbol_destruir(abb_t* arbol){
	if(!arbol)
		return;
	borrar_nodos((*arbol).nodo_raiz, (*arbol).destructor);
	free(arbol);
}


/*
* Inserta un nodo en el arbol y se devuelve a si mismo. Si no se pudo agregar, devuelve NULL.
*/

nodo_abb_t* insertar_nodo(nodo_abb_t* nodo_raiz, abb_comparador comparador, void* elemento, int* bandera){
	if(!nodo_raiz){
		nodo_abb_t* nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
		if(!nodo_nuevo){
			*bandera=ERROR;
			return NULL;
		} 
		nodo_raiz = nodo_nuevo;
		(*nodo_raiz).elemento = elemento;
		return nodo_raiz;
	}

	if(comparador(elemento, (*nodo_raiz).elemento)>0){
		(*nodo_raiz).derecha = insertar_nodo((*nodo_raiz).derecha, comparador, elemento, bandera);
	}

	else (*nodo_raiz).izquierda = insertar_nodo((*nodo_raiz).izquierda, comparador, elemento, bandera);

	return nodo_raiz;
}

/*
*Los elementos repetidos se insertaran a la izquierda.
*/

int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol) return ERROR;
	int bandera = EXITO;
	(*arbol).nodo_raiz = insertar_nodo((*arbol).nodo_raiz, (*arbol).comparador, elemento, &bandera);
	return EXITO;
}

/*
* Borro el nodo recibido e invoco su destructor (si es necesario)
*/

void borrar_nodo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	if(destructor)
		destructor((*nodo).elemento);
	free(nodo);
}

/*
* Busco al padre del sucesor inorden. 
* Si el nodo recibido no tiene hijo izquierdo, quiere decir que es el sucesor inorden y su padre es el nodo a borrar.
* Si el hijo izquierdo del nodo recibido es el sucesor inorden, devuelvo el nodo_actual.
*/

nodo_abb_t* nodo_padre_inferior_inmediato(nodo_abb_t* nodo_actual, nodo_abb_t* nodo_a_ordenar, abb_comparador comparador){
	if(!(*nodo_actual).derecha) return NULL;
	if((*nodo_actual).derecha == nodo_a_ordenar) return nodo_actual;

	return nodo_padre_inferior_inmediato((*nodo_actual).derecha, nodo_a_ordenar, comparador);
}

/*
* Busco el sucesor inorden al nodo que quiero eliminar.
* Devuelvo el sucesor inorden si es encontrado, o sino el sucesor inmediato derecho del nodo a eliminar.
*/

nodo_abb_t* nodo_inferior_inmediato(nodo_abb_t* nodo_actual){
	if(!(*nodo_actual).derecha) return nodo_actual;

	return nodo_inferior_inmediato((*nodo_actual).derecha);
}

/*
* Si el nodo a borrar tiene dos hijos, como convencion tomo el predecesor inorden.
*/

nodo_abb_t* borrar_y_ordenar_arbol(nodo_abb_t* nodo_raiz, abb_comparador comparador, abb_liberar_elemento destructor, void* elemento){
	if(!(*nodo_raiz).derecha && !(*nodo_raiz).izquierda){
		borrar_nodo(nodo_raiz, destructor);
		return NULL;
	}

	if((*nodo_raiz).derecha && (*nodo_raiz).izquierda){
		nodo_abb_t* nodo_a_ordenar = nodo_inferior_inmediato((*nodo_raiz).izquierda);
		nodo_abb_t* nodo_padre_a_ordenar = nodo_padre_inferior_inmediato((*nodo_raiz).izquierda, nodo_a_ordenar, comparador);
		if(nodo_padre_a_ordenar)
			(*nodo_padre_a_ordenar).derecha = (*nodo_a_ordenar).izquierda;
		(*nodo_a_ordenar).derecha = (*nodo_raiz).derecha;
		if(nodo_a_ordenar != (*nodo_raiz).izquierda)
			(*nodo_a_ordenar).izquierda = (*nodo_raiz).izquierda;
		borrar_nodo(nodo_raiz, destructor);
		return nodo_a_ordenar;
	}

	nodo_abb_t* nodo_auxiliar = (*nodo_raiz).derecha?(*nodo_raiz).derecha:(*nodo_raiz).izquierda;
	borrar_nodo(nodo_raiz, destructor);
	return nodo_auxiliar;
}

/*
* Recorro el arbol buscando al nodo a borrar.
*/

nodo_abb_t* buscar_nodo_a_eliminar(nodo_abb_t* nodo_raiz, abb_comparador comparador, abb_liberar_elemento destructor, void* elemento, int* bandera){
	if(!nodo_raiz){
		*bandera = ERROR;
		return NULL;
	}

	int comparacion = comparador(elemento, (*nodo_raiz).elemento);

	if(comparacion==0){
		return borrar_y_ordenar_arbol(nodo_raiz, comparador, destructor, elemento);
	}
	else if(comparacion<0){
		(*nodo_raiz).izquierda = buscar_nodo_a_eliminar((*nodo_raiz).izquierda, comparador, destructor, elemento, bandera);
	}
	else{
		(*nodo_raiz).derecha = buscar_nodo_a_eliminar((*nodo_raiz).derecha, comparador, destructor, elemento, bandera);
	}
	return nodo_raiz;
}

/*
*
*/

int arbol_borrar(abb_t* arbol, void* elemento){
	if(!arbol || !(*arbol).comparador) return ERROR;
	
	int bandera = EXITO;
	(*arbol).nodo_raiz = buscar_nodo_a_eliminar((*arbol).nodo_raiz, (*arbol).comparador, (*arbol).destructor, elemento, &bandera);
	return EXITO;
}

/*
* Recorro el arbol buscando el nodo recibido. 
* Devuelve 1 en caso de encontrar, o -1 en caso contrario.
*/

void* buscar_nodo(nodo_abb_t* nodo_raiz, abb_comparador comparador, void* elemento){
	if(!nodo_raiz) return NULL;

	int comparacion = comparador(elemento, (*nodo_raiz).elemento);
	if(comparacion==0){
		return (*nodo_raiz).elemento;
	}
	if(comparacion<0){
		return buscar_nodo((*nodo_raiz).izquierda, comparador, elemento);
	}
	return buscar_nodo((*nodo_raiz).derecha, comparador, elemento);
}

/*
*
*/

void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!arbol || !(*arbol).comparador)
		return NULL;
	void* nodo_a_buscar = buscar_nodo((*arbol).nodo_raiz, (*arbol).comparador, elemento);

	return nodo_a_buscar;
}

/*
*
*/

void* arbol_raiz(abb_t* arbol){
	if(!arbol) return NULL;
	if(!(*arbol).nodo_raiz) return NULL;
	return (*(*arbol).nodo_raiz).elemento;
}

/*
*
*/

bool arbol_vacio(abb_t* arbol){
	if(arbol_raiz(arbol)==NULL) return true;
	return false;
}

/*
* Recibo el array, y le asigno el valor al nodo recibido. Ademas, aumento en 1 el valor de la variable leidos.
*/

void escribir_array(nodo_abb_t* nodo_actual, void** array, size_t* leidos){
	*(array+(*leidos)) = (*nodo_actual).elemento;
	(*leidos)++;
}

/*
*
*/

void recorrer_inorden(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* leidos){
	if(!nodo_actual || (*leidos)==tamanio_array) return;

	if((*nodo_actual).izquierda) recorrer_inorden((*nodo_actual).izquierda, array, tamanio_array, leidos);

	if(nodo_actual) escribir_array(nodo_actual, array, leidos);

	if((*nodo_actual).derecha) recorrer_inorden((*nodo_actual).derecha, array, tamanio_array, leidos);	
}

/*
*
*/

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !array) return 0;

	size_t leidos = 0;
	recorrer_inorden((*arbol).nodo_raiz, array, tamanio_array, &leidos);
	return leidos;
}

/*
*
*/

void recorrer_preorden(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* leidos){
	if(!nodo_actual || (*leidos)==tamanio_array) return;

	if(nodo_actual) escribir_array(nodo_actual, array, leidos);

	if((*nodo_actual).izquierda) recorrer_preorden((*nodo_actual).izquierda, array, tamanio_array, leidos);

	if((*nodo_actual).derecha) recorrer_preorden((*nodo_actual).derecha, array, tamanio_array, leidos);	
}

/*
*
*/

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !array) return 0;

	size_t leidos = 0;
	recorrer_preorden((*arbol).nodo_raiz, array, tamanio_array, &leidos);
	return leidos;
}

/*
*
*/

void recorrer_postorden(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* leidos){
	if(!nodo_actual || (*leidos)==tamanio_array) return;
	
	if((*nodo_actual).izquierda) recorrer_postorden((*nodo_actual).izquierda, array, tamanio_array, leidos);

	if((*nodo_actual).derecha) recorrer_postorden((*nodo_actual).derecha, array, tamanio_array, leidos);	

	if(nodo_actual && (*leidos)!=tamanio_array) escribir_array(nodo_actual, array, leidos);
}

/*
*
*/

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !array) return 0;

	size_t leidos = 0;
	recorrer_postorden((*arbol).nodo_raiz, array, tamanio_array, &leidos);
	return leidos;
}

/*
* Invoco a la funcion recibida, y aumento la cantidad de elementos recorridos en el arbol por el iterador interno.
*/

void invocar_funcion_iterador_interno(nodo_abb_t* nodo_raiz, bool (*funcion)(void*, void*), void* extra, size_t* cant_elementos_recorridos, bool* puedo_iterar){
	(*puedo_iterar) = funcion((*nodo_raiz).elemento, extra);
	(*cant_elementos_recorridos)++;
}

/*
*
*/

void abb_con_cada_elemento_inorden(nodo_abb_t* nodo_raiz, bool (*funcion)(void*, void*), void* extra, size_t* cant_elementos_recorridos, bool* puedo_iterar){
	if(!nodo_raiz || (*puedo_iterar)==true)
		return;

	if((*nodo_raiz).izquierda) abb_con_cada_elemento_inorden((*nodo_raiz).izquierda, funcion, extra, cant_elementos_recorridos, puedo_iterar);

	if(nodo_raiz && (*puedo_iterar)==false) invocar_funcion_iterador_interno(nodo_raiz, funcion, extra, cant_elementos_recorridos, puedo_iterar);

	if((*nodo_raiz).derecha) abb_con_cada_elemento_inorden((*nodo_raiz).derecha, funcion, extra, cant_elementos_recorridos, puedo_iterar);
}

/*
*
*/

void abb_con_cada_elemento_preorden(nodo_abb_t* nodo_raiz, bool (*funcion)(void*, void*), void* extra, size_t* cant_elementos_recorridos, bool* puedo_iterar){
	if(!nodo_raiz || (*puedo_iterar)==true)
		return;

	if(nodo_raiz) invocar_funcion_iterador_interno(nodo_raiz, funcion, extra, cant_elementos_recorridos, puedo_iterar);

	if((*nodo_raiz).izquierda) abb_con_cada_elemento_preorden((*nodo_raiz).izquierda, funcion, extra, cant_elementos_recorridos, puedo_iterar);

	if((*nodo_raiz).derecha) abb_con_cada_elemento_preorden((*nodo_raiz).derecha, funcion, extra, cant_elementos_recorridos, puedo_iterar);
}

/*
*
*/

void abb_con_cada_elemento_postorden(nodo_abb_t* nodo_raiz, bool (*funcion)(void*, void*), void* extra, size_t* cant_elementos_recorridos, bool* puedo_iterar){
	if(!nodo_raiz || (*puedo_iterar)==true)
		return;

	if((*nodo_raiz).izquierda) abb_con_cada_elemento_postorden((*nodo_raiz).izquierda, funcion, extra, cant_elementos_recorridos, puedo_iterar);

	if((*nodo_raiz).derecha) abb_con_cada_elemento_postorden((*nodo_raiz).derecha, funcion, extra, cant_elementos_recorridos, puedo_iterar);

	if(nodo_raiz  && (*puedo_iterar)==false) invocar_funcion_iterador_interno(nodo_raiz, funcion, extra, cant_elementos_recorridos, puedo_iterar);
}

/*
*
*/

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if( !arbol || !funcion ) 
		return 0;

	size_t cant_elementos_recorridos = 0;
	bool puedo_iterar = false;

	if(recorrido==ABB_RECORRER_INORDEN){
		abb_con_cada_elemento_inorden((*arbol).nodo_raiz, funcion, extra, &cant_elementos_recorridos, &puedo_iterar);
	}
	if(recorrido == ABB_RECORRER_PREORDEN){
		abb_con_cada_elemento_preorden((*arbol).nodo_raiz, funcion, extra, &cant_elementos_recorridos, &puedo_iterar);	
	}
	if(recorrido == ABB_RECORRER_POSTORDEN){
		abb_con_cada_elemento_postorden((*arbol).nodo_raiz, funcion, extra, &cant_elementos_recorridos, &puedo_iterar);
	}

	return cant_elementos_recorridos;
}