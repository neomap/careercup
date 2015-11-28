#include <cassert>
#include <string>
#include <cstring>
#include <cstdlib>
#include <exception>
#include <iostream>

using namespace std;

string intToString(int x);
int stringToInt(string str);

int main() {
    assert("12345" == intToString(12345));
    assert("-12345" == intToString(-12345));
    assert("0" == intToString(0));
    assert(12345 == stringToInt("12345"));
    assert(12345 == stringToInt("+12345"));
    assert(-12345 == stringToInt("-12345"));
    assert(0== stringToInt("0"));
}


string intToString(int x) {
   char buffer[17] = {0};
   buffer[16] = '\0';
   bool neg = x <0;
   if (x == 0) return "0";
   if (neg) x*=-1;
   int i = 15;
   for (; x > 0; --i) {
       buffer[i] = x%10 + '0';
       x/=10;
   }
   if (neg) buffer[i--] = '-';
   return string(buffer+i+1,buffer+16);
}


int stringToInt(string str) {
    int len = str.length();
    if (len == 0) throw invalid_argument("str");
    int i=0;
    bool neg = false;
    if (str[0] == '+' || str[0] == '-') {
        i++;
        neg = str[0] == '-';
    }
    int val = 0;
    for (;i<len;++i) {
        if (str[i] > '9' || str[i] < '0' ) throw invalid_argument("str");
        val = val*10+str[i]-'0';
    }
    return neg? val*-1 : val;;
}
