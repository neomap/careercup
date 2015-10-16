#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <cstring>
#include <sstream>
#include <algorithm>
#include <map>
#include <cassert>
#include <stddef.h> // ptrdiff_t, size_t...

using std::ostream;
using std::endl;
using std::swap;
using std::map;

#define mark_mask   0x80000000
#define unmark_mask 0x7FFFFFFF

template<typename T>
class DefaultCompare {
public:
  bool operator()(const T &a, const T &b) {
    return a < b;
  }
};


// Compare(a,b) is true if a is better than b (a < b)

// Fibonacci Heap implementado mediante un pool de punteros a
// nodos. Esto nos permite dos cosas, ser eficientes en memoria (el
// pool se reserva como un vector contiguo en memoria), y por otro
// lado nos permite anyadir una operacion mas al heap:
// contains(iterator). Esto permite saber si un iterador existe o no
// en el heap.
template<typename Data, typename Compare = DefaultCompare<Data> >
class FibonacciHeap {
private:

  /// A node contains a pointer to its parent (will be null if it is
  /// the root) a to one of its childrens
  class node_t {
    friend class FibonacciHeap;
    
    node_t *parent, *children, *next_sibling, *prev_sibling;
    Data    data;
    unsigned int mark_bit_and_rank, time;
    
  public:

    node_t() : parent(0), children(0),
	       next_sibling(this), prev_sibling(this),
	       data(Data()), mark_bit_and_rank(0), time(0) {
    }
    
    node_t(const Data &data) :
      parent(0), children(0),
      next_sibling(this), prev_sibling(this),
      data(data), mark_bit_and_rank(0), time(0) {
    }

    void init() {
      parent = children = next_sibling = prev_sibling = 0;
      mark_bit_and_rank = time = 0;
      data = Data();
    }
    
    void init(const Data &data, unsigned int time) {
      parent = children = 0;
      mark_bit_and_rank = 0;
      this->time   = time;
      next_sibling = this;
      prev_sibling = this;
      this->data   = data;
    }

    void mark() {
      mark_bit_and_rank |= mark_mask;
    }
    void unmark() {
      mark_bit_and_rank &= unmark_mask;
    }
    unsigned int getRank() const {
      return mark_bit_and_rank & unmark_mask;
    }
    void increaseRank() {
      ++mark_bit_and_rank;
    }
    void decreaseRank() {
      --mark_bit_and_rank;
    }
    bool isMarked() const {
      return (mark_bit_and_rank & mark_mask) != 0;
    }
    
    // libera un nodo de su padre
    void cut() {
      parent->decreaseRank();
      if (next_sibling == this) parent->children = 0;
      else {
	// hacemos que el hijo sea el hermano
	parent->children = next_sibling;
	// hacemos que el hermano siguiente apunte al anterior
	next_sibling->prev_sibling = prev_sibling;
	// hacemos que el hermano anterior apunte al siguiente
	prev_sibling->next_sibling = next_sibling;
      }
      // le quitamos el padre
      parent = 0;
      // lo hacemos hijo unico
      prev_sibling = next_sibling = this;
    }
    
    void addNewChild(node_t *new_child) {
      // comprobamos que es un hijo unico
      assert(new_child->next_sibling == new_child);
      assert(new_child->prev_sibling == new_child);
      // le apuntamos su padre
      new_child->parent = this;
      // lo metemos en la lista de hermanos
      if (children) children->addSibling(new_child);
      else {
	children = new_child;
	// incrementamos el rank
	increaseRank();
      }
    }
    
    void addSibling(node_t *node) {
      assert(node->prev_sibling == node);
      assert(node->next_sibling == node);
      node->parent = parent;
      if (parent == 0) node->unmark();
      else parent->increaseRank();
      node->prev_sibling         = this;
      node->next_sibling         = this->next_sibling;
      next_sibling->prev_sibling = node;
      next_sibling               = node;
    }

    void printDotTree(ostream &out) {
      assert(this != children);
      node_t *aux = children;
      if (!isMarked())
	out << "n" << (unsigned long)this << " [label=\"d=" << data << ", r=" << getRank() << "\"];" << endl;
      else
	out << "n" << (unsigned long)this << " [style=filled; fillcolor=gray; label=\"d=" << data << ", r=" << getRank() << "\"];" << endl;
      if (aux) {
	do {
	  out << "n" << (unsigned long)this << " -> " << "n" << (unsigned long)aux << ";" << endl;
	  aux->printDotTree(out);
	  aux = aux->next_sibling;
	} while(aux != children);
      }
    }

  };

