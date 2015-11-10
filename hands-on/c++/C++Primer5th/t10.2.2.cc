#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using std::cout; using std::endl;

int main() {
    std::vector<int> vi(10);
    std::fill_n(vi.begin(),10,0);

    // demostrate back_inserter adapter
    std::vector<int> vi2;
    std::fill_n(back_inserter(vi2),10,5);
    for (auto ci=vi.cbegin(); ci != vi.cend(); ++ci) {
        cout<<*ci<<' ';
    }
    cout<<endl;
    for (auto ci=vi2.cbegin(); ci != vi2.cend(); ++ci) {
        cout<<*ci<<' ';
    }
    cout<<endl;

    // demostrate copy algorithm
    int a1[] = {1,2,3,4,5,6};
    int a2[sizeof(a1)/sizeof(*a1)];
    // c++11 provides std::begin() and std::end() function
    std::copy(std::begin(a1),std::end(a1),std::begin(a2));
    // directly copy to ostream
    std::copy(std::begin(a2),std::end(a2),std::ostream_iterator<int>(cout, " "));
    cout<<endl;

    return 0;
}
