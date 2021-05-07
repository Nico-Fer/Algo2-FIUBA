En el presente trabajo se realiza una simulacion de como Misty traslada pokemones del arrecife a su acuario.
Al inicio del programa se lee aun archivo de texto donde se encuentran los pokemones en el arrecife, si este 
no es valido se devuelve NULL, sino, se crea un arrecife.
Luego se crea un acuario vacio. Despues de esto, se crea un vector de punteros a funciones, donde en cada 
elemento de este vector apunta a una funcion booleana donde que servira para el traslado de los pokemones.
Siguiente a esto se trasladan los pokemones de forma iterativa, pedidos por misty, si devuelve true a una de las funciones booleanas.
Cuando se trasladan del acuario, se eliminan del arrecife. Y se muestra por pantalla los pokemones que quedan en el arrecife.
Si no hubo ningun problema al trasladar los pokemones, se escribe un archivo donde estan los pokemones del acuario.
Al final del programa, se libera la memoria utilizada.
Para compilar el programa se utiliza la linea: gcc -g  *.c -Wall -Wconversion -std=c99 -o evento_pesca.
Para compilar el programa con Valgrin se utiliza la linea: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca arrecife.txt acuario.txt
Y para ejecutarlo ./evento_pesca "arrecife.txt" "acuario.txt"
Tanto evento_pesca, arrecife.txt, acuario.txt son ejemplos de como escribirlos. Ya que, el primero representa el nombre del programa, 
el segundo un archivo de texto donde se encuentran los pokemones del arrecife y el tercero un archivo de texto para guardar los pokemones del acuario.

1) Punteros:
	        Un puntero es una variable que almacena una direccion de memoria.

2) Aritmetica de punteros:
		Operador de direccion(&):
								 Este permite acceder a la direccion de memoria de una variable.
		Por ejemplo:
					int x = 1;
					int* ptr = &x;
		En este ejemplo declaro un entero y un puntero a un entero, al cual le asigno la direccion de memoria de la variable x.									 
		Operador de indireccion(*):
								   Permite declarar a un tipo de dato puntero. Ademas sirve para acceder al contenido de la direecion de memoria del puntero.
		Siguiendo con el ejemplo anterior:
								   	      int x = 1;
										  int* ptr = &x;
										  int otro_entero = *ptr;
		Luego de asignarle la direccion de memoria de la variable x a ptr, declaro otra variable donde accedo al contenido al cual esta apuntando ptr.								  
		Incremento(+) y decremento(-):
									  Los punteros permiten utilizarlo como si fuera un array.
		Por ejemplo:
				    int x[75], *ptr_1, *ptr_2;
				    x[20]=1;
				    ptr_1 = x[20];
				    (*ptr_1)++;
				    (*ptr_1)--;
		Primero le asigno a ptr_1 la direccion de memoria de x[20], luego el "++" significa que el valor del puntero aumenta una unidad, es decir, ahora
		vale 2. Sucede algo parecido con el "--", pero decrementa una unidad al puntero, y vuelve a valer 1.		    

3) Punteros a funciones:
						Es la direccion de memoria de una determinada funcion en un programa. Ademas permite ejecutar la funcion desde cualquier parte del programa. Su sintaxis es:
						"tipo_de_retorno (*nombre_de_mi_funcion) (tipo_argumento_1, ..., tipo_argumento_n)"
						Los punteros a funcion pueden ser elementos de un vector, ser pasados como parametros a una funcio o ser devueltos por una funcion.

4) Malloc:
          Malloc reserva syze bytes y devuelve un puntero a la memoria reservada. Esta no esta inicializada, si no pudo reservar la memoria devuelve NULL. Su sintaxis es:
          void* malloc(size_t size);
          Si size es 0, malloc puede devolver NULL o un valor a un puntero unico.
          Por ejemplo:
          	int* ptr = malloc(sizeof(int));
          	En este ejemplo declaro un puntero a un entero, con lo cual malloc reserva 4 bytes y ptr apunta a la direccion de memoria asignada por esta funcion. El espacio reservado por malloc se encuentra en el heap.

  Realloc:
          Realloc modifica el tamaño de el bloque de memoria apuntada por un puntero en syze bytes. Existen tres posibles casos de lo que devuelve:

          1) Puede agrandar el tamaño del bloque y mi direccion de memoria es la misma.

          2) No puede agrandar el tamaño del bloque, pero puede asignar el espacio pedido en otra parte de la memoria. Con lo cual, devuelve un puntero a mi bloque de memoria nuevo, y el bloque viejo lo libera.

          3) No puede reservar memoria de ninguna de las formas anteriores, por lo tanto devuelve NULL.
          Su sintaxis es:
          				"void* realloc(void* ptr, size_t size)"
          Por ejemplo:
          	int* ptr = malloc(sizeof(int));
          	int* ptr_aux = realloc(ptr, sizeof(int)*2);
          	if(ptr_aux==NULL)
          		return NULL;
          	ptr=ptr_aux;	
          	Despues de reservar la memoria con malloc, declaro un puntero auxiliar, y le asigno la direccion de memoria que me devuelve realloc. 
          	Asigo a ptr_aux en vez de aux, por si fuera el caso en el que no pudo reservar la memoria, asi no pierdo la direccion de mi puntero.
            Si en vez de sizeof(int)*2 hubiese un 0, el realloc actuaria como un free().

