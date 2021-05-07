Introduccion:
			 Lo entregado es una aventura pokemon, donde el usuario debe cargar un archivo con un personaje y archivos con gimnasios, donde el personaje luchara a traves de todos los gimnasios hasta convertirse en un maestro pokemon o faalar en el intento.

Compilacion:
			La linea de compilacion es "gcc *.c  utiles.o -o juego -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0".

Ejecucion: La linea de ejecucion es "valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego".

Funcionamiento:
		       La idea del TP es simular batallas pokemon, mientras estoy en gimnasios.

		       El TP arranca con una introduccion pidiendole al usario que desea hacer. Entre estas opciones se presentan: Cargar personaje, Cargar gimnasio, Jugar la partida y Simular la partida.

		       Si el usuario decide jugar la partida o simularla, sin antes no haber cargado un gimnasio y un personaje, el programa no lo dejara.
		       Cuando el usuario elija la opcion de cargar personaje, le saldra un menu pidiendole que cargue un archivo del mismo. Si el personaje no se pudo cargar por algun error, el juego termina.

		       No se puede cargar archivos con gimnasios repetidos, con una dificultad negativa, y que los entrenadores y el personaje tengan pokemon repetidos.

		       Lo mismo sucede con el gimnasio, aparecera un menu por pantalla pidendo que ingreseun archivo gimnasio. Si hay algun error en la creacion del gimnasio, el juego termina.

		       Cuando se carguen el personaje y el/los gimnasio/s se podra jugar o simular la partida.
		       Si se decide jugar, aparecera otro menu donde tendra las siguientes opciones: Mostrar personaje, mostrar gimnasio en donde esta, cambiar los pokemon de mi personaje y realizar la proxima batalla.

		       Mostrar personaje: Lo que hace es mostrar los pokemon del personaje, junto a sus estadisticas, y donde se encuentran (En el party o la caja).

		       Mostrar gimnasio: Muestra el gimnasio actual por pantala, su nombre su dificultad y los entrenadores, junto a su numero de pokemon.

		       Cambiar pokemon: Permite cambiar el pokemon del party con uno de la caja. Le pide al usuario el nombre del pokemon de la caja y la posicion del que se encuentra en el party.
		       Se crea una funcion booleana y una estructura auxiliar, donde esta funcion la utilizo con el iterador interno del arbol para recorrer el arbol y encontrar el pokemon por su nombre y almacenarla en mi estructura auxiliar.
		       Luego sabiendo la posicion del pokemon el el party, invoco a la funcion de personaje_principal.c donde se realiza el cambio.

		       Realizar proxima batalla: Se invoca a la funcion batalla, donde se crean dos while, el primero es para recorrer los entrenadores del gimnasio y otro para recorrer los pokemon de cada uno de ellos. Si gana el personaje, la proxima batalla seria con el mismo pokemon del personaje y con el siguiente del entrenadores. Si se vencen todos los pokemon de un entrenador, este queda afuera del gimnasio, y se avanza al suiguiente entrenador. Asi hasta llegar con el lider. Cuando se gana al lider, aparecera un menu de victoria.
		       En este menu de victoria, el usuario debera elegir entre las siguientes opciones:

		       Tomar pokemon: Muestra por pantalla los pokemon del lider y el usuario decide que pokemon quiere quedarse. El pokemon agregado se queda en la caja del personaje.

		       Cambiar pokemon: La misma opcion mencionada previamente.

		       Proximo gimnasio: Como no quedan mas entrenadores, el gimnasio en donde se encontraba el personaje es eliminado y se avanza al siguiente. Si no hay mas gimnasios, se gana la partida.
		       Cuando empiece en un gimnasio nuevo, se vuelve a repetir el menu de cuando se empezo a jugar.

		       Si todos los pokemon en el party del personaje pierden, habra perdido la partida y se mostrara un menu de derrota.
		       En este menu, el usuario debera elegir entre las siguientes opciones:

		       Cambiar pokemon: La misma opcion mencionada previamente.

		       Reintentar: Vuelve a intentar la partida desde el entrenador con el que perdio.

		       Finalizar: Se finaliza la partida y el juego termina.

Estructuras:
			El TP cuenta con varias estructuras: lista, abb, heap binario, gimnasio, entrenador, pokemon, personaje.

			La estructura del gimnasio se implemento como un heap minimal, para que el gimnasio mas facil, sea siempre el primero y asi acceder con mayor facilidad. Ademas de que al momento de eliminar el gimnasio, sea siempre la raiz.

			Los entrenadores se implemento como una pila, por la lectura del archivo, es decir, el primer entrenador leido (el lider), sea el ultimo en combatir con el personaje. Ademas de tener una mayor facilidad de eliminar el entrenador, ya que hay una primitiva definida en el TDA lista.

			Los pokemon del entrenador como los que se encuentran en el party del personaje fueron implementados como una cola por la logica de combate, es decir, el primer pokemon leido del archivo va a ser el primer pokemon en pelear.

			Los pokemon que se encuentran en la caja se implemento como un abb para que sea de menor complejidad la busqueda. Ya que, en el peor de los casos, se degenerara en lista.

			Ademas, la estructura lista se tuvo que modificar, agregando un destructor en las funciones de borrar y destruir.

Comentarios:
			Al momento de implementar el heap, gimnasio y personaje principal, se hicieron una serie de pruebas a cada una de estas estructuras.
			Las pruebas vendran en una carpeta llamada pruebas y otra carpeta llamada archivos, donde se encuentran todos los archivos con los que realice las pruebas.
			Ademas se cuenta con el enunciado del TP.
			Utilice el archivo utiles.o solamente para detener el tiempo por pantalla cuando debo mostrar a que entrenador se vencio.


