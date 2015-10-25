#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    cout << "clock:"
         << clock() << endl;
    srand(clock());
    cout << "next random number:" << rand() <<endl;
}
