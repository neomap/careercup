#include <iostream>
using std::cout;
using std::cin;

unsigned int cycleTime(unsigned int n);

int main()
{
	unsigned int original_i; //guardara el primer numero introducido
	unsigned int original_j; //guardara el segundo numero introducido
	
	/****************************************************************
	 * Las variables 'i' y 'j' guardaran los numeros con los que realmente
	 * trabajaremos. Ademas estaran en orden, de manera que 'i' sera el
	 * numero menor y 'j' sera el mayor. Es decir, 'original_i' no tiene
	 * porque corresponder necesariamente con 'i' y 'original_j' tampoco
	 * tiene que corresponder necesariamente con 'j'. Es posible que se
	 * hayan introducido los numeros en orden inverso, de esta forma tendremos
	 * los numeros en el orden que se han introducido (en las variables original)
	 * para luego poder mostrarlos tal cual se introdujeron, y tendremos
	 * tambien los numeros en el orden correcto para poder hacer los
	 * calculos (en las variables 'i' 'j')
	 ***************************************************************/
	unsigned int i;
	unsigned int j; 
	
	unsigned int cycle_time; //guarda el cycle_time de un numero
	unsigned int max_cycle_time = 1; //guarda el cycle_time maximo
	
	/* leer dos numeros que formaran el intervalo */
	while (cin >> original_i >> original_j)
	{
		/* comprobar el orden e invertir si es necesario */
		if ( original_i > original_j )
		{
			i = original_j;
			j = original_i;
		}
		else
		{
			i = original_i;
			j = original_j;
		}
		
		/* calcular el cycle_time para cada valor del intervalo */
		for ( unsigned int n = i; n <= j; ++n )
		{
			cycle_time = cycleTime(n);
			//si el crycle_time que acabamos de calcular es mayor que el maximo...
			if ( cycle_time > max_cycle_time )
				max_cycle_time = cycle_time; //actualizamos el maximo
		}

		/* imprimir el valor maximo del cycle_time */
		cout << original_i << ' ' << original_j << ' ' << max_cycle_time << '\n';

		//devolvemos el maximo al estado original para proceder con la siguiente entrada de numeros
		max_cycle_time = 1;
	}

	return 0;
}

unsigned int cycleTime(unsigned int n)
{
	//cualquier numero tiene como minimo un cycle_time de uno
	unsigned int cycle_time = 1;

	while ( n != 1 ) //si no es un uno...
	{
		if ( n % 2 == 0 ) //si el numero es par...
			n /= 2; //ahora el numero vale la mitad
		else //si no es par...
			n = 3*n + 1; //ahora el numero vale el triple, mas uno

		++cycle_time; //aumentamos el numero de ciclos
	}
	
	return cycle_time; //devolvemos el numero d ciclos
}
