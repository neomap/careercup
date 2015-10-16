#include <iostream>
using std::cout;
using std::cin;

#include <string>
using std::string;

char campo[100][100];
int n, m;

//estas dos variables nos serviran para visitar las 8 casillas vecinas utilizando un solo bucle for
int posi[] = {0,0,1,-1,1,1,-1,-1};
int posj[] = {1,-1,0,0,1,-1,1,-1};

void contarMinas(int i,int j);

int main(void)
{
  string fila; //guardara una fila completa de la matriz
  int count = 1; //cuenta los campos de minas

  while ( cin >> n >> m )
  {
  	//condicion de parada del programa (lo dice el enunciado)
	 if ( n == 0 && m == 0 )
		break;

	//si vamos a mostrar mas de un campo de minas hay que dejar una linea en blanco
	 if ( count > 1 )
		cout << '\n';
	 
	 //rellenar campo de minas
	 for ( int i = 0; i < n; ++i )
	 {
		cin >> fila; //leemos una fila entera

		for ( int j = 0; j < m; ++j ) //recorremos la fila caracter a caracter
		{
		  campo[i][j] = fila[j]; //metemos el caracter en la matriz
		}
	 }

	 //contar minas (recorremos cada casilla del campo de minas)
	 for ( int i = 0; i < n; ++i )
	 {
		for ( int j = 0; j < m; ++j )
		{
		  if ( campo[i][j] == '.' ) //si en la casilla no hay una mina...
		  {
			 contarMinas(i,j); //contamos las minas que tiene alrededor
		  }
		}
	 }

	 //mostrar campo de minas
	 cout << "Field #"<< count << ":\n";
	 for ( int i = 0; i < n; ++i )
	 {
		for ( int j = 0; j < m; ++j )
		  cout << campo[i][j];
		cout << '\n';
	 }
	 
	 ++count; //aumentamos el contador de campos
  }
  
	return 0;
}

void contarMinas(int i, int j)
{
  campo[i][j] = '0'; //inicializamos la casilla a 0 (todavia no hemos contado ninguna mina)

  for ( int k = 0; k < 8; ++k) //miramos las 8 casillas vecinas
  	//controlamos que no nos salimos del campo de minas y que hay una mina en la casilla vecina que estamos mirando
	 if ( ((i + posi[k]) >= 0) && ((j + posj[k]) >= 0) && ((i + posi[k]) < n) && ((j + posj[k]) < m) && campo[i+posi[k]][j+posj[k]] == '*' )
		++campo[i][j]; //actualizamos el valor de la casilla aumentando en una unidad el numero de minas
}
