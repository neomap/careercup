#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXLONG  2000
#define MAXNCUTS   50
#define INF 9999999

int main(void) {
  int l, n;                       // longitud, numero de cortes y auxiliar
  int positions[MAXNCUTS+2];      // puntos de corte
  int PD[MAXNCUTS+2][MAXNCUTS+2]; // matriz de PD

  while((cin >> l) && (l != 0)) {
    cin >> n;
                
    for(int i=0; i<n; i++) {
      cin >> positions[i+1];
    }
        
    positions[0] = 0;
    n++;
    positions[n] = l;
                
    for(int i=0; i<=n; i++)
      for(int j=0;j<=n;j++)
	PD[i][j] = 0;

    for(int d=2; d<=n; d++) {
      for(int i=0, j=d; i<=n && j<=n; i++, j++) {
	PD[i][j] = INF;
	for(int k=i+1; k<j; k++) {
	  PD[i][j] = min(PD[i][k] + PD[k][j] + positions[i] - positions[j],
			 PD[i][j]);
	}
      }
    }
        
    cout << "The minimum cutting is "<< PD[0][n] << "." << endl;
  }
  
  return 0;
}

