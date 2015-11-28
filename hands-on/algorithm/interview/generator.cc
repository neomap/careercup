#include <iostream>
#include <random>
#include <cmath>
#include <map>
#include <cstdlib>
#include <string>
#include <cstring>
#include <../lib/alib.h>
using namespace std;

typedef void (*pGen)(int max, vector<int>& result);
void gen_prime(int max, vector<int>& result);
void gen_fib(int max, vector<int>& result);


int main(int argc, char** argv) {
    map<string, pGen> seqs;
    seqs["prime"] = gen_prime;
    seqs["fib"] = gen_fib;
    char* type = argv[1];
    int max = atoi(argv[2]);

    pGen gen_fun = seqs[type];
    vector<int> ret;
    gen_fun(max, ret);
    cout<<ret.size()<<endl;
    if(argc>3 && strcmp(argv[3], "-r") == 0) {
        default_random_engine ran(al::seed());
        random_shuffle(ret.begin(),ret.end(), [&ran](int m){ return ran()%m;});
    }
    copy(ret.begin(),ret.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

void gen_prime(int max, vector<int>& result) {
    int mid = ceil(sqrt(max));
    bool* A = new bool[max+1];
    memset(A,true,max+1);
    A[0] = A[1] = false;
    for(int i=2; i<=mid; ++i) if(A[i]){
            for(int k=i*2;k<=max;k+=i) A[k] = false;
        }
    result.clear();
    auto bi = back_inserter(result);
    for(int i=2; i<max+1; ++i) if(A[i]) *bi = i;
}

void gen_fib(int max, vector<int>& result) {
    result.clear();
    result.push_back(0);
    if(max>0) result.push_back(1);
    for(int i=2;; ++i) {
        int next=result[i-1] + result[i-2];
        if(next > max) break;
        result.push_back(next);
    }
}
