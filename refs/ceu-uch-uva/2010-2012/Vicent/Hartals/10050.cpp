#include <iostream>
using std::cin;
using std::cout;

bool dias[3650];
int parties[100];

int main()
{
  //casos de estudio
  int casos;
  cin >> casos;

  for ( int i=0; i < casos; ++i)
    {
      //numero de dias
      int N;
      cin >> N;

      //inicializar el vector de dias a false
      for ( int j = 0; j < N; ++j )
	{
	  dias[j] = false;
	}

      //numero de partidos
      int n_parties;
      cin >> n_parties;

      //cada cuantos dias hace huelga cada partido
      for ( int j = 0; j < n_parties; ++j )
	{
	  cin >> parties[j];
	}

      // a partir de aqui calculamos //////////////

      int cont = 0; //inicializamos contador

      for ( int j = 0; j < n_parties; ++j ) //para cada partido
	{
	  //vamos saltando por los dias. empezamos en -1 para solucionar un problema de saltos
	  for ( int d = -1; d < N; d += parties[j] ) 
	    {
	      //no contamos el dia -1 , ni los viernes, ni los sabados, ni los dias que ya se haya hecho huelga
	      if ( (d >= 0) && (d % 7 != 5) && (d % 7 != 6) && (dias[d] == false) )
		{
		  dias[d] = true; //hacemos huelga
		  ++cont; //aumentamos contador
		}
	    }
	}
	 
      // fin del calculo ///////////////////////////
	 
      cout << cont << "\n"; //mostramos el resultado
    }
  return 0;
}
