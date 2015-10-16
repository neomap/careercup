// http://en.wikipedia.org/wiki/Catalan_number
// apuntar la formula aqui

#include<iostream>

using namespace std;

int main(){

    long int in,CatalanNumbers[]={1,2,5,14,42,132,429,1430,4862,16796,58786,208012,742900,2674440,9694845,35357670,129644790,477638700,1767263190,6564120420};

    while(cin>>in){
        for(int i=0;i<20;i++){
            if(CatalanNumbers[i]==in){
                cout<<i+1<<endl;
                break;
            }
        }
    }

return 0;
}
