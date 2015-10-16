//
//  main.cpp
//  JollyJumper
//

#include <iostream>
#include <set>
#include <cmath>

using namespace std;

int jolly_jumper(int n)
{
    int actual, anterior;
    bool jolly = 1;
    set <int> estructura;
    
    cin >> anterior;
    
    for (int i=1; i<n; ++i)
    {
        cin >> actual;
        
        int dif = abs(actual - anterior); // calcula la diferencia.
        
        if ((dif > n -1) || (dif==0))         // primera condicion.
            jolly = 0;
        
       if (estructura.find(dif) == estructura.end())    // segunda condicion.
           estructura.insert(dif);
        else
            jolly = 0;
        
        anterior = actual;
    }
    
    if( estructura.size() != n-1)
        jolly =0;
    
    return jolly;
}

int main(int argc, const char * argv[])
{
    int n;
    
    while (cin >> n) {
        
        if (jolly_jumper(n) == 0)
            cout << "Not jolly" << endl;
        else
            cout << "Jolly" << endl;
    }
    
    return 0;
}

