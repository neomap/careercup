#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;


bool check_size(const int& a, const string& s) {
    return a > s.length();
}

int main() {
    int a[] = { 4,2,1,9,5};
    vector<int> vi;
    copy(begin(a),end(a),back_inserter(vi));
    auto pos = find_if(vi.begin(),vi.end(),bind(check_size,_1,"hello"));
    if (pos != vi.end()) {
        cout<< "The first int that is bigger: " <<*pos<<endl;
    }
    else {
        cout << "No such int value found!"<<endl;
    }
}
