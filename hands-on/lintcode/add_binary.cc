#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
class Solution {
public:
    /**
     * @param a a number
     * @param b a number
     * @return the result
     */
    string addBinary(string& a, string& b) {
        // Write your code here
        if(a.length() == 0 || b.length() == 0) return a+b;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int addon = 0;
        int maxlen = max(a.length(), b.length());
        string c;
        for(int i= 0; i<maxlen; ++i) {
            int sum = addon;
            if (i<a.length()) sum += a[i] - '0';
            if (i<b.length()) sum += b[i] - '0';
            c.push_back((sum & 1) + '0');
            addon = sum>>1;
        }
        if (addon == 1) {
            c.push_back('1');
        }
        reverse(c.begin(),c.end());
        return c;
    }
};

int main()
{
    string a = "1110";
    string b = "1101";
    cout << (new Solution())->addBinary(a,b)<<endl;
    return 0;
}