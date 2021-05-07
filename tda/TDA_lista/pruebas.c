#include "lista.h"
#include "pa2mm.h"

static const int ERROR = -1;
static const int EXITO = 0;

void probar_creacion_lista(){
	lista_t* una_lista = lista_crear();
	pa2m_afirmar(una_lista!=NULL, "Se pudo crear una lista");
	pa2m_afirmar((*una_lista).cantidad == 0, "La lista tiene 0 elementos");
	pa2m_afirmar((*una_lista).nodo_inicio==NULL, "El primer elemento de una lista recien creada es NULL");
	pa2m_afirmar((*una_lista).nodo_fin==NULL, "El ultimo elemento de una lista recien creada es NULL");

	lista_destruir(una_lista);
}	
	
void probar_busqueda_elemento_nulo(){
	lista_t* una_lista = lista_crear();
	lista_insertar(una_lista, NULL);
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 0)==NULL, "Se encontro un elemento nulo en la lista");

	lista_destruir(una_lista);
}	

void probar_busqueda_ultimo_elemento(lista_t* una_lista){
	pa2m_nuevo_grupo("Pruebas de busqueda del ultimo elemento");

	lista_t* lista_vacia = lista_crear();
	pa2m_afirmar(lista_ultimo(lista_vacia)==NULL, "No busca el ulitmo elemento en una lista vacia");

	pa2m_afirmar(lista_ultimo(una_lista)==(*(*una_lista).nodo_fin).elemento, "Se encontro el elemento al final de la lista");
	pa2m_afirmar(lista_ultimo(NULL)==NULL, "No busca el ultimo elemento en una lista invalida");

	free(lista_vacia);
}	

void probar_busqueda_lista(lista_t* una_lista){	
	pa2m_nuevo_grupo("Pruebas de busqueda de lista");

	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 3)==(*(*una_lista).nodo_fin).elemento, "Se encontro un elemento al final de la lista");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 0)==(*(*una_lista).nodo_inicio).elemento, "Se encontro un elemento al inicio de la lista");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 1)==(*(*(*una_lista).nodo_inicio).siguiente).elemento, "Se encontro un elemento en la segunda posision de la lista");
	probar_busqueda_elemento_nulo();
	probar_busqueda_ultimo_elemento(una_lista);
}

void probar_cantidad_elementos(){
	lista_t* una_lista = lista_crear();
	pa2m_afirmar(lista_elementos(una_lista)==0, "La cantidad de elementos de una lista vacia es cero");

	int num = 1;
	lista_insertar(una_lista, &num);
	int num_2 = 3;
	lista_insertar_en_posicion(una_lista, &num_2, 0);
	int num_3 = 5;
	lista_insertar_en_posicion(una_lista, &num_3, 1);
	pa2m_afirmar(lista_elementos(una_lista)==3, "La cantidad de elementos de la lista es la esperada");

	pa2m_afirmar(lista_elementos(NULL)==0, "La cantidad de elementos de una lista invalida es cero");

	lista_destruir(una_lista);
}

void probar_insercion_lista(){	
	lista_t* una_lista = lista_crear();
	
	pa2m_afirmar(lista_insertar(una_lista, NULL)==EXITO && (*(*una_lista).nodo_fin).elemento==NULL, "Se inserto un elemento nulo al final de la lista.");
	
	int num = 1;
	pa2m_afirmar(lista_insertar(una_lista, &num)==EXITO && (*(int*)(*(*una_lista).nodo_fin).elemento)==num, "Se inserto un elemento al final de la lista.");
	
	int num_2 = 3;
	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &num_2, 0)==EXITO && (*(int*)(*(*una_lista).nodo_inicio).elemento)==num_2, "Se inserto un elemento al principio de la lista.");
	
	int num_3 = 5;
	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &num_3, 1)==EXITO && (*(int*)(*(*(*una_lista).nodo_inicio).siguiente).elemento)==num_3, "Se inserto un elemento despues del primer elemento.");

	pa2m_afirmar(lista_insertar(NULL, NULL)==ERROR, "No se inserta un elemento en lista invalida.");
	
	probar_busqueda_lista(una_lista);
	probar_cantidad_elementos(una_lista);

	lista_destruir(una_lista);	
}	

