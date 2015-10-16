#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>

#define max( a, b ) ( (a) > (b) ) ? (a) : (b)
#define min( a, b ) ( (a) < (b) ) ? (a) : (b)

struct keyhash {
  unsigned long int operator()(const int &k) const {
    static unsigned long int cte_hash= 2654435769U;
    return k*cte_hash;
  }
};

struct keyeq {
  bool operator()(const int &a, const int &b) const { return a == b; }
};

template <typename T1, typename T2>
struct pair {
  T1 first;
  T2 second;

  typedef T1 first_type;
  typedef T2 second_type;

  // Constructors
  pair() : first(T1()), second(T2()) {}
  pair(const T1& first, const T2& second):
    first(first), second(second) {}
  pair(const pair &other):
    first(other.first), second(other.second) {}

  pair& operator=(const pair& other) {
    if (&other != this) {
      first = other.first;
      second = other.second;
    }
    return (*this);
  }
};


template<typename T1, typename T2>
bool operator== (const pair<T1,T2>& x, const pair<T1,T2>& y) {
  return ((x.first == y.first) && (x.second == y.second));
}

template<typename T1, typename T2>
bool operator< (const pair<T1,T2>& x, const pair<T1,T2>& y) {
  return (( x.first <  y.first) || 
	  ((x.first == y.first) && (x.second < y.second)));
}

//----------------------------------------------------------------------
template<typename T> struct default_hash_function
{
  static const unsigned int cte_hash  = 2654435769U; // hash Fibonacci
  long int operator()(const T& key) const {
    unsigned int resul = 1;
    unsigned int length = sizeof(T);
    const unsigned char *r = reinterpret_cast<const unsigned char *>(&key);
    for (unsigned int i=0; i<length; i++) {
      resul = (resul+(unsigned int)(r[i]))*cte_hash;
    }
    return resul;
  }
};

template<typename T> struct default_equality_comparison_function
{
  bool operator()(const T& i1, const T& i2) const {
    return i1 == i2;
  }
};

//----------------------------------------------------------------------
// Hash function for ints (operator == is OK)
//
template<> struct default_hash_function<int> {
  static const unsigned int cte_hash  = 2654435769U; // hash Fibonacci
  long int operator()(const int &i) const {
    return cte_hash*i;
  }
};


// hash open addressing
/* Tabla hash con direccionamiento abierto y timestamps

   Se utiliza un vector para guardar directamente los valores. Cuando
   se busca un valor, se utiliza la función de dispersión para obtener
   2 valores: el indice en el vector y un offset para ir avanzando
   (modulo talla del vector) mientras las posiciones consultadas esten
   ocupadas por valores distintos del elemento buscado. La busqueda
   finaliza cuando se encuentra una posición libre o bien el elemento
   buscado.

   La forma de saber si una posición esta ocupada es comprobar el
   campo stamp. De esta forma se pueden borrar TODOS los elementos del
   vector en O(1). Nótese que NO se borran efectivamente esos
   elementos, no se llama a su destructor.

   Los tipos de datos para los campos clave y valor asumen que el
   operador de copia funciona suficientemente bien como para que al
   "machacar" una posición del vector con un valor nuevo, el valor
   anterior se libere convenientemente.

   También se asume que ambos tipos de datos tienen constructores por
   defecto.

   No se puede asumir que un valor estará siempre en la misma
   posición, al menos tras realizar inserciones, puesto que vamos a
   implementar rehashing.

   No existe la operacion erase para borrar individualmente una
   entrada.

*/

template <typename KeyType, typename DataType, 
	  typename HashFcn = default_hash_function<KeyType>, 
	  typename EqualKey = default_equality_comparison_function<KeyType> >
class open_addr_hash_timestamp {
public:
    
  struct node {
    pair<const KeyType,DataType> value;
    int stamp;
    node(): value(KeyType(), DataType()) {}
    node(KeyType& k, DataType& d, int stmp):
      value(k,d), stamp(stmp) {}
  };

  typedef KeyType         key_type;
  typedef DataType        data_type;
  typedef pair<const key_type, data_type> value_type;
  typedef value_type&     reference;
  typedef const reference const_reference;
  typedef value_type*     pointer;
  typedef ptrdiff_t       difference_type;
  typedef size_t          size_type;

private:
  node *buckets;  // vector of nodes
  int num_buckets;// a power of 2
  int hash_mask;  // useful to do "& hash_mask" instead of "% num_buckets"
  int the_size;
  int rehash_threshold;
  float max_load_factor; // for rehashing purposes, MUST BE <1.0
  int current_stamp;
  static const int max_stamp = 1<<30;
  int first_power_of_2(int value);// auxiliary function
  HashFcn hash_function;
  EqualKey equal_key;
public:
  open_addr_hash_timestamp(int nbckts=1024, float mxloadf=0.5); // constructor
  open_addr_hash_timestamp(const open_addr_hash_timestamp&);   // copy constructor
  ~open_addr_hash_timestamp(); // destructor
  open_addr_hash_timestamp& operator=(const open_addr_hash_timestamp&);  // assignment operator
      
