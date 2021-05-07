#include "abb.h"
#include <stdio.h>
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

bool mostrar_elemento(void* elemento, void* extra){
    extra=extra; 
    if(elemento)
        printf("%i ", *(int*)elemento);
    return false;
}

void probar_creacion_arbol(){
	abb_t* arbol = arbol_crear(comparador, destructor);
	abb_t* arbol_1 = arbol_crear(comparador, NULL);
	abb_t* arbol_2 = arbol_crear(NULL, destructor);

	pa2m_afirmar((*arbol).nodo_raiz==NULL, "Se crea un arbol. El nodo raiz apunta a NULL");
	pa2m_afirmar(arbol_vacio(arbol)==true, "El arbol esta vacio");
	pa2m_afirmar(arbol_vacio(NULL)==true, "Un arbol que no existe esta vacio");

	pa2m_afirmar(arbol_1!=NULL, "Se puede crear un arbol sin destructor");
	pa2m_afirmar(arbol_2==NULL, "No se puede crear un arbol sin comparador");

	arbol_destruir(arbol);	
	arbol_destruir(arbol_1);
	arbol_destruir(arbol_2);
}

void probar_insercion_arbol(){
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(2);
	int* elemento_3 = crear_elemento(5);

	pa2m_afirmar(arbol_insertar(arbol, elemento_1)==EXITO && (int*)arbol_raiz(arbol)==elemento_1 , "El nodo raiz apunta al elemento agregado");
	pa2m_afirmar(*(int*)arbol_raiz(arbol)==*elemento_1 , "El valor del nodo raiz es el esperado");
	pa2m_afirmar(arbol_vacio(arbol)==false, "El arbol no esta vacio");

	pa2m_afirmar(arbol_insertar(arbol, elemento_2)==EXITO, "Puedo insertar un elemento menor que el primero");
	pa2m_afirmar((*(*arbol).nodo_raiz).izquierda && !(*(*arbol).nodo_raiz).derecha, "El nodo raiz queda con un hijo izquierdo y sin hijo derecho");

	pa2m_afirmar(arbol_insertar(arbol, elemento_3)==EXITO, "Puedo insertar un elemento mayor que el primero");
	pa2m_afirmar((*(*arbol).nodo_raiz).izquierda && (*(*arbol).nodo_raiz).derecha, "El nodo raiz queda con un hijo izquierdo y con hijo derecho");


	pa2m_afirmar(arbol_insertar(arbol, NULL)==EXITO, "Se puede insertar un elemento NULL");
	pa2m_afirmar(arbol_insertar(NULL, elemento_1)==ERROR, "No se puede insertar en un arbol inexistente");

	arbol_destruir(arbol);
}

void probar_borrar_arbol(){
	
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(2);
	int* elemento_4 = crear_elemento(6);
	int* elemento_5 = crear_elemento(5);
	int* elemento_6 = crear_elemento(1);
	int* elemento_7 = crear_elemento(10);
	int* elemento_8 = crear_elemento(8);

	arbol_insertar(arbol, elemento_1);
	arbol_insertar(arbol, elemento_2);
	arbol_insertar(arbol, elemento_3);
	arbol_insertar(arbol, elemento_8);
	arbol_insertar(arbol, elemento_5);
	arbol_insertar(arbol, elemento_4);
	arbol_insertar(arbol, elemento_6);
	arbol_insertar(arbol, elemento_7);

	pa2m_afirmar(arbol_borrar(arbol, elemento_1)==EXITO, "Se elimino el nodo raiz");
	pa2m_afirmar(arbol_borrar(arbol, elemento_4)==EXITO, "Se elimino un nodo con dos hijos");
	pa2m_afirmar(arbol_borrar(arbol, elemento_6)==EXITO, "Se elimino un nodo hoja");
	pa2m_afirmar(arbol_borrar(arbol, elemento_7)==EXITO, "Se elimino un nodo con un hijo");

	arbol_borrar(arbol, elemento_2);
	arbol_borrar(arbol, elemento_3);
	arbol_borrar(arbol, elemento_5);

	arbol_destruir(arbol);
}

void probar_busqueda_arbol(){
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(2);
	int* elemento_4 = crear_elemento(6);
	int* elemento_5 = crear_elemento(5);
	int* elemento_6 = crear_elemento(1);
	int* elemento_7 = crear_elemento(10);
	int* elemento_8 = crear_elemento(11);

	arbol_insertar(arbol, elemento_1);
	arbol_insertar(arbol, elemento_2);
	arbol_insertar(arbol, elemento_3);
	arbol_insertar(arbol, elemento_4);
	arbol_insertar(arbol, elemento_5);
	arbol_insertar(arbol, elemento_6);
	arbol_insertar(arbol, elemento_7);

	pa2m_afirmar(arbol_buscar(arbol, elemento_1)==elemento_1, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_2)==elemento_2, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_3)==elemento_3, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_4)==elemento_4, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_5)==elemento_5, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_6)==elemento_6, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_7)==elemento_7, "Busco un elemento existente y lo encuentro");
	pa2m_afirmar(arbol_buscar(arbol, elemento_8)==NULL, "Busco un elemento inexistente y no lo encuentro");

	free(elemento_8);
	arbol_destruir(arbol);
}

