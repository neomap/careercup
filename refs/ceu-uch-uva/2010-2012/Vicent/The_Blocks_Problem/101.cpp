#include <stack> //clase pila de la STL
using std::stack; //para poder usar stack (pila)

#include <iostream> //clases entrada salida
using std::cin; //para poder usar cin (lectura de entrada estandar)
using std::cout; //para poder usar cout (escritura en salida estandar)

#include <string> //clase string de la STL
using std::string; //para poder usar string (cadena)

/* Vector que contiene pilas de bloques. (los bloques se representan con un numero entero)
*  El enunciado dice que el numero de bloques que podemos tener estara siempre entre 1 y 25
*  Inicialmente cada pila contiene un bloque que coincide con su numeracion. Por ejemplo, la
*  pila '0' contiene al bloque '0', la pila '1' contiene al bloque '1', etc. */
stack<int> blocks[25];

/* Vector que guardara las posiciones (dentro del vector de pilas ) en las que se encuentran
*  las pilas. Nos servira para saber en que pila esta cierto elemento. Por ejemplo, para saber
*  en que pila esta el elemento '3' solo tendremos que consultar blocks_ptr[3]. Si el contenido
*  es '5', significara que el elemento '3' se encuentra en la pila numero '5', y podremos
*  accerder a la pila mediante blocks[5] */
int blocks_ptr[25];

stack<int> aux_a; //pila auxiliar para ir desapilando hasta encontrar un bloque 'a'
stack<int> aux_b; //pila auxiliar para ir desapilando hasta encontrar un bloque 'b'

int pos_a; //guardara la posicion (dentro del vector de pilas ) en la que se encuentra la pila que contiene al bloque 'a'
int pos_b; //guardara la posicion (dentro del vector de pilas ) en la que se encuentra la pila que contiene al bloque 'b'

/*************************************************************************************
* Funcion move_onto:
* Mueve el bloque 'a' encima del bloque 'b'
* Todos los bloques que habia encima de 'a' y 'b' vuelven a sus posiciones de origen
**************************************************************************************/
void move_onto(int a, int b);

/*************************************************************************************
* Funcion move_over:
* Mueve el bloque 'a' a la cima de la pila en la que se encuentra el bloque 'b'
* Todos los bloques que habia encima de 'a' vuelven a sus posiciones de origen
**************************************************************************************/
void move_over(int a, int b);

/*************************************************************************************
* Funcion pile_onto:
* Mueve el bloque 'a', y todos los que esten encima suya, encima del bloque 'b'
* Todos los bloques que habia encima de 'b' vuelven a sus posiciones de origen
**************************************************************************************/
void pile_onto(int a, int b);

/*************************************************************************************
* Funcion pile_over:
* Mueve el bloque 'a', y todos los que esten encima suya, a la cima de la pila en la
* que se encuentra el bloque 'b'
**************************************************************************************/
void pile_over(int a, int b);

int main(void)
{
  int n; //guardara el numero de bloques
	
	cin >> n; //leemos numero de bloques

  //inicializamos las pilas y las posiciones
  for ( int i = 0; i < n; ++i )
  {
	 blocks[i].push(i); //el bloque 'i' se apila en la pila 'i'
	 blocks_ptr[i] = i; //la pila que contiene al bloque 'i' esta en la posicion 'i'
  }

  string com1; //cadena para guardar los comandos move y pile
	string com2; //cadena para guardar los comandos onto y over

	int a, b; //guardan el numero de los bloques con los que se quiere operar

	while ( cin >> com1 ) //empezamos a pedir comandos
  {
	 if ( com1 == "quit" ) //si el primer comando es quit
		break; //salimos del bucle

	 //si no se ha salido del bucle... (el primero comando no era quit)
	 cin >> a >> com2 >> b; //leemos los numeros de bloques con los que se quiere operar y el segundo comando

	if ( (a != b) && (blocks_ptr[a] != blocks_ptr[b]) ) //si 'a' y 'b' son diferentes y no esten en la misma pila...
	 {
		//a partir de aqui empezamos a operar con los bloques dependiendo de los comandos que se hayan introducido
		if ( com1 == "move" ) //si el primer comando es 'move'...
		{
		  if ( com2 == "onto" ) //...y el segundo es 'onto'...
		  {
				move_onto(a,b); //llamamos a la funcion 'move_onto'
		  }
		  else if ( com2 == "over" ) //si el segundo es 'over'...
		  {
				move_over(a,b); //llamamos a la funcion 'move_over'
		  }
			else //si el segundo comando no es ni 'onto' ni 'over', no se hace nada (lo especifica el enunciado)
		  {
				;
		  }
		}
		else if ( com1 == "pile" ) //si el primer comando es 'pile'...
		{
			if ( com2 == "onto" ) //...y el segundo es 'onto'...
		  {
				pile_onto(a,b); //llamamos a la funcion 'pile_onto'
		  }
			else if ( com2 == "over" ) //si el segundo es 'over'...
		  {
				pile_over(a,b); //llamamos a la funcion 'pile_over'
		  }
			else //si el segundo comando no es ni 'onto' ni 'over', no se hace nada (lo especifica el enunciado)
		  {
				;
		  }
		}
		else //si el primer comando no es ni 'move' ni 'pile', no se hace nada (lo especifica el enunciado)
		  ;
	 }
	 else //si 'a' es igual a 'b' , o estan en la misma pila, no se hace nada (lo especifica el enunciado)
		;
  }

  //mostrar el estado final de los bloques
	for ( int i = 0; i < n; ++i )
  {
		cout << i << ':'; //mostramos el numero de bloque

		//se desapila y se apila en una pila auxiliar
		while ( !blocks[i].empty() ) //mientras la pila no este vacia
		{
			aux_a.push( blocks[i].top() ); //apilamos (push) la cima (top) de la pila 'i' en la pila auxiliar
			blocks[i].pop(); //desapilamos (pop) el elemento de la cima de la pila 'i'
		}

		//se desapila la pila auxiliar y asi se consigue mostrar en orden
		while ( !aux_a.empty() ) //mientras la pila no este vacia
		{
			cout << ' ' << aux_a.top(); //mostramos la cima de la pila
			aux_a.pop(); //desapilamos la cima
		}

		cout << '\n';
  }

  return 0;
}

