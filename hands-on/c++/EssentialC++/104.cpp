#include <iostream>
#include <string>
using namespace std;

int main()
{
    string user_name, last_name;
    cout << "Please enter your first name:";
    cin >> user_name;
    cout << "Please enter your last name:";
    cin >> last_name;
    cout << '\n'
          << "Hello,"
          << user_name
          <<' '
          << last_name
          << " ... and goodbye!\n";
    return 0;
}

