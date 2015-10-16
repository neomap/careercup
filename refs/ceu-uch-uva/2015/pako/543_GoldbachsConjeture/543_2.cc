#include <bitset>
#include <cmath>
#include <iostream>
#include <set>

#define MAXN         1000000
#define SQRTN        1000
#define PRIMES_SQRTN 168

using namespace std;

int auxiliary_list[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                         53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107,
                         109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                         173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
                         233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
                         293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
                         367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431,
                         433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
                         499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571,
                         577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641,
                         643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709,
                         719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
                         797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
                         863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
                         947, 953, 967, 971, 977, 983, 991, 997 };

typedef set<int> PrimesSet;
PrimesSet prime_numbers;

void eratosthenesSieve() {
  prime_numbers.clear();
  bitset<MAXN> marks;
  // mark 0 and 1 by default
  marks[0] = 1;
  marks[1] = 1;
  // execute the sieve from 2 until N (both included)
  for (int i=0; i<PRIMES_SQRTN; ++i) {
    int num = auxiliary_list[i];
    prime_numbers.insert(num);
    for (int j = num<<1; j <= MAXN; j += num) {
      marks[j] = 1;
    }
  }
  for (int i=SQRTN+1; i<=MAXN; ++i) {
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
  eratosthenesSieve();
  while(cin >> n && n>0) {
    int a = computeLowerBoundGoldbachConjecture(n);
    if (a <= 0) cout << "Goldbach's conjecture is wrong." << endl; // sure?
    else        cout << n << " = " << a << " + " << (n-a) << endl;
  }
  return 0;
}
