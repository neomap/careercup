// PROBLEM ID 10261
#include <map>
using std::map;
using std::iterator;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <stack>
using std::stack;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;

struct clave {
  clave(int x, int y) {
    izq = x;
    der = y;
  }

  int izq;
  int der;

  bool operator!=(const clave &other) const {
    return (izq!=other.izq || der!=other.der);
  }
  
  bool operator==(const clave &other) const {
    return (izq==other.izq && der==other.der);
  }
  
  bool operator<(const clave &other) const {
    if(izq < other.izq) return true;
    else if(izq > other.izq) return false;
    else return (der < other.der);
  }

};

struct valor {
  string lado;
  map<clave,valor>::iterator padre;
};

void sacar_camino(int num, map<clave,valor>::iterator it);
void mostrarCamino();
void mostrarTablaHash(int num);

vector<map<clave,valor> *> maps_for_num_cars;
map<clave,valor> nullMap;

stack<string> camino;

//ifstream fin;

int main(int argc, char* argv[]) {
  //empieza caso de prueba

  int N; //casos de prueba
  int longitud; //longitud del barco
	
  //  cin.open(argv[1]);
  cin >> N;

  clave cinicial(0,0);
  valor vinicial;
  
  maps_for_num_cars.push_back(new map<clave,valor>());
  (*maps_for_num_cars[0])[cinicial]       = vinicial;
  (*maps_for_num_cars[0])[cinicial].padre = nullMap.end();
  
  for(int c=0; c<N; ++c) {
    if(c > 0) cout << endl;

    //while(!camino.clear();

    cin >> longitud;
    longitud *= 100;


    int num = 0;
    int coche;
	
    bool puedo;
    do {
      ++num;
      if (num >= int(maps_for_num_cars.size()))
	maps_for_num_cars.push_back(new map<clave,valor>());
      maps_for_num_cars[num]->clear();
      cin >> coche;

      puedo = false;
	
      if(coche == 0) break;
	
      map<clave,valor>::iterator it;
	
      for(it = maps_for_num_cars[num -1]->begin();
	  it != maps_for_num_cars[num -1]->end(); ++it) {

	if(it->first.izq + coche <= longitud) {
	  clave aux1(it->first.der, it->first.izq + coche);
	  clave aux2(it->first.izq + coche,it->first.der);

	  if(maps_for_num_cars[num]->find(aux1) == maps_for_num_cars[num]->end() &&
	     maps_for_num_cars[num]->find(aux2) == maps_for_num_cars[num]->end()) {
	    (*maps_for_num_cars[num])[aux2].padre = it;
	    (*maps_for_num_cars[num])[aux2].lado = "port";
	    puedo = true;
	  }
	}
	
	if(it->first.der + coche <= longitud) {
	  clave aux1(it->first.der + coche, it->first.izq);
	  clave aux2(it->first.izq, it->first.der + coche);

	  if(maps_for_num_cars[num]->find(aux1) == maps_for_num_cars[num]->end() &&
	     maps_for_num_cars[num]->find(aux2) == maps_for_num_cars[num]->end()) {
	    (*maps_for_num_cars[num])[aux2].padre = it;
	    (*maps_for_num_cars[num])[aux2].lado = "starboard";
	    puedo = true;
	  }
	}
	
      }
    } while(puedo);
	
    while(coche != 0) cin >> coche; //procesar coches restantes del caso de prueba actual
	
    sacar_camino(num, maps_for_num_cars[num-1]->begin());
    mostrarCamino();
    //mostrarTablaHash(num);
		
  } //for(int c=0; c<N; ++c)

  for (unsigned int i=0; i<maps_for_num_cars.size(); ++i)
    delete maps_for_num_cars[i];

  return 0;

} //int main(void)

void sacar_camino(int num, map<clave,valor>::iterator it) {
  cout << num-1 << endl;
  clave inicial(0,0);

  while(it->second.padre != nullMap.end())  {
    camino.push(it->second.lado);
    it = it->second.padre;
  }

  //camino.push(it->second.lado);
}

void mostrarCamino() {
  while(!camino.empty()) {
    cout << camino.top() << endl;
    camino.pop();
  }
}

void mostrarTablaHash(int num) {
  map<clave,valor>::iterator it;


  for(int i = 0; i < num; ++i) {

    cout << i << endl;

    for(it= maps_for_num_cars[i]->begin(); it != maps_for_num_cars[i]->end(); ++it) {
      cout << "(" << it->first.izq << "," << it->first.der << ") => ";
      cout << it->second.lado << ", (" << it->second.padre->first.izq << "," << it->second.padre->first.der << ")" << endl;
    }
  }

}
