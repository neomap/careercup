#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using std::map;
using std::swap;

int main() {
  vector<int>   w;
  map<int,int> *current = new map<int,int>;
  map<int,int> *next    = new map<int,int>;
  
  int M;
  scanf("%d", &M);
  for (int m = 0; m<M; ++m) {
    if (m > 0) printf("\n");
    w.clear();
    int  N;
    int  W=0;
    scanf("%d", &N);
    for (int i=0; i<N; ++i) {
      scanf("%d", &w.push_back(i));
      W += w[i];
    }
    
    current->clear();
    next->clear();
    (*current)[0] = 0;
    // para cada persona
    for (int k=0; k<N; ++k) {
      next->clear();
      // para cada estado activo
      for (map<int,int>::iterator it = current->begin();
	   it != current->end();
	   ++it) {
	// la metemos en el equipo A
	(*next)[it->first - w[k]] = it->second - 1;
	// la metemos en el equipo B
	(*next)[it->first + w[k]] = it->second + 1;
	//printf ("%d :: %d %d :: %d\n", k, it->first, it->second, w[k]);
      }
      swap(current,next);
    }
    int diff = -1, besta, bestb;
    for (map<int,int>::iterator it = current->begin();
	 it != current->end();
	 ++it) {
      //printf ("%d :: %d %d\n", N, it->first, it->second);
      if (-1 <= it->second && it->second <= 1) {
	if (diff == -1 || fabs(it->first) < diff) {
	  diff = fabs(it->first);
	}
      }
    }
    besta = (W + diff) / 2;
    bestb = besta - diff;
    if (besta > bestb) swap(besta,bestb);
    printf ("%d %d\n", besta, bestb);
  }
}
