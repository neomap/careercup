#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <deque>

using namespace std;

int main() {
    deque<int> vi;
    for (int i=1; i<=9; ++i) { vi.push_back(i); }
    deque<int> v1, v2,v3;
    copy(vi.begin(),vi.end(), front_inserter(v1));
    copy(vi.begin(),vi.end(), inserter(v2, v2.begin()));
    copy(vi.begin(),vi.end(), back_inserter(v3));
    cout<<"front_inserter"<<endl;
    for (int i : v1) cout<<i<<" ";
    cout<<endl;
    cout<<"inserter"<<endl;
    for (int i : v2) cout<<i<<" ";
    cout<<endl;
    cout<<"back_inserter"<<endl;
    for (int i : v3) cout<<i<<" ";
    cout<<endl;
}
