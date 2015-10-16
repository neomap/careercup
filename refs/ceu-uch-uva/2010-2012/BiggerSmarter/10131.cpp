/*******************************
* 10131 - Is Bigger Smarter?   *
* http://uva.onlinejudge.org   *
* Contest Volumes :: Volume CI *
*******************************/

#include <vector> //contiene la clase vector
#include <algorithm> //contiene la funcion sort()
#include <iostream> //contiene cin, cout y endl

using namespace std;

struct elefante
{
    int i; //indice
    int w; //peso
    int q; //inteligencia

    /*
     * Definimos el operador 'menor que' para poder usar la funcion
     * sort() de algorithm
     */
    bool operator<( const elefante e ) const
    {
      return (w < e.w);
    }
};
  
int main(void)
{
  int count = 0; //num elefantes (inicializacion a cero)

  vector<elefante> elefantes; //vector que guardara los elefantes que
			      //vayamos leyendo

  elefante aux; //lo rellenaremos al leer y luego lo insertaremos en
		//el vector

  while ( cin >> aux.w ) //mientras podamos leer (leemos el peso)
  {
    cin >> aux.q; //leemos la inteligencia
    aux.i = ++count; //anotamos el numero del elefante e incrementamos
		     //el contador de numero de elefantes

    elefantes.push_back(aux); //insertamos el elefante en el vector
  }

  //ordenar el vector de elefantes por peso ( se ordenara por peso ya
  // que el operador '<' de la estructura 'elefante' se ha definido
  // para comparar los pesos )
  sort(elefantes.begin(), elefantes.end());

  int g[count + 2]; //vector que guardara los estados del grafo
  int s[count + 2]; //vector donde anotaremos de donde viene cada
		    //estado del grafo

  g[0] = 0; //primer estado del grafo (no hemos metido ningun
	    //elefante, entonces la longitud de la secuencia es cero)
  s[0] = 0; //el estado cero viene de si mismo (perfecto para
	    //finalizar el recorrido del camino que hemos seguido en
	    //el grafo)
  
  for ( int i = 1; i < count + 1; ++i ) //para cada elefante...
  {
    g[i] = 0; //inicializamos el estado del grafo (el estado guarda la
	      //longitud de la secuencia de elefantes)
    s[i] = 0; //inicializamos el origen del estado (de donde viene ese
	      //estado)
     
    for (int j = 1; j < i; ++j ) //miramos los elefantes y estados
				 //anteriores... (el actual es 'i')
    {
      /*
       * requisitos para considerar valido al elefante que intento
       * meter en la secuencia ( elefante 'i' ):
       *   -la intelgincia tiene que ser menor
       *   -el peso tiene que ser mayor
       */
      if ( (elefantes[j-1].q > elefantes[i-1].q) && (elefantes[j-1].w < elefantes[i-1].w) )
      {
        //nos quedamos con el estado anterior que sea mas grande (asi
        //obtenemos la mejor forma de llegar al estado actual)
        if (g[j] > g[i])
        {
          g[i] = g[j]; //actualizamos el estado actual
          s[i] = j; //actualizamos el origen del estado actual
        }
      }
    }
    g[i]++; //al haber metido un elefante en la secuencia tenemos que
	    //incremetar el estado actual (incrementar la longitud de
	    //la secuencia)
  }

  g[count+1] = 0; //inicializamos el ultimo nodo del grafo
		  //(simplemente guardara una copia del estado mas
		  //grande del grafo)
  s[count+1] = 0; //inicializamos el origen del ultimo estado del
		  //grafo (sirve para poder recorrer el camino que se
		  //ha seguido para encontrar esa solucion)
  
  for ( int j = 0; j < count + 1; ++j ) //miramos todos los estados
					//del grafo
  {
    if (g[j] > g[count+1]) //nos quedamos con el estado mas grade
    {
      g[count+1] = g[j]; //actualizamos el estado
      s[count+1] = j; //actualizamos el origen
    }
  }

  //el resultado esta en g[count+1]
  cout << g[count+1] << endl; //mostramos la longitud de la secuencia
			      //de elefantes

  //recuperar el camino del grafo (que elefantes hemos metido en la
  //secuencia)
  int pos = s[count+1]; //esto nos dice cual es el estado solucion y a
			//partir de ahi iremos recorriendo hacia atras
  int out[g[count+1]]; //vector para reconstruir el camino al reves de
		       //como lo recuperamos (si lo mostramos tal cual
		       //lo recuperamos saldra invertido)
  int k = g[count + 1]; //contador para ir iterando sobre el vector
			//'out' (nos colocamos al final del vector
			//para ir insertando desde el final hasta el
			//principio)
  while ( pos != 0 ) //mientras no lleguemos a un estado que venga del
		     //estado cero...
  {
    out[--k] = elefantes[pos-1].i; //recuperamos el indice del
				   //elefante
    pos = s[pos]; //recorremos el camino hacia atras
  }

  //mostramos los elefantes
  for ( int j = 0; j < g[count + 1]; ++j )
  {
    cout << out[j] << endl;
  }

  return 0;
}

int max(int a, int b)
{
  if ( a > b )
    return a;
  else
    return b;
}