void move_onto(int a, int b)
{
	pos_a = blocks_ptr[a]; //para saber en que pila esta el bloque 'a'
	pos_b = blocks_ptr[b]; //para saber en que pila esta el bloque 'b'
	
	while ( blocks[pos_a].top() != a ) //mientras el bloque 'a' no este en la cima de la pila
	{
		aux_a.push( blocks[pos_a].top() ); //desapilamos bloques y los metemos en una pila auxiliar 'aux_a'
		blocks[pos_a].pop(); //ahora es cuando realmente se desapila. antes solo estabamos copiando la cima
	}
	
	while ( blocks[pos_b].top() != b ) //mientras el bloque 'b' no este en la cima de la pila
	{
		aux_b.push( blocks[pos_b].top() ); //desapilamos bloques y los metemos en una pila auxiliar 'aux_b'
		blocks[pos_b].pop(); //ahora es cuando realmente se desapila. antes solo estabamos copiando la cima
	}

	//en este punto tenemos los bloques 'a' y 'b' en la cima de sus respectivas pilas
	
  //mover 'a' sobre 'b'
	blocks[pos_b].push( blocks[pos_a].top() ); //apilamos el bloque 'a' en la pila donde esta el bloque 'b'
  blocks[pos_a].pop(); //desapilamos el bloque 'a'. antes solo hemos copiado la cima
  blocks_ptr[a] = blocks_ptr[b]; //ahora el bloque 'a' esta en la misma pila que el bloque 'b'

  //devolver los que estaban sobre 'a' y 'b' a sus posiciones iniciales
  while ( !aux_a.empty() ) //repetir hasta vaciar la pila
  {
	 blocks[ aux_a.top() ].push( aux_a.top() ); //apilamos el bloque en la pila que lo contenia inicialmente, es decir, la que coincide con su numero de bloque
	 blocks_ptr[ aux_a.top() ] = aux_a.top(); //actualizamos la posicion de la pila en la que se encuentra el bloque que acabamos de mover
	 aux_a.pop(); //aqui es cuando realmente se desapila. antes solo copiabamos la cima
  }
	
	while ( !aux_b.empty() ) //repetir hasta vaciar la pila
  {
		blocks[ aux_b.top() ].push( aux_b.top() ); //apilamos el bloque en la pila que lo contenia inicialmente, es decir, la que coincide con su numero de bloque
		blocks_ptr[ aux_b.top() ] = aux_b.top(); //actualizamos la posicion de la pila en la que se encuentra el bloque que acabamos de mover
		aux_b.pop(); //aqui es cuando realmente se desapila. antes solo copiabamos la cima
  }
}

void move_over(int a, int b)
{
	pos_a = blocks_ptr[a]; //para saber en que pila esta el bloque 'a'
	pos_b = blocks_ptr[b]; //para saber en que pila esta el bloque 'b'
	
	while ( blocks[pos_a].top() != a ) //mientras el bloque 'a' no este en la cima de la pila
	{
		aux_a.push( blocks[pos_a].top() ); //desapilamos bloques y los metemos en una pila auxiliar 'aux_a'
		blocks[pos_a].pop(); //ahora es cuando realmente se desapila. antes solo estabamos copiando la cima
	}

	//en este punto el bloque 'a' se encuentra en la cima de su pila
	
	//mover 'a' a la cima de la pila donde esta 'b'
	blocks[pos_b].push( blocks[pos_a].top() ); //apilamos el bloque 'a' en la pila donde esta el bloque 'b'
	blocks[pos_a].pop(); //desapilamos el bloque 'a'. antes solo hemos copiado la cima
	blocks_ptr[a] = blocks_ptr[b]; //ahora el bloque 'a' esta en la misma pila que el bloque 'b'

	//devolver los que estaban sobre 'a' a sus posiciones iniciales
	while ( !aux_a.empty() ) //repetir hasta vaciar la pila
	{
		blocks[ aux_a.top() ].push( aux_a.top() ) ; //apilamos el bloque en la pila que lo contenia inicialmente, es decir, la que coincide con su numero de bloque
		blocks_ptr[ aux_a.top() ] = aux_a.top(); //actualizamos la posicion de la pila en la que se encuentra el bloque que acabamos de mover
		aux_a.pop(); //aqui es cuando realmente se desapila. antes solo copiabamos la cima
	}
}