  node_t **pool, *first_free;
  unsigned int pool_size, current_time;
  
  void createPool(unsigned int pool_size) {
    current_time    = 1;
    this->pool_size = pool_size;
    pool	    = new node_t*[pool_size];
    pool[0]	    = new node_t();
    for (unsigned int i=1; i<pool_size; ++i) {
      pool[i] = new node_t();
      pool[i-1]->next_sibling = pool[i];
    }
    pool[pool_size-1]->next_sibling = 0;
    first_free = pool[0];
  }
  
  node_t *getNode(const Data &data) {
    if (first_free == 0) {
      node_t **oldpool = pool;
      unsigned oldpool_size = pool_size;
      pool_size = pool_size << 1;
      pool      = new node_t*[pool_size];
      // copiamos los punteros viejos
      for (unsigned int i=0; i<oldpool_size; ++i) pool[i] = oldpool[i];
      // creamos toda la parte nueva
      pool[oldpool_size]   = new node_t();
      for (unsigned int i=oldpool_size+1; i<pool_size; ++i) {
	pool[i] = new node_t();
	pool[i-1]->next_sibling = pool[i];
      }
      pool[pool_size-1]->next_sibling = 0;
      first_free = pool[oldpool_size];
      delete[] oldpool;
    }
    node_t *new_node = first_free;
    first_free = first_free->next_sibling;
    // iniciamos a nodo valido
    new_node->init(data, current_time++);
    //std::cout << "new_node: " << new_node << " free: " << first_free << endl;
    return new_node;
  }
  
  void releaseNode(node_t *node) {
    //std::cout << "release " << node << " free: " << first_free << endl;
    // iniciamos a cero
    node->init();
    node->next_sibling = first_free;
    first_free = node;
  }
  

  /// The heap is a circular double linked list of roots, we use the
  /// pointer to the best node as a entry point to the list
  node_t *root;

  map<unsigned int, node_t*> ranks_vector;
  size_t          num_elements;
  Compare         compare;

  node_t *merge(node_t *h, node_t *new_node) {
    h->addSibling(new_node);
    if (compare(h->data, new_node->data)) return h;
    else return new_node;
  }

  node_t *link(node_t *h1, node_t *h2) {
    if (compare(h2->data, h1->data)) swap(h1, h2);
    // desmarcamos h2, el que pasa a ser hijo
    h2->unmark();
    
    // h1 es mejor que h2
    //node_t *h2_next = h2->next_sibling;
    //node_t *h2_prev = h2->prev_sibling;
    
    // anyadimos como hijo al nodo h2
    h2->prev_sibling->next_sibling = h2->next_sibling;
    h2->next_sibling->prev_sibling = h2->prev_sibling;
    h2->next_sibling = h2;
    h2->prev_sibling = h2;
    h1->addNewChild(h2);
    
    return h1;
  }
  

  void consolidateStep() {
    node_t *aux = root;
    // hacemos link de los roots que tengan el mismo rank, para
    // ello se usa un vector auxiliar donde se guardan los roots
    // por rank
    do {
      // mientras que haya colisiones, vamos haciendo links
      node_t *other;
      while((other = ranks_vector[aux->getRank()]) != 0 && other != aux) {
	unsigned int r  = other->getRank();
	aux             = link(aux, other);
	root            = aux; // para obligar a dar la vuelta
	ranks_vector.erase(r);
      }
      // metemos aux en su posicion del vector
      ranks_vector[aux->getRank()] = aux;
      aux = aux->next_sibling;
    } while(aux != root);
    // buscamos el menor root
    for (auto i=ranks_vector.begin(); i != ranks_vector.end(); ++i)
      if (compare(i->second->data, root->data)) root = i->second;
    ranks_vector.clear();
  }


public:

  class iterator {
    friend class FibonacciHeap;
    node_t *ptr;
    unsigned int time_mark;
    iterator(node_t *ptr) : ptr(ptr), time_mark(ptr->time) { }
  public:
    iterator() : ptr(0) { }
    Data &operator*()  { return ptr->data; }
    Data  operator*() const { return ptr->data; }
    Data *operator->() { return &(ptr->data); }
  };
  
  FibonacciHeap(Compare compare = Compare()) :
    root(0),
    num_elements(0), compare(compare) {
    createPool(256);
  }

  ~FibonacciHeap() {
    clear();
    for (unsigned int i=0; i<pool_size; ++i) delete pool[i];
    delete[] pool;
  }

  iterator push(Data data) {
    node_t *new_heap = getNode(data);
    if (root == 0) root = new_heap;
    else root = merge(root, new_heap);
    ++num_elements;
    return iterator(new_heap);
  }
  
