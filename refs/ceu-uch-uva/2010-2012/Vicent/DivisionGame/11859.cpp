#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

/*
Obtiene todos los numeros primos que existen
hasta un numero dado y los guarda en un vector
*/
void obtenerPrimos( vector<int> &v, int num );

/*
Cuenta todas las divisiones que se
le pueden hacer a un numero
*/
int countNumDivisions( int num );

/*
Guardara todos los primos que
existen entre 2 y 10000
*/
vector<int> primos;

/*
Guardara el tamanyo de las pilas (filas)
para despues calcular la nim-sum
*/
vector<int> pilas;

int main( void ) { 
  /*
  Obtenemos todos los primos que existen entre 2 y 10000
  y los almacenamos en el vector 'primos'
  */
  obtenerPrimos( primos, 10000 );
  
  //numero de casos de test
  int T;
  cin >> T;
  
  for ( int i = 0; i < T; ++i ) { //para cada caso de test...
    int num_divisions = 0; //inicializar el numero de visiones
    int N, M;
    int num;
    
    cin >> N >> M; //leemos el numero de filas y columnas de la matriz
    
    //a continuacion leemos todos los numeros de la matriz
    for ( int row = 0; row < N; ++row ) {
      for ( int col = 0; col < M; ++col ) {
        cin >> num; //leemos el numero correspondiente a la fila 'row' columna 'col'
        num_divisions += countNumDivisions( num ); //calculamos cuantas divisiones se le pueden hacer y las acumulamos
      }
      
      /*
      El numero de divisiones que se le pueden hacer a todos
      los numeros de la fila sera el tamanyo de nuestra pila
      */
      pilas.push_back( num_divisions );
      
      num_divisions = 0; //reseteamos el numero de divisiones
    }
    
    /*
    http://en.wikipedia.org/wiki/Nim
    
    Theorem. In a normal Nim game, the player making the first move has a winning
    strategy if and only if the nim-sum of the sizes of the heaps is nonzero.
    Otherwise, the second player has a winning strategy.
    */
    
    /*
    http://en.wikipedia.org/wiki/Nim
    Calcular la nim-sum de todas las pilas
    */
    int nim_sum = pilas[0];
    for ( unsigned int k = 1; k < pilas.size(); ++k ) {
      nim_sum ^= pilas[k];
    }

    if ( nim_sum != 0 ) { //si la nim_sum es diferente de cero...
      cout << "Case #" << (i+1) << ": YES" << endl; //ganamos
    }
    else { //si es igual a cero...
      cout << "Case #" << (i+1) << ": NO" << endl; //perdemos
    }
    
    pilas.clear(); //reseteamos las pilas

  }
   
  return 0;
}

void obtenerPrimos( vector<int> &v, int num) {
  bool esPrimo = true;
  
  for ( int i = 2; i <= num; ++i ) {
    for ( int j = 2; j <i; ++j ) {
      if ( i % j == 0 ) {
        esPrimo = false;
        break;
      }
    }
    
    if ( esPrimo ) {
      v.push_back( i );
    }
    
    esPrimo = true;
  }
}

int countNumDivisions( int num ) {
  int num_divisions = 0;
  int i = 0;
  
  while ( num != 1 ) {
    while ( num % primos[i] == 0 ) {
      num /= primos[i];
      ++num_divisions;
    }
    ++i;
  }
  
  return num_divisions;  
}
