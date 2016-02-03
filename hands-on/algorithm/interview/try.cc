#include <iostream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>
using namespace std;

uint32_t reverseBits(uint32_t n);
bool wordPattern(string pattern, string str);

int main() {
    //int num[10];
    std::array<int, 10> num;
    iota(std::begin(num), std::end(num), 30);
    set<int> s = {10,8,2,7, 5};
    copy(std::begin(num), std::end(num), inserter(s,s.end()));
    cout<< "array size" << num.size()<<endl;
    //copy(std::begin(num), std::end(num), back_inserter(s));
    multiset<int> s2 = {10,8,2,7, 5};
    s.insert(10);
    s.insert(8);
    s.insert(2);
    s.insert(7);

//    copy(num,num+100, ostream_iterator<int>(cout, " "));
    copy(s.begin(),s.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "reverse bits:" << 0<<endl;
    cout <<reverseBits(0)<<endl;

    wordPattern("abba", "dog cat cat dog");
    
    return 0;
}

    uint32_t reverseBits(uint32_t n) {
        int b = 1;
        uint32_t ret = n & 1;
        n >>=1;
        while (n>0) {
            ret <<=1;
            ret |= n&1;
            b ++;
            n >>=1;
        }
        ret <<=(32-b);
        return ret;
    }

bool wordPattern(string pattern, string str) {
        unordered_map<char, string> M;
        unordered_set<string> S;
        istringstream sin(str);
        string temp;
        for (auto p: pattern) {
            if (!(sin >> temp)) return false;
            if (M.find(p) != M.end()) {
                if (S.count(temp)) return false;
                M[p] = temp;
            }
            else if (M[p] != temp) return false;
        }
        return !(sin>>temp);
    }