  Data& top() {
    return root->data;
  }
 
  void pop() {
    node_t *best = root;
    // hacemos que root apunte al siguiente
    if (root->next_sibling == root) root = 0;
    else root = root->next_sibling;
    // eliminamos best, sacandolo fuera de la lista doblemente
    // enlazada
    best->prev_sibling->next_sibling = best->next_sibling;
    best->next_sibling->prev_sibling = best->prev_sibling;
    // anyadimos los hijos de best como nuevas raices
    node_t *new_trees = best->children;
    if (root) {
      // hacemos que los hijos del best sean hermanos de root
      if (new_trees) {
	node_t *aux = new_trees;
	do {
	  node_t *next = aux->next_sibling;
	  aux->next_sibling = aux->prev_sibling = aux;
	  root->addSibling(aux);
	  aux = next;
	} while(aux != new_trees);
      }
    }
    else {
      // en caso de que root sea nulo, hacemos que root =
      // new_trees y apuntamos los parents a 0
      node_t *aux = new_trees;
      if (aux) {
	do {
	  aux->parent = 0;
	  aux         = aux->next_sibling;
	} while(aux != new_trees);
      }
      root = new_trees;
    }
    if (root) {
      node_t *aux = root;
      // si tiene mas de un hermano, consolidamos
      if (aux && aux->prev_sibling != root) consolidateStep();
    }
    else root = 0;
    releaseNode(best);
    --num_elements;
  }

  /*
    Operation decrease key will take the node, decrease the key and if
    the heap property becomes violated (the new key is smaller than
    the key of the parent), the node is cut from its parent. If the
    parent is not a root, it is marked. If it has been marked already,
    it is cut as well and its parent is marked. We continue upwards
    until we reach either the root or an unmarked node. In the process
    we create some number, say k, of new trees. Each of these new
    trees except possibly the first one was marked originally but as a
    root it will become unmarked. One node can become
    marked. Therefore the potential decreases by at least k − 2. The
    actual time to perform the cutting was O(k), therefore the
    amortized running time is constant.
  */
  void improveKey(iterator it, Data new_data) {
    assert(compare(new_data, it.ptr->data));
    it.ptr->data = new_data;
    if (it.ptr->parent) {
      // comprobamos si se viola la propiedad del heap
      if (compare(it.ptr->data, it.ptr->parent->data)) {
	it.ptr->cut();
	root->addSibling(it.ptr);
	node_t *to_parent = it.ptr->parent;
	if (to_parent) {
	  while(to_parent->parent != 0 && to_parent->isMarked()) {
	    to_parent->cut();
	    root->addSibling(to_parent);
	    to_parent = to_parent->parent;
	  }
	  // si el padre no es una raiz, lo marcamos
	  if (to_parent->parent != 0) to_parent->mark();
	}
      }
    }
    // comprobamos si el valor nuevo pasa a ser el minimo
    if (compare(it.ptr->data, root->data)) root = it.ptr;
  }
  
  bool contains(iterator it) {
    return it.time_mark == it.ptr->time;
  }
  
  void del(iterator it) {
    // decreaseKey(it, BEST_POSIBLE_VALUE)
    if (it.ptr->parent) {
      // asumimos que viola la propiedad del heap
      it.ptr->cut();
      root->addSibling(it.ptr);
      node_t *to_parent = it.ptr->parent;
      if (to_parent) {
	while(to_parent->parent != 0 && to_parent->isMarked()) {
	  to_parent->cut();
	  root->addSibling(to_parent);
	  to_parent = to_parent->parent;
	}
	// si el padre no es una raiz, lo marcamos
	if (to_parent->parent != 0) to_parent->mark();
      }
    }
    // pasa a ser el minimo
    root = it.ptr;
    // lo quitamos con un pop estandar
    pop();
  }
  void clear() {
    num_elements = 0;
    root = 0;
    pool[0]->init();
    for (unsigned int i=1; i<pool_size; ++i) {
      pool[i]->init();
      pool[i-1]->next_sibling = pool[i];
    }
    pool[pool_size-1]->next_sibling = 0;
    current_time = 1;
  }
  size_t size() const {
    return num_elements;
  }
  bool empty() const {
    return root == 0;
  }
  void printDot(ostream &out) {
    out << "Digraph prueba {" << endl;
    node_t *aux = root;
    if (aux) {
      do {
	aux->printDotTree(out);
	aux = aux->next_sibling;
      } while(aux != root);
    }
    out << "}" << endl;
  }
};

#undef mark_mask
#undef unmark_mask

#endif