void probar_borrar_lista_un_elemento(){
	lista_t* una_lista = lista_crear();
	lista_insertar(una_lista, NULL);
	pa2m_afirmar(lista_borrar(una_lista)==EXITO && (*una_lista).nodo_inicio==NULL && (*una_lista).nodo_fin == NULL, "Se borro el unico elemento de la lista.");

	lista_destruir(una_lista);
}

void probar_borrar_lista_varios_elementos(){
	lista_t* una_lista = lista_crear();
	lista_insertar(una_lista, NULL);
	int num_1 = 1;
	lista_insertar(una_lista, &num_1);
	int num_2 = 2;
	lista_insertar(una_lista, &num_2);
	pa2m_afirmar(lista_borrar(una_lista)==EXITO , "Se borro el ultimo elemento de la lista.");

	lista_borrar(una_lista);
	lista_borrar(una_lista);
	pa2m_afirmar(lista_borrar(una_lista)==ERROR , "No se borra ningun elemento de una lista vacia.");

	lista_destruir(una_lista);
}

void probar_borrar_lista(){
	probar_borrar_lista_un_elemento();
	
	probar_borrar_lista_varios_elementos();
	
	pa2m_afirmar(lista_borrar(NULL) , "No se borra ningun elemento de una lista invalida.");
}

void probar_lista_vacia(){
	lista_t* una_lista = lista_crear();
	pa2m_afirmar(lista_vacia(una_lista)==true, "La lista recien creada esta vacia");
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 3)==ERROR, "No se puede borrar un elemento en una posicion arbitraria en una lista vacia");
	pa2m_afirmar(lista_borrar(una_lista)==ERROR, "No se puede borrar el ultimo elemento de una lista vacia");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 0)==NULL, "Pedir una posision en una lista vacia devuelve NULL");

	lista_insertar(una_lista, NULL);
	int num_1 = 1;
	lista_insertar(una_lista, &num_1);
	int num_2 = 2;
	lista_insertar(una_lista, &num_2);
	pa2m_afirmar(lista_vacia(una_lista)==false, "La lista contiene elementos");

	lista_destruir(una_lista);

	pa2m_afirmar(lista_vacia(NULL)==true, "Una lista invalida esta vacia.");
}	

void probar_borrar_elemento_en_posicion(){
	lista_t* una_lista = lista_crear();

	lista_insertar(una_lista, NULL);
	int num_1 = 1;
	lista_insertar(una_lista, &num_1);
	int num_2 = 2;
	lista_insertar(una_lista, &num_2);
	int num_3 = 5;
	lista_insertar_en_posicion(una_lista, &num_3, 1);

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 1)==EXITO && (*una_lista).cantidad==3 && (*(int*)(*(*(*una_lista).nodo_inicio).siguiente).elemento)==num_1, "Se elimino el segundo elemento de la lista");

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0)==EXITO && (*una_lista).cantidad==2 && (*(int*)(*(*una_lista).nodo_inicio).elemento)==num_1, "Se elimino un elemento nulo de la lista");

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 1)==EXITO && (*una_lista).cantidad==1 && (*(int*)(*(*una_lista).nodo_inicio).elemento)==num_1, "Se elimino el ultimo elemento de la lista");

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 1)==EXITO && (*una_lista).cantidad==0 && (*una_lista).nodo_inicio==NULL && (*una_lista).nodo_fin==NULL, "Posicion no valida, elimina el elemeno del final");

	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0)==ERROR, "No se puede borrar en una lista vacia.");

	pa2m_afirmar(lista_borrar_de_posicion(NULL, 9)==ERROR, "No se puede borrar en una lista invalida");

	lista_destruir(una_lista);

}
	