  void clear(); // Erases all of the elements.
  data_type* find(const key_type& k);
  const value_type* find_pair(const key_type& k) const;
  bool search(const key_type& k) const {
    return find_pair(k) != 0;
  }
  data_type& operator[] (const key_type& k);
  void insert(const key_type& k, const data_type& d) {
    (*this)[k] = d;
  }

  void resize(int n); // rehash, num_buckets at least n after resize
  int bucket_count() const { // Returns the number of buckets used by the hash
    return num_buckets;
  }
  int size() const { // Returns the size of the hash
    return the_size;
  }
  bool empty() const {
    return the_size == 0;
  }

  struct const_iterator;
    
  class iterator {
    friend class const_iterator;
    friend class open_addr_hash_timestamp;

    open_addr_hash_timestamp *h;
    int index;

    iterator(open_addr_hash_timestamp *h, int index):
      h(h), index(index) {}

  public:
    typedef KeyType         key_type;
    typedef DataType        data_type;
    typedef pair<const key_type, data_type> value_type;
    typedef value_type&     reference;
    typedef const reference const_reference;
    typedef value_type*     pointer;
    typedef ptrdiff_t       difference_type;
    typedef size_t          size_type;

    iterator(): h(0), index(0) {}
    iterator(const iterator &other):
      h(other.h), index(other.index) {}
    iterator& operator=(const iterator &other) {
      if (&other != this) {
	h     = other.h;
	index = other.index;
      }
      return *this;
    }

    iterator& operator++() { // preincrement
      // asumimos que no se incrementa un iterador con
      // index>=num_buckets
      do {
	index++;
      } while (index<h->num_buckets &&
	       h->buckets[index].stamp != h->current_stamp);
      return *this;
    }

    iterator operator++(int) { // postincrement
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    value_type& operator *() { //dereference
      return h->buckets[index].value;
    }

    value_type* operator ->() {
      return &(h->buckets[index].value);
    }

    bool operator == (const iterator &other) {
      return ((index == other.index) && (h == other.h));
    }

    bool operator != (const iterator &other) {
      return ((index != other.index) || (h != other.h));
    }

  };
      
  class const_iterator {
    friend class open_addr_hash_timestamp;

    const open_addr_hash_timestamp *h;
    int index;
        
    const_iterator(open_addr_hash_timestamp *h, int index):
      h(h), index(index) {}

  public:
    typedef KeyType         key_type;
    typedef DataType        data_type;
    typedef pair<key_type, data_type> value_type;
    typedef value_type&     reference;
    typedef const reference const_reference;
    typedef value_type*     pointer;
    typedef ptrdiff_t       difference_type;
    typedef size_t          size_type;

    const_iterator(): h(0), index(0) {}
        
    // Copy constructor (from iterator and const_iterator)
    const_iterator(const iterator &other):
      h(other.h), index(other.index) {}
    const_iterator(const const_iterator &other):
      h(other.h), index(other.index) {}

    // Assignment operators
    const_iterator& operator=(const iterator &other) {
      h     = other.h;
      index = other.index;
    }
    const_iterator& operator=(const const_iterator &other) {
      h     = other.h;
      index = other.index;
    }

    const_iterator& operator++() { // preincrement
      // asumimos que no se incrementa un iterador con
      // index>=num_buckets
      do {
	index++;
      } while (index<h->num_buckets &&
	       h->buckets[index].stamp != h->current_stamp);
      return *this;
    }

    const_iterator operator++(int) { // postincrement
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    const value_type& operator *() { //dereference
      return h->buckets[index].value;
    }

    const value_type* operator ->() {
      return &(h->buckets[index].value);
    }

    // Eq comparisons
    bool operator == (const iterator &other) {
      return ((index == other.index) && (h == other.h));
    }
    bool operator == (const const_iterator &other) {
      return ((index == other.index) && (h == other.h));
    }
    bool operator != (const iterator &other) {
      return ((index != other.index) || (h != other.h));
    }
    bool operator != (const const_iterator &other) {
      return ((index != other.index) || (h != other.h));
    }

  };

