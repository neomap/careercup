#include <iostream>
using namespace std;

double amounts[1000]; //aqui se guardara el dinero que gasta cada estudiante
double round(double a); //esta funcion redondeara las cantidades hasta los centimos

int main()
{
	int n; //numero de estudiantes
	double average = 0; //guardara la media
	double total = 0; //guardara el total
	
	while ( cin >> n ) //leemos el numero de estudiantes
	{
		if ( n == 0 ) //si es cero salimos (condicion de parada, lo dice el enunciado)
			break;
		
		for ( int i = 0; i < n; ++i ) //para cada estudiante
			cin >> amounts[i]; //nos guardamos lo que ha gastado

		//calculamos la media
		for ( int i = 0; i < n; ++i )
		{
			average += amounts[i]; //la suma de lo que se ha gastado cada estudiante...
		}
		average /= n; //...dividido por el numero de estudiantes

		//redondeamos la media hasta los centimos
		average = round(average);

		//calculamos cuanto dinero cambiara de manos, de dos maneras...

		//la primera forma es restar la media a las cantidades mas grandes que la media
		double total1 = 0;
		for ( int i = 0; i < n; ++i )
		{
			if ( average < amounts[i] )
				total1 += amounts[i] - average;
		}

		//la segunda forma es restarle a la media las cantidades menores que la media
		double total2 = 0;
		for ( int i = 0; i < n; ++i )
		{
			if ( average > amounts[i] )
				total2 += average - amounts[i];
		}

		//tenemos que quedarnos con el total minimo y que NO sea cero
		if ( total1 != 0 )
			if ( total2 != 0 )
				if ( total1 < total2 )
					total = total1;
				else
					total = total2;
			else
				total = total1;
		else
			total = total2;
		///////////////////////////////////////////////////////////

		printf("$%.2f\n",total); //mostrar resultado

		total = 0; //limpiar total
		average = 0; //limpiar media
	}
	return 0;
}

double round(double a)
{
	double x, y, z;
	
	x = a*100;
	y = int(x);
	z = x - y;

	if ( z > 0.49 )
		++y;

	return y/100;
}
