#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define MAX_ROWS  10
#define MAX_COLS 100

typedef long int my_int;

my_int m[MAX_ROWS][MAX_COLS];
my_int F[MAX_ROWS][MAX_COLS];
int P[MAX_ROWS][MAX_COLS];
int path[MAX_COLS];

inline int mod(int x, int y) {
  int z = x % y;
  return (z>=0) ? z : y+z;
}

int less(int r1, int r2, int c) {
  if (c == 0) return r1 - r2;
  int ret = less(P[r1][c], P[r2][c], c-1);
  if (ret == 0) return r1 - r2;
  else return ret;
}

void unidirectionalTSP(int rows, int cols) {
  for (int r=0; r<rows; ++r) {
    F[r][0] = m[r][0];
    P[r][0] = r;
  }
  for (int c=1; c<cols; ++c) {
    for (int r=0; r<rows; ++r) {
      P[r][c] = r;
      F[r][c] = F[r][c-1];
      for (int x=-1; x<=1; x+=2) {
	int p = mod(r+x, rows);
	int l = 0;
	if (F[p][c-1] < F[r][c] ||
	    (F[p][c-1] == F[r][c] && less(p,P[r][c],c-1)<0)) {
	  P[r][c] = p;
	  F[r][c] = F[p][c-1];
	}
      }
      F[r][c] += m[r][c];
    }
  }
  int imin = 0;
  for (int r=1; r<rows; ++r) {
    if (F[r][cols-1] < F[imin][cols-1] ||
	(F[r][cols-1] == F[imin][cols-1] && less(r,imin,cols-1)<0)) imin = r;
  }
  int k = imin;
  for (int i=cols-1; i>=0; --i) {
    path[i] = k;
    k       = P[k][i];
  }
  for (int i=0; i<cols-1; ++i) cout << path[i]+1 << " ";
  cout << path[cols-1]+1 << endl;
  cout << F[imin][cols-1] << endl;
}

int main() {
  int rows, cols;
  cin >> rows;
  while(cin.good()) {
    cin >> cols;
    for (int r=0; r<rows; ++r)
      for (int c=0; c<cols; ++c)
	cin >> m[r][c];
    unidirectionalTSP(rows, cols);
    cin >> rows;
  }
}
