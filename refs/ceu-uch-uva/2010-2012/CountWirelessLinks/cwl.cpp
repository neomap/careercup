#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <list>
using std::list;
using std::iterator;

#include <vector>
using std::vector;

#include <cmath>

struct point
{
  int x;
  int y;
};

int calcular_casilla( const point p, const int num_cols_grid, const int grid_cell_width, point &grid_cell);

void casillas_adyacentes( const point current_grid_cell, int num_cols_grid, int num_rows_grid,
								  const map< int, list<point> > &points,
								  int grid_cell_width, int R, vector<int> &p_adyacentes );

float distancia_euclidea( const point p1, const point p2 );

int max(int L,int H)
{
  if ( L > H )
	 return L;
  else
	 return H;
}

int main(void)
{
  int L, H, R, N;
  int grid_cell_width;
  int casilla;
  point p;
  float dist;
  int links;
  point current_grid_cell;
  

  while ( cin >> L )
  {
	 map< int, list<point> > points;
	 
	 cin >> H >> R >> N;

	 //decidir el tamanyo de las casillas
	 if ( (L > 500) || (H > 500) )
		grid_cell_width = 500;
	 else
		grid_cell_width = max(L,H);

	 //dividir el area total en casillas de tamanyo 'div'
	 float L_div = L / grid_cell_width;
	 float H_div = L / grid_cell_width;

	 int num_cols_grid = ceil(L_div); //numero de casillas a lo ancho
	 int num_rows_grid = ceil(H_div); //numero de casillas a lo alto
	 
	 int num_cells = num_cols_grid * num_rows_grid; //numero total de casillas

	 links = 0; //inicializar el numero de links
	 
	 for ( int i = 0; i < N; ++i ) //vamos a leer 'N' puntos
	 {
		cin >> p.x >> p.y; //leemos un punto

		casilla = calcular_casilla( p, num_cols_grid, grid_cell_width, current_grid_cell ); //calcular en que casilla cae

		vector<int> p_adyacentes;
		
		casillas_adyacentes( current_grid_cell, num_cols_grid, num_rows_grid, points, grid_cell_width, R, p_adyacentes ); //mirar casillas adyacentes

		for ( unsigned int i = 0; i < p_adyacentes.size(); ++i ) //para cada casilla adyacente
		{
		  //recorremos toda la lista de puntos que hay en esa casilla
		  for ( list<point>::iterator it = points[ p_adyacentes[i] ].begin(); it != points[ p_adyacentes[i] ].end(); ++it )
		  {
			 dist = distancia_euclidea( p, *it ); //calculamos la distancia entre los puntos

			 if ( dist < R ) //si el punto esta a una distancia menor que 'R'
				++links; //tenemos un link mas
		  }
		}

		points[casilla].push_front(p);
	 }
	 
	 cout << links << endl;
  }
  
  return 0;
}

int calcular_casilla( const point p, const int num_cols_grid, const int grid_cell_width, point &grid_cell )
{
  grid_cell.x = p.x / grid_cell_width;
  grid_cell.y = p.y / grid_cell_width;
  
  return ( (grid_cell.x * num_cols_grid) + grid_cell.y );
}

void casillas_adyacentes( const point current_grid_cell, int num_cols_grid, int num_rows_grid,
								  const map< int, list<point> > &points,
								  int grid_cell_width, int R, vector<int> &p_adyacentes )
{
  int a = ceil( R / float(grid_cell_width) );

  for ( int i = current_grid_cell.x - a; i <= current_grid_cell.x + a; ++i )
  {
	 for ( int j = current_grid_cell.y - a; j <= current_grid_cell.y + a; ++j )
	 {
		if ( (i < num_rows_grid) && (j < num_cols_grid) && (i >= 0) && (j >= 0) ) //si no me salgo fuera del mundo
		{
		  int num_grid = i*num_cols_grid + j;

		  if ( points.find(num_grid) != points.end() ) //si esa casilla no esta vacia
		  {
			 p_adyacentes.push_back(num_grid); //me apunto esa casilla
		  }
		}
	 }
  }
}

float distancia_euclidea( const point p1, const point p2 )
{
  float dist;

  dist = sqrt( float( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) ) );

  return dist;
}