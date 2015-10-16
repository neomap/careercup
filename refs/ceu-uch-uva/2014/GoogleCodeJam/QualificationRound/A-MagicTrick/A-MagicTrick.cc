#include <iostream>

#define N 16
#define VOLUNTEER_CHEATED -1
#define BAD_MAGICIAN -2

using namespace std;

void readGarbageRows(int n) {
  int garbage;
  for (int j=0; j<n; ++j) {
    cin >> garbage >> garbage >> garbage >> garbage;
  }
}

void readRow(int *row) {
  int r;
  cin >> r;
  for (int i=0; i<N; ++i) row[i] = 0;
  readGarbageRows(r - 1);
  for (int j=0; j<4; ++j) {
    int v;
    cin >> v;
    row[v-1] = 1;
  }
  readGarbageRows(4 - r);
}

int main() {
  int row1[N], row2[N];
  int T;
  cin >> T;
  for (int i=0; i<T; ++i) {
    readRow(row1);
    readRow(row2);
    int result = VOLUNTEER_CHEATED;
    for (int j=0; j<N; ++j) {
      // cout << j << " " << row1[j] << " " << row2[j] << endl;
      if (row1[j] > 0 && row2[j] > 0) {
        if (result == VOLUNTEER_CHEATED) result = j+1;
        else if (result > 0) result = BAD_MAGICIAN;
      }
    }
    cout << "Case #" << (i+1) << ": ";
    switch(result) {
    case VOLUNTEER_CHEATED:
      cout << "Volunteer cheated!" << endl;
      break;
    case BAD_MAGICIAN:
      cout << "Bad magician!" << endl;
      break;
    default:
      cout << result << endl;
    }
  }
  return 0;
}
