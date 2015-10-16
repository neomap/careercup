

#include <iostream>
#define MAX 10000

using namespace std;


int main()
{
	long long int i,k,dia;
	long long int aux;
	while(cin >> k >> dia){
		aux=0;
		for(i=k;;i++){
			aux= aux + i;
			if(aux>=dia){
				cout << i <<endl;
				break;}
			} 
		}
	return 0;
}

