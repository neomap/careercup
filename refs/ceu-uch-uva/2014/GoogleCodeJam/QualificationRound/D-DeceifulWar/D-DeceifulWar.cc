#include <algorithm>
#include <iostream>
#include <set>
#include <string>

#define MAXN 1000

using namespace std;

int playDeceifulWar(double *naomi, double *ken, int N) {
  set<double> naomi_set(naomi, naomi+N);
  int k = 0;
  for (int i=0; i<N; ++i) {
    set<double>::iterator naomi_it = naomi_set.upper_bound(ken[i]);
    if (naomi_it != naomi_set.end()) {
      ++k;
    }
    else {
      naomi_it = naomi_set.begin();
    }
    naomi_set.erase( naomi_it );
  }
  return k;
}

int playWar(double *naomi, double *ken, int N) {
  set<double> ken_set(ken, ken+N);
  int k = 0;
  for (int i=0; i<N; ++i) {
    set<double>::iterator ken_it = ken_set.upper_bound(naomi[i]);
    if (ken_it == ken_set.end()) {
      ++k;
      ken_it = ken_set.begin();
    }
    ken_set.erase( ken_it );
  }
  return k;
}

double readNumber() {
  string str;
  cin >> str;
  while(str.size() < 7) str = str + "0";
  return atof(str.substr(2,str.size()-2).c_str());
}

int main() {
  double *naomi = new double[MAXN];
  double *ken   = new double[MAXN];
  int T, N;
  cin >> T;
  for (int i=1; i<=T; ++i) {
    cin >> N;
    for (int j=0; j<N; ++j) naomi[j] = readNumber();
    for (int j=0; j<N; ++j) ken[j] = readNumber();
    cout << "Case #" << i << ": "
         << playDeceifulWar(naomi, ken, N) << " "
         << playWar(naomi, ken, N) << endl;
  }
  return 0;
}