  iterator begin() {
    int i=0;
    while (i<num_buckets &&
	   buckets[i].stamp != current_stamp) i++;
    return iterator(this, i);
  }

private:
  iterator end_iterator;
    
public:
  iterator& end() { return end_iterator; }
      
};
 

template <typename ky, typename dt,
	  typename hfcn, typename eqky>
int open_addr_hash_timestamp<ky,dt,hfcn,eqky>::first_power_of_2(int value) {
  int result = 4; // ojito, minimo 4. TODO: se queda este valor?
  while (result < value)
    result += result;
  return result;
}
  
template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
open_addr_hash_timestamp<ky,dt,hfcn,eqky>::open_addr_hash_timestamp(int nbckts, float mxloadf) {
  num_buckets     = first_power_of_2(nbckts);
  hash_mask       = num_buckets-1; // num_buckets is a power of 2
  the_size        = 0;
  max_load_factor = (mxloadf <= 0.9) ? mxloadf : 0.9; // must be <1
  rehash_threshold= (int)ceilf(max_load_factor*num_buckets);
  end_iterator    = iterator(this, num_buckets);
  current_stamp   = 1;
  // buckets         = reinterpret_cast<node*>(new pair<ky,dt>[num_buckets]);
  buckets         = reinterpret_cast<node*>(new node[num_buckets]);
  for (int i=0; i<num_buckets; i++)
    buckets[i].stamp = 0;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
open_addr_hash_timestamp<ky,dt,hfcn,eqky>::open_addr_hash_timestamp(const open_addr_hash_timestamp& other) { // copy constructor
  num_buckets     = other.num_buckets;
  hash_mask       = other.hash_mask;
  the_size        = other.the_size;
  max_load_factor = other.max_load_factor;
  rehash_threshold= other.rehash_threshold;
  current_stamp   = other.current_stamp;
  buckets         = new node[num_buckets];
  for (int i=0; i<num_buckets; i++)
    buckets[i] = other.buckets[i];    
  end_iterator    = iterator(this, num_buckets);
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
void open_addr_hash_timestamp<ky,dt,hfcn,eqky>::clear() {
  // Erases all of the elements.
  if (current_stamp >= max_stamp) {
    for (int i=0; i<num_buckets; i++)
      buckets[i].stamp = 0;
    current_stamp = 1;
  } else {
    current_stamp++;
  }
  the_size = 0;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
open_addr_hash_timestamp<ky,dt,hfcn,eqky>& 
open_addr_hash_timestamp<ky,dt,hfcn,eqky>::operator=(const open_addr_hash_timestamp& other) {  // The assignment operator
  if (this != &other) {
    if (num_buckets != other.num_buckets) {
      delete[] buckets;
      num_buckets  = other.num_buckets;
      buckets      = new node[num_buckets];
    }
    hash_mask       = other.hash_mask;
    the_size        = other.the_size;
    max_load_factor = other.max_load_factor;
    rehash_threshold= other.rehash_threshold;
    current_stamp   = other.current_stamp;
    for (int i=0; i<num_buckets; i++)
      buckets[i] = other.buckets[i];
    end_iterator    = iterator(this, num_buckets);
  }
  return *this;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
open_addr_hash_timestamp<ky,dt,hfcn,eqky>::~open_addr_hash_timestamp() { // destructor
  delete[] buckets;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
dt* open_addr_hash_timestamp<ky,dt,hfcn,eqky>::find(const ky& k) {
  value_type* p = const_cast<value_type*>(find_pair(k));
  return p ? &(p->second) : 0;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
const pair<const ky,dt>* open_addr_hash_timestamp<ky,dt,hfcn,eqky>::find_pair(const ky& k) const {
  unsigned int hfval = hash_function(k);
  unsigned int index = hfval & hash_mask;
  unsigned int step  = (hfval >> 15) | 1; // debe ser impar
  while (buckets[index].stamp == current_stamp) {
    if (equal_key(buckets[index].value.first,k))
      return &(buckets[index].value);
    index = (index + step) & hash_mask;
  }
  return 0;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
dt& open_addr_hash_timestamp<ky,dt,hfcn,eqky>::operator[] (const ky& k) {
  unsigned int hfval = hash_function(k);
  unsigned int index = hfval & hash_mask;
  unsigned int step  = (hfval >> 15) | 1; // debe ser impar
  while (buckets[index].stamp == current_stamp) {
    if (equal_key(buckets[index].value.first,k))
      return buckets[index].value.second;
    index = (index + step) & hash_mask;
  }
  the_size++;
  if (the_size >= rehash_threshold) {
    resize(2*num_buckets);
    // recalcular index sabiendo que no esta, hfval ya lo tenemos
    index = hfval & hash_mask;
    step  = (hfval >> 15) | 1;
    while (buckets[index].stamp == current_stamp)
      index = (index + step) & hash_mask;
  }
  buckets[index].stamp       = current_stamp;
  *((ky *)(&buckets[index].value.first)) = k;
  buckets[index].value.second = dt();
  return buckets[index].value.second;
}

template <typename ky, typename dt, 
	  typename hfcn, typename eqky>
void open_addr_hash_timestamp<ky,dt,hfcn,eqky>::resize(int n) {
  n = first_power_of_2(n);
  if (n != num_buckets) {
    node *old_buckets = buckets;
    int old_num_buckets= num_buckets;
    int old_stamp      = current_stamp;
    num_buckets = n;
    end_iterator= iterator(this, num_buckets);
    hash_mask   = n-1;
    rehash_threshold= (int)ceilf(max_load_factor*num_buckets);
    buckets     = new node[num_buckets];
    for (int i=0; i<num_buckets; i++)
      buckets[i].stamp = 0;
    current_stamp = 1;
    for (int i=0; i<old_num_buckets; i++)
      if (old_buckets[i].stamp == old_stamp) {
	// insertamos sabiendo que no estaba
	unsigned int hfval = hash_function(old_buckets[i].value.first);
	unsigned int index = hfval & hash_mask;
	unsigned int step  = (hfval >> 15) | 1; // debe ser impar
	while (buckets[index].stamp == current_stamp) {
	  index = (index + step) & hash_mask;
	}
	buckets[index].stamp = current_stamp;
	*const_cast<ky*>(&buckets[index].value.first) = old_buckets[i].value.first;
	buckets[index].value.second = old_buckets[i].value.second;
	//buckets[index].value = old_buckets[i].value;
      }
    delete[] old_buckets;
  }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// clase grafo sencilla, lista de adyacencia
struct Grafo {
  // clase nodo del grafo
  struct Nodo {
    int   to;    // destino
    int   coste; // coste de la arista
    Nodo *sig;   // siguiente en lista enlazada
    Nodo(int to, int coste, Nodo *sig) : to(to), coste(coste), sig(sig) { }
  };
  // lista de adyacencia :)
  Nodo **lista_ady;
  // numero de vertices
  int    numv;
  
  Grafo(int numv) : numv(numv) {
    lista_ady = new Nodo*[numv];
    for (int i=0; i<numv; ++i) lista_ady[i] = 0;
  }
  ~Grafo() {
    for (int i=0; i<numv; ++i) {
      Nodo *aux = lista_ady[i];
      while(aux) {
	Nodo *del = aux;
	aux = aux->sig;
	delete del;
      }
    }
    delete[] lista_ady;
  }
  void addEdge(int from, int to, int coste) {
    lista_ady[from] = new Nodo(to, coste, lista_ady[from]);
  }
};

//programacion dinamica
open_addr_hash_timestamp<int,int,keyhash,keyeq> *current = new
  open_addr_hash_timestamp<int,int,keyhash,keyeq>();
open_addr_hash_timestamp<int,int,keyhash,keyeq> *next = new
  open_addr_hash_timestamp<int,int,keyhash,keyeq>();

int TouristGuide(Grafo &g, int S, int D, int T) {
  open_addr_hash_timestamp<int,int,keyhash,keyeq> *aux;  
  int max_viajeros = 0;
  open_addr_hash_timestamp<int,int,keyhash,keyeq>::iterator it;
  // estado activo inicial
  current->clear();
  (*current)[S] = T;
  // bucle sobre las etapas del grafo
  for ( int k = 0; k < g.numv; ++k ) {
    // bucle sobre los estados activos de la tabla actual
    for ( it = current->begin(); it != current->end(); ++it ) {
      // bucle sobre las aristas del vertice del estado activo
      for (Grafo::Nodo *a = g.lista_ady[it->first]; a != 0; a=a->sig) {
      	int &ref = (*next)[a->to];
	ref = max( min( a->coste - 1, it->second ), ref );
	// maximizamos sobre los caminos que llegan al vertice final
	if ( a->to == D ) max_viajeros = max( max_viajeros, ref );
      }
    }
    aux     = next;
    next    = current;
    current = aux;
    next->clear();
  }
  return int ( ceilf( float(T) / float(max_viajeros) ) ); 
}

int main(void)
{
  int N, R; //vertices y aristas
  int n_cases = 0;
  while ( cin >> N >> R ) {
    //condicion de parada
    if ( ( 0 == N ) && ( 0 == R ) ) break;
    // creamos el grafo para N vertices
    Grafo g(N);
    //leer aristas
    for ( int i = 0; i < R; ++i ) {
      int s, d, w;
      cin >> s >> d >> w;
      // OJO: comenzamos en 0
      g.addEdge(s-1, d-1, w);
      g.addEdge(d-1, s-1, w);
    }
    ///////////////
    //leer origen, destino y pasajeros
    int S, D, T;
    cin >> S >> D >> T;
    // OJO: comenzamos en 0
    int n_trips = TouristGuide(g,S-1,D-1,T);
    cout << "Scenario #" << ++n_cases << endl;
    cout << "Minimum Number of Trips = " << n_trips << endl << endl;
  }
  return 0;
}
