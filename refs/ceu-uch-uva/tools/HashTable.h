#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <utility>
#include <algorithm>
#include <list>

using std::make_pair;
using std::list;
using std::pair;
using std::find;

// KeyType necesita tener implementado el operador==
template<typename KeyType, typename ValueType,
	 typename KeyHashFunctor>
class HashTable {
  typedef pair<KeyType,ValueType> HashTableNode;
  typedef typename list<HashTableNode>::iterator NodeInList;
  list< HashTableNode > *buckets;
  unsigned int number_of_buckets, number_of_elements;
  KeyHashFunctor  key_hash_func;
  
  struct KeyFinder {
    const KeyType key;
    KeyFinder(const KeyType &key) : key(key) { }
    bool operator()(const HashTableNode &other) const {
      return other.first == key;
    }
  };
  
  NodeInList findPairUsingKey(const KeyType &k, unsigned long int &p) {
    p = key_hash_func(k) % number_of_buckets;
    return find_if(buckets[p].begin(), buckets[p].end(), KeyFinder(k));
  }

public:
  class iterator {
    friend class HashTable;
    HashTable     *table;
    unsigned int   current_bucket;
    NodeInList     node;
    iterator(HashTable *table, unsigned int current_bucket, NodeInList node) :
      table(table), current_bucket(current_bucket), node(node) { }
  public:
    iterator() : table(0), node(0) { }
    iterator &operator=(const iterator &other) {
      table = other.table; current_bucket = other.current_bucket;
      node = other.node; return *this;
    }
    bool operator==(const iterator &other) {
      return(table==other.table &&
	     current_bucket==other.current_bucket &&
	     node==other.node);
    }
    bool operator!=(const iterator &other) { return !(*this == other); }
    std::pair<KeyType,ValueType> &operator*() { return *node; }
    std::pair<KeyType,ValueType> *operator->() { return &(*node); }
    void toNextElement() {
      ++node;
      if (node == table->buckets[current_bucket].end()) {
	++current_bucket;
	while(current_bucket < table->number_of_buckets &&
	      table->buckets[current_bucket].begin() == table->buckets[current_bucket].end())
	  ++current_bucket;
	if (current_bucket == table->number_of_buckets) *this = table->end();
	else node = table->buckets[current_bucket].begin();
      }
    }
    iterator &operator++() { this->toNextElement(); return *this; }
  };
  HashTable(unsigned int n) : number_of_buckets(n), number_of_elements(0) {
    buckets = new list<HashTableNode>[number_of_buckets];
  }
  ~HashTable() { delete[] buckets; }
  iterator search(const KeyType &k) {
    unsigned long int p;
    NodeInList find_iter = findPairUsingKey(k, p);
    if (find_iter != buckets[p].end()) return iterator(this, p, find_iter);
    else return end();
  }
  
  void insert(const KeyType &k, const ValueType &v) {
    unsigned long int p;
    NodeInList find_iter = findPairUsingKey(k, p);
    HashTableNode node   = make_pair(k,v);
    if (find_iter != buckets[p].end()) find_iter->second = v;
    else {
      buckets[p].push_front(node);
      ++number_of_elements;
    }
  }
  
  void erase(iterator it) {
    buckets[it.current_bucket].erase(it.node);
    --number_of_elements;
  }
  
  iterator begin()   {
    if (number_of_elements == 0) return end();
    else {
      unsigned int i;
      int current_bucket = 0;
      for (i=0; (i<number_of_buckets &&
		 buckets[i].begin() == buckets[i].end()); ++i);
      return iterator(this, i, buckets[i].begin());
    }
  }

  iterator end() { return iterator(this, number_of_buckets,
				   buckets[number_of_buckets-1].end()); }
};
#endif // HASHTABLE_H
