#include <regex>
#include <string>
#include <iostream>

using namespace std;
int main() {
   string  str("Name: andy");
   regex re("^Name: (.*)$");
   smatch match;
   if (regex_search(str, match, re) && match.size() >1 ) {
       cout <<"Find name:" << match.str(1) <<endl;
   }
   else {
       cout << "No found" <<endl;
   }
}
