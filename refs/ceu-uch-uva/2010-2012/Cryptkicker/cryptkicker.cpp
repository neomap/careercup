#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

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
    for (int i=0; i<max_size; ++i) {
      while(V[i]) {
	node_t *aux = V[i];
	V[i] = V[i]->next;
	delete aux;
      }
    }
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





/**************************************************************************/




#define MAXLINE    2000
#define WLEN         50
#define NUMLETTERS  256
#define FIRSTLETTER   0

using namespace std;

char char_map[NUMLETTERS];
bool inv_map[NUMLETTERS];

void set_map(char a, char b) {
  char_map[a - FIRSTLETTER] = b;
  inv_map[b - FIRSTLETTER]  = true;
}

void unset_map(char a) {
  inv_map[char_map[a - FIRSTLETTER] - FIRSTLETTER] = false;
  char_map[a - FIRSTLETTER]			   = '?';
}

bool get_inv_map(char a) {
  return inv_map[a - FIRSTLETTER];
}

char get_map(char a) {
  return char_map[a - FIRSTLETTER];
}

void print_map() {
  for (int i=0; i<30; ++i)
    cout << char_map[i];
  cout << endl;
}

void print_decrypted_word(string word) {
  for (int i=0; i<word.size(); ++i)
    cout << get_map(word[i]);
}

void Tokenize(const string& str,
	      vector<string>& tokens,
	      const string& delimiters = " ")
{
  // Skip delimiters at beginning.
  string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  string::size_type pos     = str.find_first_of(delimiters, lastPos);
  
  while (string::npos != pos || string::npos != lastPos)
    {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      // Skip delimiters.  Note the "not_of"
      lastPos = str.find_first_not_of(delimiters, pos);
      // Find next "non-delimiter"
      pos = str.find_first_of(delimiters, lastPos);
    }
}

// struct para representar la clave que nos serve para identificar las
// palabras del vocabulario
struct voc_key {
  int size;
  int code[WLEN];
  voc_key() {
    size = 0;
  }
  voc_key(int *cod, int s) {
    for (int i=0; i<s; ++i) code[i] = cod[i];
    size = s;
  }
  voc_key(string word) {
    map<char, int> letters;
    size = word.size();
    for (int i=0; i<word.size(); ++i) {
      int &pos = letters[word[i]];
      if (pos == 0) pos = i+1;
      code[i] = pos - 1;
    }
  }
  void print() const {
    cout << size;
    for (int i=0; i<size; ++i) cout << " " << code[i];
  }
  friend bool operator==(const voc_key& k1, const voc_key& k2) {
    if (k1.size != k2.size) return false;
    for(int i=0; i<k1.size; i++)
      if (k1.code[i] != k2.code[i]) return false;
    return true;
  }
};

// para comparar claves
struct voc_key_eq
{
  bool operator()(const voc_key& k1, const voc_key& k2)
  {
    return k1 == k2;
  }
};

// para sacar el hash
struct voc_key_hash
{
  unsigned long int operator()(const voc_key& k) const
  {
    static unsigned long int cte_hash= 2654435769U;
    unsigned long int h = 0;
    for(int i=0; i<k.size; i++)
      h = (h + k.code[i])*cte_hash;
    return h;
  }
};


// para cada clave guardamos una lista de palabras
typedef vector<string> voc_value;

typedef Hash<voc_key,voc_value,voc_key_hash,voc_key_eq> VocHash;

struct input_word {
  vector<string>	*voc_words;
  string		 word;
  int                    pos;
  
  input_word(VocHash &voc, string word, int pos) :
    voc_words(&voc[voc_key(word)]), word(word), pos(pos) {
  }
  
  char	operator[](int i) const { return word[i]; }
  int	size() const      { return word.size(); }

  void print() const {
    cout << " " << word << " ";
    print_decrypted_word(word);
    cout << endl;
  }

  friend bool operator==(const input_word &k1, const input_word &k2) {
    return k1.word == k2.word;
  }

  friend bool operator<(const input_word &k1, const input_word &k2) {
    return k1.word.size() > k2.word.size();
  }
  
};


