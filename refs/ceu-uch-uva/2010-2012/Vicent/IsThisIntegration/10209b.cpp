#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define PI 3.14159265358979323846

int main()
{
	double a;
	
	while ( cin >> a )
	{
		double A = a*a*0.2798; //area central
		double B = 2*( a*a - ( a*a - (PI*a*a/12) ) - ( a*a - (PI*a*a/12) ) - A ); //area de los petalos
		double C = a*a -B -A; //area restante

		printf("%.3f %.3f %.3f\n", A, B, C); //mostrar resultado
	}
	
	return 0;
}
