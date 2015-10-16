#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <climits>
#include <algorithm>

using namespace std;


struct estado
{
	int i;
	int gasoil;

	estado(int I, int Gasoil)
	{
		this->i 	= I;
		this->gasoil 	= Gasoil;
	}
};

int** matriz_costes;
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

		//Creamos la matriz de costes
		matriz_costes = new int*[distancias.size()];
		for(unsigned int i = 0; i<distancias.size(); ++i)
			matriz_costes[i] = new int[201];


		//Inicialización
		for(int i = 0; i<=200; ++i)
			matriz_costes[0][i] = INT_MAX;
		
		matriz_costes[0][100] = 0;
		

		for(unsigned int i = 1; i<distancias.size(); ++i)
			for(int G = 0; G<=200; ++G)
			{
				int ini = distancias[i]-distancias[i-1];
				int fin = min(200, G+ ini);
				int mejor = INT_MAX;
				for(int U = ini; U<=fin; ++U)
				{	
					if(matriz_costes[i-1][U] != INT_MAX)
					{
						int gas = G - U + ini;
						if (gas == 0 || precios[i] != INT_MAX) {
						int valor_actual = matriz_costes[i-1][U] + precios[i]*(G-U+ini);
						if(valor_actual < mejor)
							mejor = valor_actual;
						}
					}
				}
				matriz_costes[i][G] = mejor;
			}

		int best = INT_MAX;
		for(int i = 100; i<=200; ++i)
			if(matriz_costes[distancias.size()-1][i] < best && matriz_costes[distancias.size()-1][i] >= 0)
			   best = matriz_costes[distancias.size()-1][i];
		
		if(best == INT_MAX)
			cout << "Impossible" << endl;
		else
			cout << best << endl;

/*		for(int j = 0; j<=200; ++j)
		{
			for(int i = 0; i<=distancias.size()-1; ++i)
				cout << matriz_costes[i][j] << " ";
			cout << endl;
		}*/

		//Liberamos memoria de la matriz
		for(unsigned int i = 0; i<distancias.size(); ++i)
			delete[](matriz_costes[i]);

		//Borramos vectores para siguiente caso de uso
		distancias.clear();
		precios.clear();
	}


	
	return 0;
}
