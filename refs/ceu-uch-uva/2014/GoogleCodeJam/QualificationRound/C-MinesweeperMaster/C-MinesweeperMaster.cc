#include <algorithm>
#include <iostream>

#define MAXR 50
#define MAXC 50

using namespace std;

char **initializeField() {
  char **field = new char*[MAXR];
  for (int j=0; j<MAXR; ++j) field[j] = new char[MAXC];
  return field;
}

void showField(const char * const * field, int R, int C) {
  for (int i=0; i<R; ++i) {
    for (int j=0; j<C; ++j) {
      cout << field[i][j];
    }
    cout << endl;
  }
}

bool solve(char **field, int R, int C, int M, int pos, int prev) {
  if (pos == R-1 && R > 1 && prev == M) return false;
  if (M == (R*C) - 1) {
    for (int i=0; i<R; ++i) {
      for (int j=0; j<C; ++j) {
        field[i][j] = '*';
      }
    }
    return true;
  }
  else if (M == 0) {
    for (int i=pos; i<R; ++i) {
      for (int j=0; j<C; ++j) {
        field[i][j] = '.';
      }
    }
    return true;
  }
  else if (pos < R) {
    for (int i=0; i<=min(prev,M); ++i) {
      if (i != C-1) {
        if (! (R > 1 && pos == R-1 && prev >= C-1) ) {
          if (solve(field, R, C, M - i, pos+1, i)) {
            for (int j=0; j<i; ++j) field[pos][j] = '*';
            for (int j=i; j<C; ++j) field[pos][j] = '.';
            return true;
          }
        }
      }
    }
  }
  return false;
}

int main() {
  int T, R, C, M;
  char **field;
  field = initializeField();
  cin >> T;
  for (int i=1; i<=T; ++i) {
    cin >> R >> C >> M;
    bool possible = solve(field,R,C,M,0,C);
    cout << "Case #" << i << ":" << endl;
    if (!possible) {
      cout << "Impossible" << endl;
    }
    else {
      field[R-1][C-1] = 'c';
      showField(field,R,C);
    }
  }
  for (int i=0; i<MAXR; ++i) delete[] field[i];
  delete[] field;
  return 0;
}
