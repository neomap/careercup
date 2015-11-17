#include <vector>
#include <iostream>

using namespace std;

int main() {
    int vals[] = { 2,3,4,5,6,8,10,20};
    vector<int> vi(begin(vals),end(vals));
    auto it = vi.crbegin();
    for(; it != vi.crend(); ++it) {
        cout << " "<<*it;
    }
    cout << endl;
    auto it2 = vi.cend();
    for( it2--; it2 != vi.begin(); --it2) {
        cout << " "<<*it2;
    }
    cout << " " <<*(vi.begin());
    cout <<endl;
}
