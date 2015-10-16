#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <algorithm>
#include <vector>

using std::vector;
using std::swap;

// Por defecto es un MinHeap
#define compute_parent(x) ((x)/2)
#define compute_left(x)   ((x)*2)
#define compute_right(x)  ((x)*2 + 1)
template<typename KeyType>
class BinaryHeap {
  vector<KeyType> tree;
  int n;
  void privateBubbleUp(int p) {
    if (p == 1) return;
    int parent = compute_parent(p);
    if (tree[p] < tree[parent]) {
      swap(tree[p], tree[parent]);
      privateBubbleUp(parent);
    }
  }
  void privateHeapify(int parent) {
    int child = compute_left(parent);
    if (child <= n) {
      if (child+1 <= n && tree[child+1] < tree[child]) child++;
      if (tree[child] < tree[parent]) {
        swap(tree[parent], tree[child]);
        privateHeapify(child);
      }
    }
  }
  void privateIterativeHeapify(int p) {
    int child;
    KeyType tmp = tree[p];
    // mientras que el hijo_izq no se salga del heap...
    while (compute_left(p) <= n) {
      // En este bucle haremos que uno de los dos hijos (el que sea
      // menor) pase a la posicion de su padre, siempre que el padre sea
      // mayor que alguno de sus hijos.
      child = compute_left(p);
      // Si el hijo derecho tampoco se sale del heap y ademas es menor
      // que el hijo izquierdo, lo tomamos como hijo predilecto
      if (child+1 <= n && tree[child+1] < tree[child])
        child++; // el hijo derecho
      // si el padre es mayor que el hijo
      if (tree[child] < tmp)
        // ponemos al hijo en la posicion del padre
        tree[p] = tree[child];
      else
        // en otro caso, el padre es mayor que el hijo y ya hemos
        // terminado de hundir al padre
        break;
      // cambiamos pos por la posicion del hijo predilecto (equivale a
      // mover el padre a la posicion de su hijo)
      p = child;
    }
    // situamos al padre en su posicion destino
    tree[ p ] = tmp;
  }
  
public:
  // Reservamos la posicion 0 para que el heap empiece siempre en 1
  BinaryHeap() : n(0) { tree.push_back(0); }
  ~BinaryHeap() { }
  void push(const KeyType &k) {
    ++n;
    if (tree.size() < n+1) tree.push_back(k);
    else tree[n] = k;
    privateBubbleUp(n);
  }
  int size() const { return n; }
  bool empty() const { return size() == 0; }
  // Devuelve maximo o minimo (depende de la funcion de
  // orden, operator<)
  KeyType &top() { return tree[1]; }
  KeyType pop() {
    KeyType aux = tree[1];
    tree[1] = tree[n];
    --n;
    privateHeapify(1);
    //privateIterativeHeapify(1);
  }
  void buildHeap(const vector<KeyType> &elements) {
    n = static_cast<int>(elements.size());
    tree.clear(); tree.push_back(0);
    for (int i=0; i<n; ++i) tree.push_back(elements[i]);
    for (int i=n/2; i>=1; --i) privateHeapify(i);
  }
  void heapSort(vector<KeyType> &v, bool invert) {
    buildHeap(v);
    for (int i=n; i>=1; --i) {
      swap(tree[1],tree[i]);
      --n;
      privateHeapify(1);
    }
    int sz = static_cast<int>(v.size());
    for (int i=0; i<sz; ++i) {
      if (!invert) v[i] = tree[i+1];
      else v[i] = tree[sz - i];
    }
  }
};
#undef compute_parent
#undef compute_left
#undef compute_right

#endif // BINARYHEAP_H
