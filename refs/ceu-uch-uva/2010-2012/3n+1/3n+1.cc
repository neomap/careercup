#include <algorithm>
#include <iostream>

using namespace std;

unsigned int computeCicleLength(unsigned int n);
unsigned int computeCicleLength(unsigned int n) {
  unsigned int len = 1;
  while ( n != 1 ) {
    if ( n % 2 == 0 ) n /= 2;
    else n = 3*n + 1;
    ++len;
  }
  return len;
}

int main()
{
  unsigned int min_bound;
  unsigned int max_bound;
  while (cin >> min_bound >> max_bound) {
    unsigned int max_len = 0;
    for (unsigned int n = min_bound; n <= max_bound; ++n) {
      unsigned int len = computeCicleLength(n);
      if (len > max_len) max_len = len;
    }
    cout << min_bound << ' ' << max_bound << ' ' << max_len << endl;
  }
  return 0;
}
