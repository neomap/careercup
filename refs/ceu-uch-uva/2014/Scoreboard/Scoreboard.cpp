#include <iostream>
#include <algorithm>
#include <sstream>

#define NUMPROB 9
#define PENALTI 20
#define MAXGRUPOS 100
using namespace std;

class Grupo {
    
    int id_grupo;
    int num_prob;
    int tiempo_acumulado;
    int intentos[NUMPROB];
    bool submission;
    bool check[NUMPROB];
    
public: 
    
    void apuntar_fallo(int prob){
        ++intentos[prob];
    }
    void apuntar_acierto(int prob, int tiempo) {
        if (check[prob]==false){
        num_prob++;
        tiempo_acumulado += tiempo;
        tiempo_acumulado += PENALTI*intentos[prob];
        }
        check[prob]=true;
    }
    Grupo(int _id_grupo) {
        id_grupo = _id_grupo;
        num_prob = 0;
        tiempo_acumulado = 0;
        submission = false;
        for (int i=0; i < NUMPROB; ++i) {
            intentos[i]=0;
            check[i]=false;
        }
               
    }
    Grupo () {}
    
    void submiss () {
        submission = true;
    }    
    int getId()const {  
        return id_grupo;
    }    
    int getNumProblem()const {   
        return num_prob;
    }   
    int getTiempo()const {     
        return tiempo_acumulado;
    }
    
    void mostrar(){
       
        if (submission == true) {
        cout << id_grupo + 1 <<" "<<num_prob <<" "<< tiempo_acumulado << endl;
        }
    }
};

Grupo grupos[MAXGRUPOS];

bool compare(const Grupo &a, const Grupo &b) {
    
    int Na = a.getNumProblem();
    int Nb = b.getNumProblem();
    int Ta = a.getTiempo();
    int Tb = b.getTiempo();
    int ida = a.getId();
    int idb = b.getId();
    
    if (Na > Nb) return true;
    else if (Na < Nb) return false; 
    else if (Ta == Tb) {
        
        return ida < idb;
    }
    else {
        return Ta < Tb;
    }
}

int main () {
    
    int cases;
    string linea, linea_vacia;
  
    cin >> cases;
    getline (cin,linea_vacia);
    getline (cin,linea_vacia);

    for (int i=0; i< cases; ++i) {
        if (i >0) cout << endl;
        
        for (int j=0; j<MAXGRUPOS; ++j) {            
            grupos[j] = Grupo(j); // Asignacion por copia
        }
        
        do {   
            getline(cin,linea);
            if (linea.size() == 0) break;

            int id, num, tiempo;
            string estado;            
            stringstream stream;            
            stream << linea;            
            stream >> id >> num >> tiempo >> estado;            
            id = id -1;            
            num = num -1;            
            grupos[id].submiss();
             
            if (estado == "C") {               
                grupos[id].apuntar_acierto(num,tiempo);                
            }            
            else if (estado == "I") {
                grupos[id].apuntar_fallo(num);
            }
        } while (linea.size() != 0);
        
        sort(grupos+0, grupos+MAXGRUPOS, compare);
        
        for (int a=0; a<MAXGRUPOS; ++a) {
        grupos[a].mostrar();       
        }
        
    }
    return 0;
}