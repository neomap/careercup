#include <iostream>
#include <map>
#include <queue>
#include <list>
#include <set>

using namespace std;

int num_nodos_no_visitados(map <int,list<int> > &grafo, int start, int ttl) {
    
    queue <pair <int,int> > q;
    set <int> visitados;
    pair <int,int> aux;
    
    int nodo, dist;
    
    q.push(pair<int,int>(start,0));
    visitados.insert(start);
    
    while (!q.empty()){
        
        aux = q.front();
        nodo = aux.first ;
        dist = aux.second;
        q.pop();
        
        if (dist < ttl) {
            
            for (list <int>::iterator v=grafo[nodo].begin(); 
                    v!= grafo[nodo].end() ; ++v) {
              if (visitados.find(*v) == visitados.end()) {
                q.push(pair<int,int>(*v,dist+1));
                visitados.insert(*v);
              }
            }
        }
    }

    return grafo.size() - visitados.size();
}

int main() {
 
    int num_nodos,u,v,start,ttl;
    map <int,list<int> > grafo;
    int contador=0;
    // para cada grrafo
    while( (cin >> num_nodos) && num_nodos != 0 ) {  
        grafo.clear();
        // para cada conexion
         for (int i=0; i<num_nodos; ++i) {
        
            cin >> u >> v;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
        }
        // para cada caso
        do{
            cin >> start >> ttl;
        
         if (start == 0 && ttl == 0) {
            
                break;
         }
        
          else {
            
             int res = num_nodos_no_visitados(grafo,start,ttl);
             contador++;
             cout << "Case " << contador << ": " << res << " " <<"nodes not "
                "reachable from node " << start << " with TTL = " << ttl << "."
                     << endl;

         }
        
        }while (true);
    
    }
    
    
    return 0;
}
