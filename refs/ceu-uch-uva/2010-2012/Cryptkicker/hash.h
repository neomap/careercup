#ifndef HASH_H
#define HASH_H

template <typename Key, typename Value, typename KeyHash, typename KeyEq>
class Hash {
public:
  
  struct pair_key_value_t {
    Key		key;
    Value	value;
    
    pair_key_value_t() { }
    
    pair_key_value_t(Key k, Value v) {
      key   = k;
      value = v;
    }
  };
  
private:
  
  struct node_t {
    pair_key_value_t	 data;
    node_t		*next;	// lista enlazada
    
    node_t() { next=0; }
    node_t(pair_key_value_t d, node_t *n) {
      data = d;
      next = n;
    }
  };
  
  int max_size;
  int size;
  
  node_t **V; // vector de listas enlazadas
  
  KeyHash hash_key;
  KeyEq   equal_key;
  
public:

  class iterator {
    Hash<Key, Value, KeyHash, KeyEq>	*h;
    node_t		*node;
    int			 bucket;
    iterator(Hash<Key, Value, KeyHash, KeyEq> *h, node_t *node, int bucket) {
      this->h	   = h;
      this->node   = node;
      this->bucket = bucket;
    }
  public:
    Value getValue() { return node->data.value; }
    Key   getKey()   { return node->data.key; }
    iterator &operator++() {
      if (node) node = node->next;
      if (node) return *this;
      while (node == 0 && (++bucket) < h->max_size) node = h->V[bucket];
      return *this;
    }
    
    friend bool operator!=(const iterator &it1, const iterator &it2) {
      
      if (it1.h	     != it2.h		||
	  it1.node   != it2.node	||
	  it1.bucket != it2.bucket) return true;
      
      return false;
    }
    
    pair_key_value_t *operator->() {
      return &node->data;
    }

    friend class Hash;
  };
  
  iterator begin() {
    int i;
    for (i=0; V[i] == 0 && i < max_size; ++i);
    if (i == max_size) return iterator(this, 0, max_size);
    return iterator(this, V[i], i);
  }
  iterator end() {
    return iterator(this, 0, max_size);
  }
  
  Hash(int max_size) {
    this->max_size = max_size;
    V              = new node_t*[max_size];
    size           = 0;
    for (int i=0; i<max_size; ++i) V[i] = 0;
  }
  
  ~Hash() {
    for (int i=0; i<max_size; ++i) if (V[i]) delete V[i];
    delete[] V;
  }
  
  void insert(Key &k, Value &v) {
    
    unsigned long int	h      = hash_key(k);
    int			bucket = h % max_size;
    
    node_t *aux = V[bucket];
    while(aux != 0 && !equal_key(aux->data.key, k)) aux = aux->next;
    
    if (!aux) {
      aux	= new node_t(pair_key_value_t(k, v), V[bucket]);
      V[bucket] = aux;
      ++size;
    }
    else aux->data.value = v;
    
  }
  
  Value *search(const Key &k) {
    unsigned long int	h      = hash_key(k);
    int			bucket = h % max_size;
    
    node_t *aux = V[bucket];
    while(aux != 0 && !equal_key(aux->data.key, k)) aux = aux->next;
    
    if (!aux) return 0;
    return &(aux->data.value);
  }
  
  Value &operator[](const Key &k) {
    unsigned long int	h      = hash_key(k);
    int			bucket = h % max_size;
    
    node_t *aux = V[bucket];
    while(aux != 0 && !equal_key(aux->data.key, k)) aux = aux->next;
    
    if (!aux) {
      aux	= new node_t(pair_key_value_t(k, Value()), V[bucket]);
      V[bucket] = aux;
      ++size;
    }
    return aux->data.value;
  }
};

#endif // HASH_H
