//
//  main.cpp
//  3n+1
//

#include <iostream>
#include <algorithm>

using namespace std;

unsigned int computarLongitudCiclo (unsigned int n) {
    
    unsigned int cont=0;
    
    while ( n != 1) {
        
        if ((n%2 == 0)) n = n/2;
        
        else
            n = 3*n +1;
        
        cont++;
    }
    
    return cont +1;
}

unsigned int computarCicloMaximo (unsigned int i, unsigned int j) {
    
    unsigned int ciclo_maximo=0;
    
    if (j < i)
        swap(i,j);
    
    for (unsigned int a = i; a <= j; ++a)
    {
        unsigned int longitud_ciclo = computarLongitudCiclo(a);
        
        if (longitud_ciclo > ciclo_maximo) ciclo_maximo = longitud_ciclo;
    }
    
    return  ciclo_maximo;
}

int main()
{
    unsigned int i, j;
    
    while (cin >> i >> j) {
        
        unsigned int ciclo_maximo = computarCicloMaximo(i,j);
        cout << i << " " << j << " " << ciclo_maximo << endl;
    }
    
    return 0;
}

