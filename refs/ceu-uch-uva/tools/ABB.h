#include <cassert>
#include <cstdlib>
#include <utility>

template<typename KeyType, typename ValueType>
class ABB {
  class ABBNode {
    friend class ABB;
    std::pair<KeyType, ValueType> data;
    ABBNode *parent;       // este atributo es opcional
    ABBNode *left, *right; // hijo izquierdo y derecho
  public:
    ABBNode(const KeyType &k, const ValueType v) :
      data(std::pair<KeyType,ValueType>(k,v)), parent(0), left(0), right(0) { }
    bool isRightChild() const { return parent->right == this; }
  };
  ABBNode *privateSearch(ABBNode *node, const KeyType &k)  {
    if (node == NULL) return NULL;
    if (k == node->data.first) return node;
    if (k < node->data.first) return privateSearch(node->left, k);
    else return privateSearch(node->right, k);
  }
  ABBNode *privateMaximum(ABBNode *node) {
    if (node != NULL)
      while(node->right != NULL)
	node = node->right;
    return node;
  }
  ABBNode *privateMinimum(ABBNode *node) {
    if (node != NULL)
      while(node->left != NULL)
	node = node->left;
    return node;
  }
  ABBNode *privateSearchSucessor(ABBNode *node) {
    assert(node != NULL);
    ABBNode *succ;
    if (node->right) succ = privateMinimum(node->right);
    else {
      succ=node;
      while(succ->parent && succ->parent->right == succ) succ = succ->parent;
      succ = succ->parent;
    }
    return succ;
  }
  ABBNode *privateSearchPredecessor(ABBNode *node) {
    assert(node != NULL);
    ABBNode *pred;
    if (node->left) pred = privateMaximum(node->left);
    else {
      pred=node;
      while(pred->parent && pred->parent->left == pred) pred = pred->parent;
      pred = pred->parent;
    }
    return pred;
  }
  void *privateFreeNode(ABBNode *node) {
    if (node) {
      privateFreeNode(node->left);
      privateFreeNode(node->right);
      delete node;
    }
  }
  void privateErase(ABBNode *node) {
    assert(node != NULL);
    bool is_root = (node == root);
    // caso (a) es un nodo hoja
    if (node->left == NULL && node->right == NULL) {
      if (is_root) root = NULL;
      else {
	if (node->isRightChild()) node->parent->right = NULL;
	else node->parent->left = NULL;
      }
    }
    // caso (b.1)
    else if (node->left == NULL) {
      if (is_root) root = node->right;
      else if (node->isRightChild()) node->parent->right = node->right;
      else node->parent->left = node->right;
      node->right->parent = node->parent;
    }
    // caso (b.2)
    else if (node->right == NULL) {
      if (is_root) root = node->left;
      else if (node->isRightChild()) node->parent->right = node->left;
      else node->parent->left = node->left;
      node->left->parent = node->parent;
    }
    else {
      // caso (c)
      ABBNode *succ = privateSearchSucessor(node);
      node->data = succ->data;
      privateErase(succ);
      node = 0; // para evitar el delete
    }
    delete node;
  }
  ABBNode *root; // raiz del arbol
public:
  // la clase iteradora nos permitira movernos por el arbol
  class iterator {
    friend class ABB;
    ABB     *tree;
    ABBNode *node;
    iterator(ABB *tree, ABBNode *node) : tree(tree), node(node) { }
  public:
    iterator() : tree(0), node(0) { }
    iterator &operator=(const iterator &other) {
      tree = other.tree;
      node = other.node;
      return *this;
    }
    bool operator==(const iterator &other) {
      return tree == other.tree && node == other.node;
    }
    bool operator!=(const iterator &other) {
      return !(*this == other);
    }
    std::pair<KeyType,ValueType> &operator*() { return node->data; }
    std::pair<KeyType,ValueType> *operator->() { return &node->data; }
    void toParent()     { node = node->parent; }
    void toLeftChild()  { node = node->left;   }
    void toRightChild() { node = node->right;  }
    void toNextKey()    { node = tree->privateSearchSucessor(node); }
    void toPrevKey()    { node = tree->privateSearchPredecessor(node); }
    iterator &operator++() {
      this->toNextKey();
      return *this;
    }
    iterator &operator--() {
      this->toPrevKey();
      return *this;
    }
  };
  ABB() : root(0) { }
  ~ABB() { privateFreeNode(root); }
  iterator search(const KeyType &k) {
    return iterator(this, privateSearch(root, k));
  }
  void insert(const KeyType &k, const ValueType &v) {
    ABBNode *item = new ABBNode(k, v);
    if (root == NULL) root = item;
    else {
      ABBNode *parent = NULL, **pos = &root;
      while(*pos) {
	parent = *pos;
	if (k < (*pos)->data.first) pos = &( (*pos)->left );
	else if (k > (*pos)->data.first) pos = &( (*pos)->right );
	else { (*pos)->data = item->data; delete item; return; }
      }
      *pos = item;
      item->parent = parent;
    }
  }
  void erase(iterator &it) {
    privateErase(it.node);
    it = end();
  }
  iterator searchSucessor(const iterator &it) {
    return privateSearchSucessor(it.node);
  }
  iterator searchPredecessor(const iterator &it) {
    return privateSearchPredecessor(it.node);
  }
  iterator maximum() {
    return iterator(this, privateMaximum(root));
  }
  iterator minimum() {
    return iterator(this, privateMinimum(root));
  }
  iterator getRoot() { return iterator(this,root); }
  iterator begin()   { return minimum(); }
  iterator end()     { return iterator(this, NULL); }
};
