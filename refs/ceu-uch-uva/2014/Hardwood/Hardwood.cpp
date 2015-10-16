#include <iostream>
#include <map>
#include <string>
#include <cstdio>

using namespace std;

typedef map<string,int> SpeciesCounts;
typedef SpeciesCounts::iterator SpeciesIterator;

void procesar_arbol(SpeciesCounts &arboles, const string &arbol) {
   
    SpeciesIterator it =  arboles.find(arbol);
    
    if (it == arboles.end()){
        
        arboles.insert(pair<string,int>(arbol,1));
   
    }
    
    else {
    
        it->second = it-> second +1; 
    }
}

void calcular(SpeciesCounts &arboles, int &num){
    
    SpeciesIterator it;
    float result;
    
    for (it = arboles.begin(); it != arboles.end(); it++){
        
        result = it -> second / float(num) * 100.0f;
        printf("%s %.4f\n", it->first.c_str(), result);
    }
}



int main() {
    int cases;
    string linea_vacia, linea, arbol;
    
    cin >> cases;
    getline (cin,linea_vacia);
    getline (cin,linea_vacia);

    for (int i=0; i< cases; ++i) {
        if (i >0) cout << endl;
        
        SpeciesCounts arboles;
        int tamany = 0;
      
        do {
            getline (cin, linea);
            if (linea.size() > 0 ) {
            
                
                procesar_arbol(arboles, linea);
                tamany++;
            
             }
        }while (linea.size() > 0);
        
         calcular (arboles,tamany);
    }    
    
    
    
    return 0;
}