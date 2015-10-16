
#include <iostream>
#include <set>
#include <math.h>
#define MAX 1000000
using namespace std;

set <int> setprimos;
char marcados[MAX+1];

void generar_primos(){

	int i, mitad;

	for (i = 0; i <= MAX; ++i) {
		
		marcados[i] = 1;
	}

	marcados[0] = 0;
	marcados[1] = 0;
	
	mitad = sqrt(MAX);

		for(i = 2; i <= mitad; ++i) 
			if (marcados[i] == 1) {

				for(int j = 2 * i;  j <= MAX; j+=i) {
					marcados[j]=0; 
				}
		}
}

void pasar_primo(){

	for (int i=0; i <= MAX ; ++i) {

		if (marcados[i] == 1) {

			setprimos.insert(i);
		}
	}
}

void calcular_num(int num) {

	set<int>::iterator it;

	for (it=setprimos.begin(); it != setprimos.end() && *it <= num/2; ++it)
	{
		int a = *it;
		int b = num - a; 

		if (setprimos.find(b) != setprimos.end()) {
			
			cout << num << " = " << a << " + " << b << endl;
			return;
		}
	}

	cout << "Goldbach's conjecture is wrong." << endl;		
}

int main () {

	int numero_final, aux, numero1, numero2;
	
	generar_primos();
	pasar_primo();

	do{ 	
		cin >> numero_final;
		
		if ( numero_final == 0) break;

		calcular_num(numero_final);

	}while(numero_final!=0); 

	return 0;
}