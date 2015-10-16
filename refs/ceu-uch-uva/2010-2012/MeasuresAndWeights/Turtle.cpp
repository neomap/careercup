#include <algorithm>
#include <vector>
#include <iostream>

using std::vector;
using std::sort;
using std::cin;
using std::cout;

const int max = 6000;
const float inf = -99999;

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )

#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

struct tortuga_t {
  float peso;
  float fuerza;
  tortuga_t(float p, float f) : peso(p), fuerza(f) { }
  bool operator<(const tortuga_t &b) const {
    return fuerza > b.fuerza;
  }
};

int main(void)
{
  float peso, fuerza;
  vector<tortuga_t> turtles;
  float **matriz;
  
  while(cin >> peso >> fuerza)
    turtles.push_back(tortuga_t(peso, fuerza));
  
  sort(turtles.begin(), turtles.end());
  
  matriz = new float*[turtles.size()+1];
  for (int j=0; j<=turtles.size(); ++j) matriz[j] = new float[turtles.size()+1];
  matriz[0][0] = 0;
  for(int x = 1; x <= turtles.size(); x++)
    {
      matriz[0][x] = inf;
      matriz[x][0] = 0;
    }
  for(int k = 1; k <= turtles.size(); k++)
    {
      for(int N = 1; N <= turtles.size(); N++)
	{
	  if(N == 1)
	    {
	      matriz[k][N] = MAX(turtles[k-1].fuerza - turtles[k-1].peso, matriz[k-1][N]);
	    }
	  else{
	    if(matriz[k-1][N-1] > inf && matriz[k-1][N-1] - turtles[k-1].peso >= 0)
	      {
		matriz[k][N] = MAX(matriz[k-1][N],
				   MIN(matriz[k-1][N-1] - turtles[k-1].peso,
				       turtles[k-1].fuerza-turtles[k-1].peso));
	      }
	    else
	      {
		matriz[k][N] = matriz[k-1][N];
	      }
	  }
	}
    }
  
  for(int N = 0; N <= turtles.size(); N++)
    {
      for(int k = 0; k <= turtles.size(); k++)
    {

    cout << matriz[k][N] << " ";
    }
    cout << "\n";
    }
  
  for (int x = turtles.size(); x >=0; x--)
    {
      if(matriz[turtles.size()][x] >= 0)
	{
	  cout << x << "\n";
	  break;
	}
    }
  for (int j=0; j<=turtles.size(); ++j) delete[] matriz[j];
  delete [] matriz;
  return 0;
}
