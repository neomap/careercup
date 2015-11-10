#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    stringstream ss;
    ss<<"1 2 3 4 5 6 7 8";
    istream_iterator<int> in_iter(ss),eof;
    vector<int> vec(in_iter,eof);
    copy(vec.begin(),vec.end(),ostream_iterator<int>(cout, " "));
    cout<<endl;
}
