#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <list>

using std::list;
using std::swap;
using std::map;
using std::vector;
using std::sort;
using std::cin;
using std::cout;

const int   max =   6000;
const float inf = -99999;

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )

#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

/** tabla hash estatica (conocemos su tamanyo, y las claves son
    numeros enteros) con timestamp **/
template<typename T>
class StaticHash {
  struct node_t {
    int timestamp;
    T   value;
  };
  int     current_stamp;
  node_t *V;
  int    *fast_iterator;
  int     size, used_size;
  T       inf; // valor nulo
public:
  
  class iterator {
    StaticHash *h;
    int         idx;
    iterator(StaticHash *h, int idx) : h(h), idx(idx) {
    }
  public:
    iterator(const iterator &it) {
      h   = it.h;
      idx = it.idx;
    }
    iterator &operator++() {
      while (h->V[h->fast_iterator[++idx]].timestamp != h->current_stamp);
      return *this;
    }
    int getKey() { return h->fast_iterator[idx]; }
    T   &getValue() { return h->V[h->fast_iterator[idx]].value; }
    bool operator!=(const iterator &other) {
      return (other.h != h || other.idx != idx);
    }
    bool operator==(const iterator &other) {
      return !((*this) != other);
    }
    friend class StaticHash;
  };
  
  friend class iterator;
  
  StaticHash(int size, T inf) : size(size), used_size(0), inf(inf) {
    V = new node_t[size];
    fast_iterator = new int[size];

    current_stamp = 1;
    for (int i=0; i<size; ++i)
      V[i].timestamp = 0;
  }
  
  ~StaticHash() {
    delete[] V;
    delete[] fast_iterator;
  };
  
  iterator begin() {
    return iterator(this, 0);
  }
  
  iterator end() {
    return iterator(this, used_size);
  }
  
  T &operator[](const int idx) {
    if (V[idx].timestamp != current_stamp) {
      V[idx].value     = inf;
      V[idx].timestamp = current_stamp;
      fast_iterator[used_size] = idx;
      ++used_size;
    }
    return V[idx].value;
  }
  
  void clear() {
    if (current_stamp >= 2<<28) {
      current_stamp = 1;
      for (int i=0; i<size; ++i)
	V[i].timestamp = 0;      
    }
    else ++current_stamp;
    used_size = 0;
  }
  
  T *search(int idx) {
    if (V[idx].timestamp == current_stamp) return &V[idx].value;
    return 0;
  }
  
  void insert(int idx, T value) {
    V[idx].value     = value;
    if (V[idx].timestamp != current_stamp) {
      V[idx].timestamp = current_stamp;
      fast_iterator[used_size] = idx;
      ++used_size;
    }
  }
  
  void erase(int idx) {
    V[idx].timestamp = current_stamp - 1;
  }
};

struct tortuga_t {
  float peso;
  float fuerza;
  tortuga_t(float p, float f) : peso(p), fuerza(f) { }
  bool operator<(const tortuga_t &b) const {
    return fuerza > b.fuerza;
  }
};

struct value_t {
  float score;
  list<int> turtles;
  value_t() {
  }
  value_t(float score) : score(score) {
  }
};

int main(void)
{
  float peso, fuerza;
  vector<tortuga_t> turtles;
  StaticHash<value_t> *current, *next;

  current = new StaticHash<value_t>(max, value_t(inf));
  next    = new StaticHash<value_t>(max, value_t(inf));
  
  while(cin >> peso >> fuerza)
    turtles.push_back(tortuga_t(peso, fuerza));
  
  sort(turtles.begin(), turtles.end());
  
  next->insert(0, value_t(0.0f));
  for(unsigned int k = 1; k <= turtles.size(); k++) {
    swap(current, next);
    
    next->clear();
    
    for (StaticHash<value_t>::iterator it = current->begin();
	 it != current->end(); ++it) {
      float     score;
      int       prev_N  = it.getKey();
      value_t   &prev_v = it.getValue();
      
      {
	/** No ponemos la tortuga, maximizamos **/
	value_t &next_v = (*next)[prev_N];
	if (prev_v.score > next_v.score) next_v = prev_v;
      }
      
      /***********************************************************
       ***********************************************************/
      
      /** La ponemos la ultima **/
      value_t &next_v = (*next)[prev_N+1];
      // solo hay una
      if (prev_N == 0) score = turtles[k-1].fuerza - turtles[k-1].peso;
      else {
	// hay mas de una
	score = prev_v.score;
	score = MIN(score - turtles[k-1].peso,
		    turtles[k-1].fuerza-turtles[k-1].peso);
      }

      // maximizamos
      if (score > 0.0f && score > next_v.score) {
	next_v.score   = score;
	next_v.turtles = prev_v.turtles;
	next_v.turtles.push_back(k-1);
      }
      
      /***********************************************************
       ***********************************************************/

      /** recorremos la lista de tortugas del origen, y tratamos de
	  insertar la nueva en alguna posicion anterior de dicha
	  lista **/
      /*
	float suma_pesos;
	for (list<int>::reverse_iterator j = prev_v.turtles.rbegin();
	j != prev_v.turtles.rend(); ++j) {
	int prev_turtle = *j;
	
	}
      */
      
      // comprobamos que next_v sea > 0, en caso contrario eliminamos
      // de la tabla hash
      if (next_v.score < 0.0f) next->erase(prev_N+1);
      
    }
    
    /*
      for (StaticHash<value_t>::iterator it = next->begin();
      it != next->end(); ++it) {
      printf ("(%d, %d)  %f\n",
      k, it.getKey(), it.getValue().score);
      }
    */
    
  }
  
  int m = 0;
  for (StaticHash<value_t>::iterator it = next->begin();
       it != next->end(); ++it) {
    int N = it.getKey();
    if (N > m) m = N;
  }
  printf ("%d\n", m);
  
  /*
    delete[] current;
    delete[] next;
  */
  return 0;
}
