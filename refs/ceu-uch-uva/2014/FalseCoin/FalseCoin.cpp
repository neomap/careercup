#include <iostream>
#include <set>
#include <algorithm>
#define MAX 100

using namespace std;

void borrar_elementos(set <int> &destino, set <int> &elementos) {
    
    set <int> aux; 
    
    set_difference(destino.begin(),destino.end(),elementos.begin(),elementos.end(),
            inserter(aux,aux.begin()));
    destino = aux;    
}

set <int> interseccion(set <int> &destino, set <int> &elementos){
    
    set <int> aux; 
    
    set_intersection(destino.begin(),destino.end(),elementos.begin(),elementos.end(),
            inserter(aux,aux.begin()));
    return aux;    
}

set <int> union_set(set <int> &destino, set <int> &elementos){
    
    set <int> aux;
    
    set_union(destino.begin(),destino.end(),elementos.begin(),elementos.end(),
            inserter(aux,aux.begin()));
    return aux; 
}

void compare_set(string sign, set <int> &der, set <int> &izq, set <int> &lt, set <int> &gt) {
    
    if (sign == "=") {
     
        borrar_elementos(lt,der);
        borrar_elementos(lt,izq);
        borrar_elementos(gt,der);
        borrar_elementos(gt,izq);
    } 

     else if (sign == "<") {
        
        lt = interseccion(lt,izq);
        borrar_elementos(lt,der);
        gt = interseccion(gt,der);
        borrar_elementos(gt,izq);
     }
    
       else {
         
            gt = interseccion(gt,izq);
            borrar_elementos(gt,der);
            lt = interseccion(lt,der);
            borrar_elementos(lt,izq);
       }
}

void inicializar(set <int> &aux, int n){
        
    for (int i=1; i<=n; ++i) {
        
        aux.insert(i);
    }
}

void mostrar(set <int> &aux) {
    
    set <int>::iterator it;
    
    for (it=aux.begin(); it!=aux.end(); ++it) {
        
        cout << *it << endl;
    }
}

int main()
{
    int cases,N,K;
    
    cin >> cases;
    
    for (int i=0; i<cases; i++) {
        if (i >0) cout << endl;

        cin >> N >> K;
        
        set <int> lt;
        set <int> gt;
        set <int> aux;
       
        inicializar(lt, N);
        inicializar(gt, N);

        for (int j=0; j<K; j++) {
            set <int> derecha;
            set <int> izquierda;
            int num;
            string signo;
            cin >> num;
            
            for (int z=0; z<num; z++) {
                
                int elem;
                cin >> elem;
                izquierda.insert(elem);
            }
            
            for (int a=0; a<num; a++){
                int elem2;
                cin >> elem2;
                derecha.insert(elem2);
            }
            
            cin >> signo;
            compare_set(signo,derecha,izquierda,lt,gt);
        }
        
       aux = union_set(lt,gt);
       set <int>::iterator it;
       it = aux.begin();

       if (aux.size() == 1) {
           
           cout << *it << endl;
       }
        
       else cout << "0" << endl;
    }
    
    return 0;
}