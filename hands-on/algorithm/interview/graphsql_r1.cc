#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

const int maxn = 214748347;

int GetMinCount(int N, int *coins, int length) {
    std::vector<int> vc;
    for (int i=0; i<length; ++i) vc.push_back(coins[i]);
    sort(vc.begin(), vc.end(), [](const int& a, const int&b){ return a>b;});
    vector<int> count(N+1, maxn);
    count[0] = 0;
    count[1] = 1;
    if (N < 0) return 0;
    if (N == 1) return 1;
    for (int i=2; i<=N; ++i) {
        for (int k=0; k<length; ++k) {
            if (i >= vc[k]) 
                count[i] = min(count[i], 1+count[i-vc[k]]);
        }
    }
    return count[N];
}

int main() {
    int coins[3] = {1,7,9};
    int N;
    while(cin>>N) {
        int ret = GetMinCount(N, coins, sizeof(coins)/sizeof(int));
        cout<< "N="<<N<<"; count = "<<ret<<endl;
    }
}