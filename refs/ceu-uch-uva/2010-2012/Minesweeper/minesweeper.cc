#include <iostream>

#define MAXN 100
#define MAXM 100

void minesweeper(char field[MAXN][MAXM],
		 char output[MAXN][MAXM],
		 int n, int m) {
  int finc[] = {-1,  0,  1, -1, 1, -1, 0, 1};
  int cinc[] = {-1, -1, -1,  0, 0,  1, 1, 1};
  for (int i=0; i<n; ++i) {
    for (int j=0; j<m; ++j) {
      if (field[i][j] == '*') output[i][j] = '*';
      else {
	output[i][j] = '0';
	for (int k=0; k<8; ++k) {
	  int f = i+finc[k];
	  int c = j+cinc[k];
	  if (f >= 0 && c >= 0 && f < n && c < m) {
	    if (field[f][c] == '*') ++output[i][j];
	  }
	}
      }
    }
  }
}

int main()
{
  int k=0;
  char field[MAXN][MAXN], output[MAXN][MAXN];
  while(1) {
    int n,m;
    std::cin >> n >> m;
    if (n == 0 && m == 0) break;
    else if (k > 0) std::cout << std::endl;
    for (int i=0; i<n; ++i)
      for (int j=0; j<m; ++j)
	std::cin >> field[i][j];
    minesweeper(field, output, n, m);
    std::cout << "Field #" << (++k) << ":" << std::endl;
    for (int i=0; i<n; ++i) {
      for (int j=0; j<m; ++j)
	std::cout << output[i][j];
      std::cout << std::endl;
    }
  }
}
