#include <cmath>
#include <iostream>
using namespace std;
int main() {
  long int S;
  long int D;
  while(cin >> S >> D) {
    long double A, B;
    A = -(S - 0.5);
    B = sqrtl( A*A + 2.0*D );
    long int N = ceill(A + B) + S - 1;
    cout << N << endl;
  }
  return 0;
}