/** busca hipotesis **/
void search_hyp(const input_word &w, vector<string> &h) {
  const vector<string> *voc_words = w.voc_words;
  for (int j=0; j<voc_words->size(); ++j) {
    bool ok = true;
    for (int i=0; i<w.size() && ok; ++i) {
      if (get_map(w[i])!='?' && get_map(w[i])!=(*voc_words)[j][i]) ok = false; 
      if (get_map(w[i])=='?' && get_inv_map((*voc_words)[j][i]))   ok = false;
    }
    if (ok) h.push_back((*voc_words)[j]);
    //cout << ok << " " << voc_words[j] << " " << w.word << endl;
  }
}

void print_solution(vector<input_word> &input_words) {
  vector<string> sol(input_words.size());
  for (int i=0; i<input_words.size(); ++i)
    sol[input_words[i].pos] = input_words[i].word;
  for (int i=0; i<sol.size(); ++i) {
    if (i>0) cout << " ";
    print_decrypted_word(sol[i]);
  }
  cout << endl;
}



/*******************************************************************/



/** METODO PRINCIPAL **/
bool cryptkicker(VocHash &voc, vector<input_word> &input_words,
		 int current_word) {
  
  if (current_word == input_words.size()) {
    /** es una solucion **/
    print_solution(input_words);
    return true;
  }
  
  /** conjunto de posibles hipotesis **/
  vector<string> h;
  search_hyp(input_words[current_word], h);
  
  for (int i=0; i<h.size(); ++i) {
    vector<char> char_map_update;
    bool ok = true;
    /** modificamos el char_map, pasar al estado nuevo **/
    for (int j=0; j<h[i].size() && ok; ++j) {
      if (get_map(input_words[current_word][j]) == '?') {
	char_map_update.push_back(input_words[current_word][j]);
	set_map(input_words[current_word][j], h[i][j]);
      }
    }
    
    /* llamada recursiva, desciende en profundidad por el arbol de
       soluciones */
    if (ok) if (cryptkicker(voc, input_words, current_word+1)) return true;
    
    /** modificamos el char_map, restaurar el estado anterior **/
    for (int j=0; j<char_map_update.size(); ++j)
      unset_map(char_map_update[j]);
  }
  
  return false;
}

int main()
{
  // tabla hash, map en este caso :S
  VocHash voc(4096);
  
  int voc_size;
  cin >> voc_size;
  for (int i=0; i<voc_size; ++i) {
    string word;
    cin >> word;
    voc[voc_key(word)].push_back(word);
  }

  /** DEBUG DEL VOCABULARIO **/
  /*
    for (VocHash::iterator it = voc.begin(); it != voc.end(); ++it) {
    it->key.print();
    for (int i=0; i<it->value.size(); ++i)
    cout << " " << it->value[i];
    cout << endl;
    }
  */
  
  char line[MAXLINE];
  cin.getline(line, MAXLINE-1);
  while(!cin.eof()) {
    cin.getline(line, MAXLINE-1);
    
    if (strlen(line) > 0) {
      vector<input_word> input_words;
      
      vector<string> words;
      Tokenize(string(line), words, " ");
      for (int i=0; i<words.size(); ++i)
	input_words.push_back(input_word(voc, words[i], i));
      
      for (int i=0; i<NUMLETTERS; ++i) {
	char_map[i] = '?';
	inv_map[i]  = false;
      }
      
      sort (input_words.begin(), input_words.end());

      /** llamamos al procedimiento que resuelve el problema **/
      if (!cryptkicker(voc, input_words, 0)) {
	/* si llegamos aqui es porque no ha encontrado solucion */
	vector<string> sol(input_words.size());
	for (int i=0; i<input_words.size(); ++i)
	  sol[input_words[i].pos] = input_words[i].word;
	for (int i=0; i<sol.size(); ++i) {
	  if (i > 0) cout << " ";
	  for (int j=0; j<sol[i].size(); ++j)
	    cout << "*";
	}
	cout << endl;
      }
    } else if (!cin.eof()) cout << endl;
  }
  
  return 0;
}
