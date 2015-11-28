#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    int num[100];
    iota(std::begin(num), std::end(num), 1);
    copy(num,num+100, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
