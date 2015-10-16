#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#define MAX 100
#define CARTAS 52
#define CARTASPALO 13

using namespace std;

vector <int> solucion(CARTAS);
vector <int> solucion2(CARTAS);
vector <int> final(CARTAS);
vector <string> palos;
vector <string> numero;
int N;
int matriz [MAX][CARTAS];

void inicializar (vector <int> &s) {
    for (int i=0; i<CARTAS; ++i) {
        s[i] = i;
    }
    
}

void barajar(int s) {
   int i;
    
   for (int j=0 ;j<CARTAS; ++j) {
       i=matriz[s][j];
       solucion2[j]=solucion[i];
   }    
    solucion2.swap(solucion);
}

void datos(int n){    
    for (int i=0; i<n; i++) {
        for (int j=0; j<CARTAS; j++) {
            cin >> matriz[i][j];
            --matriz[i][j];
        }
    } 
}



int main() {

    int cases, shuffles, barajados;
    string blanco, linea_vacia;
    
    palos.push_back("Clubs");
    palos.push_back("Diamonds");
    palos.push_back("Hearts");
    palos.push_back("Spades");
    numero.push_back("2");
    numero.push_back("3");
    numero.push_back("4");
    numero.push_back("5");
    numero.push_back("6");
    numero.push_back("7");
    numero.push_back("8");
    numero.push_back("9");
    numero.push_back("10");
    numero.push_back("Jack");
    numero.push_back("Queen");
    numero.push_back("King");
    numero.push_back("Ace");

    cin >> cases;
    
    for (int j=0; j<cases; ++j) {
        if (j > 0) cout << endl;
        
        cin >> shuffles;
        inicializar(solucion);
   
        datos(shuffles);
        getline(cin, linea_vacia);
        do {
            getline(cin, blanco);
               if (blanco.size() >0) {
                barajados =  atoi(blanco.c_str());
                --barajados;
                barajar(barajados);
              }
            } while(blanco.size() > 0);
        
        for (int i=0; i<CARTAS; ++i) {
        
            int num, palo;
            
            num = solucion[i] % CARTASPALO;
            palo = solucion[i] / CARTASPALO;
            
            cout << numero[num] << " of " << palos[palo] << endl;  
        }
    
      }
   return 0;
}