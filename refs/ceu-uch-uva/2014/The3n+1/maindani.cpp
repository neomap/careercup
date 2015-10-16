#include <iostream>

using namespace std;

unsigned int  calcular(unsigned int  i){
    unsigned int cont=0;
    while (i!=1){

            if (i%2!=0){
                   i=(3*i)+1;
            }
                else {
                   i=i/2;
                }
        cont++;

    }
        return cont+1;
}

int main()
{
    unsigned int  i,j,z;
    unsigned int  maxim=0, ciclo=0;

    while(cin>>j>>i){

    maxim=0;
    for(z=i; z<=j; z++){

        ciclo = calcular(z);

        if (ciclo>maxim) maxim = ciclo;

    }
        cout<<i<<" "<<j<<" "<<maxim<<endl;
    }
    return 0;
}
