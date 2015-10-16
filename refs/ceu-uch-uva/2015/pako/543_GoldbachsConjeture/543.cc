#include <bitset>
#include <cmath>
#include <iostream>
#include <set>

#define MAXN 1000000

using namespace std;

typedef set<int> PrimesSet;
PrimesSet prime_numbers;

int integerSqrt(int a) {
  return static_cast<int>(sqrtf(static_cast<float>(a)));
}

void EratosthenesSieve() {
  prime_numbers.clear();
  bitset<MAXN> marks;
  // mark 0 and 1 by default
  marks[0] = 1;
  marks[1] = 1;
  // execute the sieve from 2 until sqrt(N) (both included)
  int limit = integerSqrt(MAXN);
  for (int i=2; i<=limit; ++i) {
    if (!marks[i]) {
      // pass all non marked numbers to the map prime_numbers
      prime_numbers.insert(i);
      for (int j=i+i; j<=MAXN; j += i) {
        marks[j] = 1;
      }
    }
  }
  // introduce prime numbers from sqrt(N)+1 until MAXN (both included)
  for (int i=limit+1; i<=MAXN; ++i) {
    if (!marks[i]) prime_numbers.insert(i);
  }
}

int computeLowerBoundGoldbachConjecture(const int n) {
  // it is important the condition less or EQUAL: *it <= n/2 because for example
  // 6 = 3 +3
  for (PrimesSet::iterator it = prime_numbers.begin();
       it != prime_numbers.end() && *it <= n/2; ++it) {
    int a = *it;
    int b = n - *it;
    if (prime_numbers.find(b) != prime_numbers.end()) return a;
  }
  return 0; // return less than or equal to 0 in case of conjecture failure
}

int main() {
  int n;
  EratosthenesSieve();
  while(cin >> n && n>0) {
    int a = computeLowerBoundGoldbachConjecture(n);
    if (a <= 0) cout << "Goldbach's conjecture is wrong." << endl; // sure?
    else        cout << n << " = " << a << " + " << (n-a) << endl;
  }
  return 0;
}
