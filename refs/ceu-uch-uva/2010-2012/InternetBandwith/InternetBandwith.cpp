#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

/// clase Matrix para acceder a un vector contiguo en memoria como si
/// fuera una matriz bidimensional
template<typename T>
class Matrix {
  T *data;
  int w,h;
public:
  Matrix(int w, int h) : w(w), h(h) {
    data = new T[w*h];
  }
  ~Matrix() { delete[] data; }
  T *operator[](int i) {
    return data + w*i;
  }
};

// recorrido en anchura buscando el primer camino que empieza en s y
// acaba en t
int bfs(Matrix<int> &m, int v[100], int &min, int s, int t, int n)
{
  queue<int> cola;
  cola.push(s);
  int visitados[100];
  for(int i=0; i<n; i++) visitados[i] = -1; //no han sido visitados
  visitados[s] = s;
  
  while(!cola.empty() && visitados[t] == -1) {
    int current = cola.front();
    cola.pop();
    for(int i=0; i<n; i++) {
      if (visitados[i]==-1 && m[current][i]>0) {
	cola.push(i);
	visitados[i] = current;
      }
    }
  }
  
  if(visitados[t] == -1) return 0; //no hay camino
  
  int aux = t;
  
  min = m[t][visitados[aux]];
  int pos = 0;
  
  while(aux != s) {
    if (min > m[aux][visitados[aux]]) min = m[aux][visitados[aux]];
    v[pos++] = aux;
    aux = visitados[aux];
  }
  v[pos++] = aux;
  
  
  return pos;
}

long int fulkerson(Matrix<int> &m, int s, int t, int n)
{
  long int flujo = 0;
  int length;
  
  int v[100];
  int min;
  while( (length=bfs(m, v, min, s, t, n )) != 0) {
    
    flujo+=min;
    for(int i = 0; i<length - 1; i++){
      
      m[v[i]][v[i+1]] -= min;
      m[v[i+1]][v[i]] -= min;
      
    }
  }
  
  return flujo;
}

int main()
{
  int delta = 0;
  int n; //número nodos
  int s; //origen
  int t; //destino
  int c; //número conexiones en la red
  int u, v, w;
  Matrix<int> m(100,100);
  
  int network =0;
  
  while(cin >> n){
    
    if( n==0 ) break;
    network++;
    for(int i=0; i<100; i++) for(int j=0; j<100; j++) m[i][j] = 0;
    cin >> s >> t >> c;
    for(int i=0; i<c; i++) {
      cin >> u >> v;
      cin >>w;
      m[u-1][v-1] += w;
      m[v-1][u-1] += w;
    }
    
    if (network > 1) cout <<endl;
    cout << "Network "<< network<<endl;
    cout << "The bandwidth is "<<fulkerson(m, s-1, t-1, n) << "." << endl;
  }
  return 0;
}