void probar_operaciones_pila(){
	lista_t* pila = lista_crear();

	int numeros[]={1,2,3,4,5,6};

    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        lista_apilar(pila, &numeros[i]);
    }

    pa2m_afirmar(lista_tope(pila)==(*(*pila).nodo_inicio).elemento, "El primer elemento es el esperado");

    pa2m_afirmar((*pila).cantidad==6  && (*(int*)(*(*pila).nodo_inicio).elemento)==numeros[5] && (*(int*)(*(*pila).nodo_fin).elemento)==numeros[0], "La pila apila con exito.");
    while(!lista_vacia(pila)){
        lista_desapilar(pila);
    }

    pa2m_afirmar(lista_apilar(NULL, NULL)==ERROR, "No apila en una pila invalida");

    pa2m_afirmar((*pila).cantidad==0  && (*pila).nodo_inicio==NULL && (*pila).nodo_fin==NULL , "La pila se desapilo con exito");

    pa2m_afirmar(lista_tope(pila)==(*pila).nodo_inicio && lista_tope(pila)==NULL, "Una pila vacia apunta a NULL");

    pa2m_afirmar(lista_desapilar(NULL)==ERROR, "No desapila en una pila invalida");
    
    lista_destruir(pila);
}

void probar_operaciones_cola(){
	lista_t* cola = lista_crear();

    int numeros[]={1,2,3,4,5,6};

    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        lista_encolar(cola, &numeros[i]);
    }

    pa2m_afirmar((*cola).cantidad==6  && (*(int*)(*(*cola).nodo_inicio).elemento)==numeros[0] && (*(int*)(*(*cola).nodo_fin).elemento)==numeros[5], "La cola se encola con exito.");
    pa2m_afirmar(lista_primero(cola)==(*(*cola).nodo_inicio).elemento, "El primer elemento es el esperado");

    while(!lista_vacia(cola)){
        lista_desencolar(cola);
    }

    pa2m_afirmar(lista_encolar(NULL, NULL)==ERROR, "No encola en una cola invalida");

    pa2m_afirmar((*cola).cantidad==0  && (*cola).nodo_inicio==NULL && (*cola).nodo_fin==NULL , "La cola se desacolo con exito");

    pa2m_afirmar(lista_tope(cola)==(*cola).nodo_inicio && lista_tope(cola)==NULL, "Una cola vacia apunta a NULL");

    pa2m_afirmar(lista_desencolar(NULL)==ERROR, "No desencola en una cola invalida");

    lista_destruir(cola);
}

void probar_iterador_en_lista_vacia(){
	lista_t* una_lista = lista_crear();
	lista_iterador_t* iterador = lista_iterador_crear(una_lista);
	pa2m_afirmar(iterador!=NULL , "Se pudo crear un iterador externo en una lista vacia");

	pa2m_afirmar(lista_iterador_elemento_actual(iterador)==lista_elemento_en_posicion(una_lista, 0) && lista_iterador_elemento_actual(iterador)==NULL, "El elemento actual en una lista vacia es NULL");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false, "El iterador en una lista vacia no tiene siguiente");
	pa2m_afirmar(lista_iterador_avanzar(iterador)==false, "El iterador en una lista vacia no puede avanzar");
	lista_iterador_destruir(iterador);
	lista_destruir(una_lista);
}

void probar_iterador_externo(){
	lista_t* una_lista = lista_crear();
	int num_1 = 10, num_2=20, num_3=4;
	lista_insertar(una_lista, &num_1);
	lista_insertar(una_lista, &num_2);
	lista_insertar(una_lista, &num_3);
	lista_iterador_t* iterador = lista_iterador_crear(una_lista);

	pa2m_afirmar(iterador!=NULL , "Se pudo crear un iterador externo");
	pa2m_afirmar((*iterador).corriente == (*una_lista).nodo_inicio, "El iterador creado apunta al inicio de la lista");

	pa2m_afirmar(lista_iterador_elemento_actual(iterador)==lista_elemento_en_posicion(una_lista, 0), "El primer elemento es el esperado");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==true, "El iterador tiene siguiente");

	lista_iterador_avanzar(iterador);
	pa2m_afirmar(lista_iterador_elemento_actual(iterador)==lista_elemento_en_posicion(una_lista, 1), "El segundo elemento es el esperado");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==true, "El iterador tiene siguiente");

	lista_iterador_avanzar(iterador);
	pa2m_afirmar(lista_iterador_elemento_actual(iterador)==lista_elemento_en_posicion(una_lista, 2), "El Ultimo elemento es el esperado");

	pa2m_afirmar(lista_iterador_avanzar(iterador)==false , "El iterador puede avanzar en el ultimo elemento y devuelve false");

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false, "El iterador no tiene siguiente");
	pa2m_afirmar(lista_iterador_avanzar(iterador)==false, "El iterador no puede avanzar");

	probar_iterador_en_lista_vacia();

	lista_iterador_destruir(iterador);
	lista_destruir(una_lista); 
}

