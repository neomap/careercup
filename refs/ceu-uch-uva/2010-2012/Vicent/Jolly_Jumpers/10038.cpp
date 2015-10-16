#include <iostream>
#include <cstdlib> //para usar la funcion abs (valor absoluto)
using namespace std;

bool differences[3000]; //en este vector anotaremos las ocurrencias de las diferencias
int numbers[3000]; //aqui guardaremos la secuencia de numeros que nos pasan por la entrada estandar

int main(void)
{
	int n; //cantidad de numeros que componen la secuencia
	
	while ( cin >> n ) 
	{
		for ( int i = 0; i < n; ++i ) //leemos n numeros de la entrada estandar
		{
			cin >> numbers[i]; //guaramos los numeros en un vector
		}

		bool jj = true; //suponemos que es jolly jumper
		int diff; //aqui guardaremos el calculo de la diferencia
		
		for ( int i = 0; i < n-1; ++i ) //recorreremos el vector de numeros para ir calculando diferencias consecutivas
		{
			diff = abs(numbers[i] - numbers[i+1]); //calcular diferencia
			
			if ( (diff > 0) && (diff < n) ) //si la diferencia esta entre 1 y n-1
			{
				differences[diff] = true; //la anotamos
			}
			else
			{
				jj = false; //ya no es jolly jumper
				break;
			}
		}

		if ( jj ) //si al terminar de recorrer el vector todavia sigue siendo jolly jumper (hipotesis)
		{
			for ( int i = 1; i < n; ++i ) //comprobar que las diferencias consecutivas toman todos los valores desde 1 hasta n-1
			{
				if ( differences[i] != true ) //si hay alguna que no esta
				{
					jj = false; //ya no es jolly jumper
					break;
				}
			}
		}

		if ( jj ) //si es jolly jumper
		{
			cout << "Jolly\n";
		}
		else
		{
			cout << "Not jolly\n";
		}

		for ( int i = 1; i < n; ++i ) //limpiamos el vector de diferencias
		{
			differences[i] = false;
		}
	}
	
	return 0;
}