#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<char> S;
    copy(istream_iterator<char>(cin), istream_iterator<char>(), back_inserter(S));
    int n=S.size();
    // assume n is less than 64
    for(int i=0; i<(1<<n); ++i) {
        bool first = true;
        cout<<"{";
        for (int j=0; j<n; ++j) {
            if ((1<<j) & i) {
                if (first) { 
                    cout << S[j];
                    first = false;
                }
                else cout << "," << S[j];
            }
        }
        cout <<"}"<<endl;
    }
    return 0;
}
