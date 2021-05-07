 
                                                               TDA LISTA

Lo entregado es un tda lista simplemente enlazada con su set de primitivas. Ademas incluye un iterador interno, un iterador externo, y las funciones basicas de los TDA`s pila y cola.

La linea de compilacion es:

gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

La linea de ejecucion es:

valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se

Mi implementacion fue la siguiente:

lista_crear():
			  Reservo memoria en el heap llamando a calloc(), creando asi la lista y con sus valores ya inicializados, como cantidad=0, nodo_inicio = NULL, etc. Luego retorno un puntero a la lista creada.

lista_insertar():
				 Verifico que la lista recibida sea valida, luego reservo memoria en el heap para un nodo y me fijo que se haya podido reservar.
				 Si la lista recibida no es valida, retorno el valor -1, lo mismo si no se pudo reservar memoria para el nodo.
				 Si no hay ningun error, me fijo la cantidad de elementos de la lista, si la lista esta vacia, invoco a una funcion para insertar al primer elemento de la lista. Sino, inserto un elemento al final de la lista. En ambos casos, aumento lista->cantidad y retorno 1. 

lista_insertar_en_principio():
							  Verifico que la lista recibida sea valida, si no es valida devuelvo -1. 
							  Si no hay ninguna error, me fijo cual es el valor recibido de posicion. 
							  Si posicion==0, invoco a una funcion que me inserta un elemento al principio de la lista. En esta funcion reservo memoria para un nodo y verifico cual es la cantidad de elementos de la lista, si la cantidad es cero invoco otra funcion para insertar el primer elemento de la lista. Sino, inserto un elemento al inicio de la lista.
							  Si el valor de posicion es 1 y hay 1 elemento o mas en la lista, inserto un elemento despues del primer elemento de la lista.
							  Si no se cumple ninugna de las condiciones anteriores, invoco a lista_insertar() e inserto el elemento al final de la lista.
							  En caulquiera de los casos, si se pudo insertar el elemento, retorno 1. En caso contrario -1.

lista_borrar():
			   Si la lista recibida es invalida o la lista esta vacia, la funcion retorna -1.
			   Si la cantidad es 1, llamo a una funcion para borrar al unico elemento de la lista. En la cual libero al unico nodo y le asigno a nodo_fin y nodo_inicio NULL, reduzco la cantidad a cero, y retorno 1.
			   Sino, busco al anteultimo nodo con una funcion recursiva. Elegi este metodo ya que es mas facil de leer y entender el codigo. Despues de encontrarlo, le asigo una nodo auxiliar a este para no perder su referencia , libero el ultimo nodo de la lista y le asigno a la lista nodo_fin al anteultimo nodo, reduzco la cantidad y retorno 1.

lista_borrar_de_posicion():
						   Si la lista recibida es invalida o la lista esta vacia, la funcion retorna -1.
						   Si la posicion recibida es menor a cero o mayor o igual a la cantidad de elementos, invoco a lista_borrar() y elimino al ultimo elemento de la lista.
						   Si la posicion es 0, invoco a una funcion que elimina el primer elemento de la lista.
						   Si no se cumple ninguna de las condiciones anteriores, significa que la posicion recibida es valida, por lo tanto borro el elemento en dicha posicion. Declaro un nodo auxiliar, recorro la lista hasta el nodo anterior del que quiero eliminar, y el auxiliar apunta a este. Luego libero el nodo que queria eliminar, y enlazo los nodos. Si la cantidad resultante es 1, nodo_fin y nodo_inicio apuntan al mismo nodo.

lista_elemento_en_posicion():
							 Si la lista recibida es invalida, la posicion recibida es menor a cero o mayor o igual a la cantidad de elementos, devuelvo NULL.
							 Sino, asigno un nodo auxiliar que apunta al inicio y recorro la lista con un while hasta encontrar al elemento.
							 Luego, devuelvo un puntero a ese elemento. 

Luego estan las funciones como lista_vacia(), lista_ultimo(), etc. En donde solo verifico si la lista es valida y devuelvo lo pedido.


En las primitivas de pila y cola, son bastantes simples, ya que en todas verifico que la lista sea valida y luego llamo a una determinada primitiva de lista que cumpla con las condiciones de estos tda. Por ejemplo, en la funcion apilar(), solamente llamo a la funcion insertar_en_principio(), ya que es una funcion de la lista pero que cumple con la condicion de pila, en donde los elementos se inertan el el tope de la pila.



                                                                 LISTA


Una lista es un conjunto de elementos ordenados. Donde agrupa elementos, y cada uno tiene un sucesor (menos el ultimo) y un predecesor (menos el primero).
Este tipo de dato esta basado en los nodos enlazados. La idea del mismo reside en que un nodo al poder conocer a su siguiente puede crear una lista de nodos, esta lista termina cuando el ultimo nodo apunta a nada o a NULL.
Este tipo de dato abstracto tiene un conjunto de operaciones, las cuales son:

-Crear
-Insertar
-Insertar en posicion
-Borrar
-Borrar en posicion
-Elemento en posicion
-Ultimo
-Vacia
-Elementos
-Destruir

Existen muchas variantes de como se estructure su nodos y su comportamiento, algunas de ellas son:

-Simplemente enlazada
-Doblemente enlazada
-Circular

¿Cual es la diferencia entre simplemente enlazada y doblemente enlazada?

En una lista simplemente enlazada cada nodo conoce al nodo siguiente, de forma tal que es unidireccional su recorrido. Mientras que en una lista doblemente enlazada, cada nodo conoce al nodo siguiente y anterior, de forma que su recorrido es bidireccional.



.¿Cuales son las caracteristicas fundamentales de las pilas?

Una pila es una coleccion ordenanda de elementos en las que pueden insertarse y eliminarse por un extremo, denominada tope. Este tda tiene una estructura LIFO (last in, first out), es decir, el ultimo elemento que entro, es el primero en salir. Ademas, existen un conjunto de operaciones que se puden realizar, las cuales son:

-crear:
	   Crea la pila.
-Destruir:
		  Destruye la pila.
-Apilar:
		Ingresa un elemento en el tope de la pila.
-Desapilar:
		   Elimina un elemento en el tope de la pila.
-Vacia:
	   Verifica si la pila esta vacia o no.
-Tope:
	  Me dice cual es el elemento que esta en el tope de la pila.

Se puede implementar mediante vectores estaticos, vectores dinamicos, o nodos.

¿Y una cola?

Una cola, es un aestructura que posee de dos extremos, el inicio de la cola y el final. Es una estructura FIFO (first in, firs out), es decir, el primer elemento que entro, es el primero en salir. Tambien posee un conjunto de operaciones:

-crear:
	   Crea la cola.
-Destruir:
		  Destruye la cola.
-Encolar:
		Ingresa un elemento al final de la cola.
-Desencolar:
		   Elimina un elemento al inicio de la cola.
-Vacia:
	   Verifica si la cola esta vacia o no.
-Primero:
	  Me dice cual es el elemento que esta al inicio de la cola.





¿Que es un iterador?¿Cual es su funcion?

Un iterador es un tipo de dato abstracto, que me permite recorrer secuencialmente mi lista, sin tener que ser consciente de la estructura del mismo. Este, en algunos casos, me ayuda a reducir la complejidad algoritmica de mi programa al momento de recorrer mi lista.
Existen dos tipos de iteradores, el iterador externo y el interno. 
El iterador interno permite recorrer todos los elementos de la lista sin tener que controlar el ciclo en el cual se recorre el mismo. Para ello normalmente un iterador interno es una funcion que recibe tres parametros:

-La lista

-Un puntero a una funcion, que recibe un dato como el contenido de un nodo, otro puntero extra por si la funcion lo necesita

-Un puntero a void extra que funciona como nodo comun a todos los nodos visitados.

Mientras que un iterador externo es una TDA con un set de primitivas especiales que me permiten recorrer una estructura, osea, es una estructura externa a la estructura de la lista. Sus primitivas son:

-Crear
-Primero
-Siguiente
-HaySiguiente
-ElementoActual.

	   







       