void probar_recorrido_inorden(){
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(2);
	int* elemento_4 = crear_elemento(6);
	int* elemento_5 = crear_elemento(5);
	int* elemento_6 = crear_elemento(1);
	int* elemento_7 = crear_elemento(10);

	arbol_insertar(arbol, elemento_1);
	arbol_insertar(arbol, elemento_2);
	arbol_insertar(arbol, elemento_3);
	arbol_insertar(arbol, elemento_4);
	arbol_insertar(arbol, elemento_5);
	arbol_insertar(arbol, elemento_6);
	arbol_insertar(arbol, elemento_7);

	int* array_1[10];

    size_t cantidad = arbol_recorrido_inorden(arbol, (void**)array_1, 7);

    pa2m_afirmar(cantidad==7, "La cantidad de elementos leidos es la esperada");
    pa2m_afirmar(arbol_recorrido_inorden(arbol, (void**)array_1, 4)==4, "La cantidad de elementos leidos es menor a la de los que hay en el arbol");
    pa2m_afirmar(arbol_recorrido_inorden(arbol, (void**)array_1, 10)==7, "Pido recorrer mas elementos de los existentes");

	arbol_destruir(arbol);
}

void probar_recorrido_preorden(){
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(2);
	int* elemento_4 = crear_elemento(6);
	int* elemento_5 = crear_elemento(5);
	int* elemento_6 = crear_elemento(1);
	int* elemento_7 = crear_elemento(10);

	arbol_insertar(arbol, elemento_1);
	arbol_insertar(arbol, elemento_2);
	arbol_insertar(arbol, elemento_3);
	arbol_insertar(arbol, elemento_4);
	arbol_insertar(arbol, elemento_5);
	arbol_insertar(arbol, elemento_6);
	arbol_insertar(arbol, elemento_7);

	int* array_1[10];

    size_t cantidad = arbol_recorrido_preorden(arbol, (void**)array_1, 7);

    pa2m_afirmar(cantidad==7, "La cantidad de elementos leidos es la esperada");
    pa2m_afirmar(arbol_recorrido_preorden(arbol, (void**)array_1, 4)==4, "La cantidad de elementos leidos es menor a la de los que hay en el arbol");
    pa2m_afirmar(arbol_recorrido_preorden(arbol, (void**)array_1, 10)==7, "Pido recorrer mas elementos de los existentes");

	arbol_destruir(arbol);
}

void probar_recorrido_postorden(){
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(2);
	int* elemento_4 = crear_elemento(6);
	int* elemento_5 = crear_elemento(5);
	int* elemento_6 = crear_elemento(1);
	int* elemento_7 = crear_elemento(10);

	arbol_insertar(arbol, elemento_1);
	arbol_insertar(arbol, elemento_2);
	arbol_insertar(arbol, elemento_3);
	arbol_insertar(arbol, elemento_4);
	arbol_insertar(arbol, elemento_5);
	arbol_insertar(arbol, elemento_6);
	arbol_insertar(arbol, elemento_7);

	int* array_1[10];

    size_t cantidad = arbol_recorrido_postorden(arbol, (void**)array_1, 7);

    pa2m_afirmar(cantidad==7, "La cantidad de elementos leidos es la esperada");
    pa2m_afirmar(arbol_recorrido_postorden(arbol, (void**)array_1, 4)==4, "La cantidad de elementos leidos es menor a la de los que hay en el arbol");
    pa2m_afirmar(arbol_recorrido_postorden(arbol, (void**)array_1, 10)==7, "Pido recorrer mas elementos de los existentes");

	arbol_destruir(arbol);
}

void probar_iterador_interno(){
	abb_t* arbol = arbol_crear(comparador, destructor);

	int* elemento_1 = crear_elemento(4);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(2);
	int* elemento_4 = crear_elemento(6);
	int* elemento_5 = crear_elemento(5);
	int* elemento_6 = crear_elemento(1);
	int* elemento_7 = crear_elemento(10);

	arbol_insertar(arbol, elemento_1);
	arbol_insertar(arbol, elemento_2);
	arbol_insertar(arbol, elemento_3);
	arbol_insertar(arbol, elemento_4);
	arbol_insertar(arbol, elemento_5);
	arbol_insertar(arbol, elemento_6);
	arbol_insertar(arbol, elemento_7);

	pa2m_nuevo_grupo("1)Pruebas  inorden");
	size_t leidos = abb_con_cada_elemento(arbol, 0, mostrar_elemento, NULL);
	printf("\n");
	pa2m_afirmar(leidos==7, "La cantidad de elementos iterados es la esperada");

	pa2m_nuevo_grupo("2)Pruebas  preorden");
	leidos = abb_con_cada_elemento(arbol, 1, mostrar_elemento, NULL);
	printf("\n");
	pa2m_afirmar(leidos==7, "La cantidad de elementos iterados es la esperada");

	pa2m_nuevo_grupo("3)Pruebas  postorden");
	leidos = abb_con_cada_elemento(arbol, 2, mostrar_elemento, NULL);
	printf("\n");
	pa2m_afirmar(leidos==7, "La cantidad de elementos iterados es la esperada");

	arbol_destruir(arbol);
}

int main(){
	pa2m_nuevo_grupo("Pruebas de creacion de arbol");
	probar_creacion_arbol();

	pa2m_nuevo_grupo("Pruebas de insercion de arbol");
	probar_insercion_arbol();

	pa2m_nuevo_grupo("Pruebas de borrar arbol");
	probar_borrar_arbol();

	pa2m_nuevo_grupo("Pruebas de busqueda de arbol");
	probar_busqueda_arbol();

	pa2m_nuevo_grupo("Pruebas recorrido inorden");
	probar_recorrido_inorden();

	pa2m_nuevo_grupo("Pruebas recorrido preorden");
	probar_recorrido_preorden();

	pa2m_nuevo_grupo("Pruebas recorrido postorden");
	probar_recorrido_postorden();

	pa2m_nuevo_grupo("Pruebas iterador interno:");
	probar_iterador_interno();

	return 0;
}