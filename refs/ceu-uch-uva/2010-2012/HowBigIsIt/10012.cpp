#include <cfloat> //para usar la constante DBL_MAX
#include <cmath> //para usar la funcion sqrt (raiz cuadrada)
#include <iostream> //para usar cin
#include <cstdio> //para usar printf

using namespace std;

const int tam = 8; //el enunciado dice que como maximo nos pueden dar
		   //los radios de 8 circulos
double radios[tam]; //vector que guardara el radio de los circulos

/* En este vector guardaremos las posiciones X de los centros de los
   circulos. La posicion Y no hace falta porque todos los circulos
   estan tocando el suelo, entonces la posicion Y sera igual al radio.
   Ademas este vector no servira para saber los circulos que ya hemos
   metido en la caja. Si el circulo 'i' NO esta metido en la caja,
   c[i] vale -1. En caso contrario valdra la posicion X donde se
   encuentra su centro. */
double c[tam];

double backtrack( int m, int k ); //funcion de backtracking

/* La funcion calcularCentro() devuelve la posicion X donde se
   colocara el circulo 'i'.  Se calcula la posicion del circulo
   respecto de TODOS los demas circulos que ya esten metidos en la
   caja, y nos quedamos con la posicion mas grande (la de mas a la
   derecha). Esto se hace asi para evitar que el nuevo circulo que
   vamos a meter se coma (o solape en parte) a otros circulos que ya
   esten dentro de la caja */
double calcularCentro( int i, int m );

int main()
{
  //inicializar a -1 el vector solucion (el que guarda las posiciones
  //X de los centros)
  for ( int i = 0; i < tam; ++i )
    c[i] = -1;
  
  int n, m; //n = numero de instancias, m = numero de circulos (m
	    //cambiara con cada instancia)
  
  cin >> n; //leer numero de instancias

  for ( int i = 0; i < n; ++i ) //para cada instancia
    {
      cin >> m; //leer numero de circulos

      for ( int j = 0; j < m; ++j ) //para cada circulo...
	{
	  cin >> radios[j]; //...guardamos su radio
	}

      /* Llamamos a la funcion de backtracking para que nos de el
	 resultado.  Usamos %.3f porque tenemos que mostrar el
	 resultado con una precision de tres decimales.  Aprovechamos
	 la misma linea para mostrar el resultado devuelto por la
	 funcion de backtrackin, asi nos evitamos guardar el resultado
	 en una variable para luego mostrarla. */
      printf( "%.3f\n", backtrack(m, 0) );
    }
  
  return 0;
}

double backtrack( int m, int k )
{
  if ( m == 0) return 0;
  
  double ancho = DBL_MAX; //inicializamos el ancho al valor maximo que
			  //puede tomar
  double temp; //el ancho calculado lo guardaremos aqui, para despues
	       //comparar y actualizar la variable 'ancho'
  
  if ( k == m ) //si es solucion solucion (se han metido todos los
		//circulos dentro de la caja)
    {
      //procesar solucion
      double min, max; //extremo inferior y superior

      //inicializar los min y max
      min = c[0] - radios[0];
      max = c[0] + radios[0];
	 
      //actualizar el min y el max
      for ( int i = 1; i < k; ++i )
	{
	  if ( min > (c[i] - radios[i]) )
	    min = c[i] - radios[i];

	  if ( max < (c[i] + radios[i]) )
	    max = c[i] + radios[i];
	}

      //calcular ancho total
      return (max - min);
    }
 OB
  //EL FLUJO DEL PROGRAMA SIGUE AQUI SI K != M (no es solucion)

  ++k; //vamos a meter un circulo mas

  for ( int i = 0; i < m; ++i ) //para cada circulo
    {
      if ( c[i] == -1 ) //si el circulo no se ha metido ya...
	{
	  c[i] = calcularCentro(i, m); //calcular posicion X de su centro

	  temp = backtrack(m, k); //llamada recursiva a backtracking
	  if ( ancho > temp ) //si el ancho que tenemos es mayor que
			      //el que acabamos de calcular...
	    ancho = temp; //...actualizamos el ancho

	  /* IMPORTANTE Se restaura el estado (se saca el circulo que
	     hemos metido) para volver a llamar a backtracking con el
	     siguiente candidato (el siguiente circulo)
	  */
	  c[i] = -1;
	}
    }

  return ancho; //devolvemos el ancho (minimo)
}

double calcularCentro( int i, int m )
{
  double max_pos = radios[i]; //inicializamos el valor del maximo a la
			      //MINIMA posicion que puede ocupar el
			      //nuevo circulo
  
  for ( int j = 0; j < m; ++j ) //para cada circulo
    {
      if ( ( c[j] != -1 ) && ( j != i ) ) //si ese circulo no esta
					  //metido en la caja, y
					  //ademas no es el candidato
	{
	  double d, h, z, x, pos; //variables para hacer los calculos
				  //matematicos

	  //sacamos la posicion X del circulo resolviendo una ecuacion
	  //de segundo grado
	  d = (radios[j] + radios[i])*(radios[j] + radios[i]);
	  h = (radios[j] - radios[i])*(radios[j] - radios[i]);
	  x = c[j]*c[j];

	  z = d - h - x;
		
	  pos = ( 2*c[j] + sqrt(4*c[j]*c[j] + 4*z) )/2;
	  ///////////////////////////////////////////////////////////////

	  if ( pos > max_pos) //si la posicion esta mas a la derecha
			      //que maxima calculada hasta el
			      //momento...
	    max_pos = pos; //...actualizamos el maximo
	}
    }
  return max_pos; //devolvemos el maximo (que es la posicion que nos
		  //interesa, la de mas a la derecha)
}
