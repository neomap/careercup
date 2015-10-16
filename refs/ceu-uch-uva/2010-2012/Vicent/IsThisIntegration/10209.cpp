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
		double l = (2*( ( a/( 2*cos( PI/3 ) ) )*sin( PI/3 ) ) -a)*cos( PI/4 ); //lado del cuadrado central
		double A = l*l +4*( (PI*a*a/12) - (l*(sqrt( a*a - (l/2)*(l/2) ))/2) ); //area central
		double B = 2*((a*a - 2*(a*a - PI*a*a/4)) - A); //area de los petalos
		double C = a*a -A -B; //area restante

		printf("%.3f %.3f %.3f\n", A, B, C); //mostrar resultado
	}
	
	return 0;
}