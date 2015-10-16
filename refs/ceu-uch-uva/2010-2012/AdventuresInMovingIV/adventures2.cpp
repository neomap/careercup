#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <climits>
#include <algorithm>
#include <map>

using namespace std;


struct value {
  int v;
  value() : v(INT_MAX) {
  }
};

map<int,value> CURRENT, NEXT;
vector<int> distancias;
vector<int> precios;

int main()
{
	//Para rellenar los vectores
	int temp_distancia;
	int temp_precio;

	//Para obtener las variables de arriba
	string temp_linea;

	//Cargamos los casos
	int test_cases;
	cin >> test_cases;

	//Numero de km entre Waterloo hasta la gran ciudad
	int kilometers = 0;

	//Para cada caso de test
	for(int c = 0; c<test_cases; c++)
	{
		//Restricción de output de juez
		if(c>0)
			cout << endl;

		//Leemos la distancia de Waterloo a la gran ciudad
		cin >> kilometers;
		
		//Leemos el /n que queda
		getline(cin, temp_linea);
		distancias.push_back(0);
		precios.push_back(0);
		//Leemos las distancias a las gasolineras, y sus precios ahí
		//CUIDADO: Si el Juez nos lo echa para atrás, puede ser que haya metido estaciones más allá de la gran ciudad.
		while(getline(cin, temp_linea))
		{
			//Si hemos encontrado fin de estaciones, break
			if(temp_linea.size()==0)
				break;

			//Si no, volcamos la linea en el stringstream, y lo separamos en valores que metemos en los vectores.
			stringstream linea(temp_linea);
			linea >> temp_distancia >> temp_precio;
			distancias.push_back(int(temp_distancia));
			precios.push_back(int(temp_precio));

			temp_linea.clear();
		}

		//Si no hay gasolinera en la gran ciudad, la añadimos nosotros
		/*if(distancias[distancias.size()-1] != kilometers)
		{*/
			distancias.push_back(kilometers); //-distancias.size()-1);
			precios.push_back(INT_MAX);
		//}

			CURRENT[100].v = 0;
			for(unsigned int i = 1; i<distancias.size(); ++i) {
			  for (map<int,value>::iterator from = CURRENT.begin();
			       from != CURRENT.end(); ++from) {
			    int d   = distancias[i] - distancias[i-1];
			    int ini = max(0, from->first - d);
			    int max = 200;
			    for (int G=ini; G<=max; ++G) {
			      int gas = G - from->first + d;
			      if (gas == 0 || precios[i] != INT_MAX) {
				value &to_cost = NEXT[G];
				to_cost.v = min(to_cost.v, from->second.v + gas * precios[i]);
			      }
			    }
			  }
			  CURRENT.swap(NEXT);
			  NEXT.clear();
			}
			
			int best = INT_MAX;
			for (map<int,value>::iterator from = CURRENT.begin();
			     from != CURRENT.end(); ++from) {
			  if (from->first >= 100) {
			    best = min(best, from->second.v);
			  }
			}
			CURRENT.clear();
			
		if(best == INT_MAX)
			cout << "Impossible" << endl;
		else
			cout << best << endl;



		//Borramos vectores para siguiente caso de uso
		distancias.clear();
		precios.clear();
	}


	
	return 0;
}