bool mostrar_elemento(void* elemento, void* contador){
	if(!elemento)
		return false;
	printf("%i %i\n", *(int*)elemento, (*(int*)contador)++);
	return true;
}

void probar_iterador_interno(){
	lista_t* una_lista = lista_crear();
	int num_1 = 10, num_2=20, num_3=4;
	lista_insertar(una_lista, &num_1);
	lista_insertar(una_lista, &num_2);
	lista_insertar(una_lista, &num_3);

	int contador = 0;
	printf("imrpimo los elementos de la lista  y la cantidad de iteraciones\n");
	lista_con_cada_elemento(una_lista, mostrar_elemento, &contador);

	pa2m_afirmar(contador==3, "se iteraron todos los elementos esperados");

	lista_t* otra_lista = lista_crear();
	int otro_contador=0;
	lista_con_cada_elemento(otra_lista, mostrar_elemento, &otro_contador);
	pa2m_afirmar(otro_contador==0, "No itero en una lista vacia");
	pa2m_afirmar(lista_con_cada_elemento(otra_lista, NULL, &otro_contador)==0, "No itero sin funcion de iteracion.");

	lista_destruir(una_lista);
	lista_destruir(otra_lista);
}

void probrar_ingresar_5000_elementos_lista(){
	lista_t* una_lista = lista_crear();
	int vector_de_elementos[5000];
	for (int i = 0; i < 5000; i++){
		vector_de_elementos[i]=i;
		lista_insertar(una_lista, &vector_de_elementos[i]);
	}

	pa2m_afirmar((*una_lista).cantidad==5000, "Se insertaron 5000 elementos");
	lista_destruir(una_lista);
}

void probrar_ingresar_10000_elementos_lista(){
	lista_t* una_lista = lista_crear();
	int vector_de_elementos[10000];
	for (int i = 0; i < 10000; i++){
		vector_de_elementos[i]=i;
		lista_insertar(una_lista, &vector_de_elementos[i]);
	}

	pa2m_afirmar((*una_lista).cantidad==10000, "Se insertaron 10000 elementos");
	lista_destruir(una_lista);
}

void probrar_ingresar_30000_elementos_lista(){
	lista_t* una_lista = lista_crear();
	int vector_de_elementos[30000];
	for (int i = 0; i < 30000; i++){
		vector_de_elementos[i]=i;
		lista_insertar(una_lista, &vector_de_elementos[i]);
	}

	pa2m_afirmar((*una_lista).cantidad==30000, "Se insertaron 30000 elementos");
	lista_destruir(una_lista);
}

void pruebas_de_stress_de_lista(){
	probrar_ingresar_5000_elementos_lista();
	probrar_ingresar_10000_elementos_lista();
	probrar_ingresar_30000_elementos_lista();
}

int main(){
	pa2m_nuevo_grupo("Pruebas de creacion de lista");
	probar_creacion_lista();

	pa2m_nuevo_grupo("Pruebas de insercion de lista");
	probar_insercion_lista();

	pa2m_nuevo_grupo("Pruebas de borrar lista");
	probar_borrar_lista();

	pa2m_nuevo_grupo("Pruebas de lista vacia");
	probar_lista_vacia();

	pa2m_nuevo_grupo("Pruebas cantidad de elementos");
	probar_cantidad_elementos();

	pa2m_nuevo_grupo("Pruebas cantidad de borrar elemento en posision");
	probar_borrar_elemento_en_posicion();

	pa2m_nuevo_grupo("Pruebas operaciones de pila");
	probar_operaciones_pila();

	pa2m_nuevo_grupo("Pruebas operaciones de cola");
	probar_operaciones_cola();

	pa2m_nuevo_grupo("Pruebas iterador externo");
	probar_iterador_externo();

	pa2m_nuevo_grupo("Pruebas iterador interno");
	probar_iterador_interno();

	pa2m_nuevo_grupo("Pruebas de stress de lista");
	pruebas_de_stress_de_lista();

	pa2m_mostrar_reporte();

	return 0;
}