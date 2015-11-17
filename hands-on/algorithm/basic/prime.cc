#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>
#include "alib.h"
#include <ctime>
#include <random>

using namespace std;

const int maxn = 1024*1024*10;
int buffer[maxn+1] = {0,0};
int main() {
    int max;
    //cout << "Please input the ceiling of desired primes:";
    cin >> max;
    if (max > maxn) {
        cerr << "the value is too big. (> " << maxn << ")\n";
    }
    int ms = ceil(sqrt(max));
    //memset(buffer, true, sizeof(buffer));
    for (int i=2; i<=max; ++i) buffer[i] = i;
    for (int i=2; i<= ms; i++) {
        if( !buffer[i] ) continue;
        for (int k = 2; k*i <= max; k++) buffer[i*k] = 0;
    }
    vector<int> vi;
    al::copy_if(buffer, buffer+max,
            back_inserter(vi),
            [](const int& v)->bool { return v !=0;});
    auto ran = default_random_engine(clock());
    random_shuffle(vi.begin(),vi.end(),[&ran](const int& n) {return ran()%n;});
    cout << vi.size() <<endl;
    copy(vi.begin(),vi.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