void pile_onto(int a, int b)
{
	pos_a = blocks_ptr[a]; //para saber en que pila esta el bloque 'a'
	pos_b = blocks_ptr[b]; //para saber en que pila esta el bloque 'b'
	
	while ( blocks[pos_a].top() != a ) //mientras el bloque 'a' no este en la cima de la pila
	{
		aux_a.push( blocks[pos_a].top() ); //desapilamos bloques y los metemos en una pila auxiliar 'aux_a'
		blocks[pos_a].pop(); //ahora es cuando realmente se desapila. antes solo estabamos copiando la cima
	}
	
	while ( blocks[pos_b].top() != b ) //mientras el bloque 'b' no este en la cima de la pila
	{
		aux_b.push( blocks[pos_b].top() ); //apilamos el bloque 'a' en la pila donde esta el bloque 'b'
		blocks[pos_b].pop(); //ahora es cuando realmente se desapila. antes solo estabamos copiando la cima
	}

	//en este punto tenemos los bloques 'a' y 'b' en la cima de sus respectivas pilas

	//mover 'a' sobre 'b'
	blocks[pos_b].push( blocks[pos_a].top() ); //apilamos el bloque 'a' en la pila donde esta el bloque 'b'
	blocks[pos_a].pop(); //desapilamos el bloque 'a'. antes solo hemos copiado la cima
	blocks_ptr[a] = blocks_ptr[b]; //ahora el bloque 'a' esta en la misma pila que el bloque 'b'
	
	//mover los bloques que habia encima de 'a' sobre 'b' (en realidad seria sobre 'a' , ya que 'a' acaba de ser apilado sobre 'b')
	while ( !aux_a.empty() ) //repetir hasta vaciar la pila
	{
		blocks[pos_b].push( aux_a.top() ); //apilamos el bloque de la cima en la pila donde esta el bloque 'b'
		blocks_ptr[ aux_a.top() ] = blocks_ptr[b]; //ahora ese bloque esta en la misma pila que 'b'
		aux_a.pop(); //ahora es cuando realmente se desapila. antes solo copiabamos la cima
	}

	//devolver los que estaban sobre 'b' a sus posiciones iniciales
	while ( !aux_b.empty() ) //repetir hasta vaciar la pila
	{
		blocks[ aux_b.top() ].push( aux_b.top() ); //apilamos el bloque en la pila que lo contenia inicialmente, es decir, la que coincide con su numero de bloque
		blocks_ptr[ aux_b.top() ] = aux_b.top(); //actualizamos la posicion de la pila en la que se encuentra el bloque que acabamos de mover
		aux_b.pop(); //aqui es cuando realmente se desapila. antes solo copiabamos la cima
	}
}

void pile_over(int a, int b)
{
	pos_a = blocks_ptr[a]; //para saber en que pila esta el bloque 'a'
	pos_b = blocks_ptr[b]; //para saber en que pila esta el bloque 'b'
	
	while ( blocks[pos_a].top() != a ) //mientras el bloque 'a' no este en la cima de la pila
	{
		aux_a.push( blocks[pos_a].top() ); //desapilamos bloques y los metemos en una pila auxiliar 'aux_a'
		blocks[pos_a].pop(); //ahora es cuando realmente se desapila. antes solo estabamos copiando la cima
	}

	//mover 'a' a la cima de la pila donde esta 'b'
	blocks[pos_b].push( blocks[pos_a].top() ); //apilamos el bloque 'a' en la pila donde esta el bloque 'b'
	blocks[pos_a].pop(); //desapilamos el bloque 'a'. antes solo hemos copiado la cima
	blocks_ptr[a] = blocks_ptr[b]; //ahora el bloque 'a' esta en la misma pila que el bloque 'b'

	//mover los bloques que habia encima de 'a' a la cima de la pila donde esta 'b' (y ahora tambien 'a', ya que acaba de ser apilado)
	while ( !aux_a.empty() ) //repetir hasta vaciar la pila
	{
		blocks[pos_b].push( aux_a.top() ); //apilamos el bloque de la cima en la pila donde esta el bloque 'b'
		blocks_ptr[ aux_a.top() ] = blocks_ptr[b]; //ahora ese bloque esta en la misma pila que 'b'
		aux_a.pop(); //ahora es cuando realmente se desapila. antes solo copiabamos la cima
	}
}