#include <iostream>
#include <cstdlib>
#include "101_sort.h"
using namespace std;

const int MAX_COUNT = 10240;
const int NUM_ONE_LINE = 10;

typedef void (*sort_fun)(int a[], int len);
sort_fun sorts[] = 
{
    sort:: insert_sort,
};
int main(int argc, char** argv)
{
    int buffer[MAX_COUNT];
    int len;
    sort_fun sf = sorts[0];
    if( argc > 1)
    {
      int index = atoi(argv[1]);
      if (index >= sizeof(sorts)/sizeof(sort_fun))
      {
          cerr << "bad algorithm index" << endl;
          return -1;
      }
      sf = sorts [ index -1 ];
    }

    cin >> len;
    for(int i = 0; i < len; ++i)
    {
        cin >> buffer[i];
    }
    sf(buffer, len);
    for( int i = 0; i < len; ++i)
    {
        cout << buffer[i]
             << ((i % NUM_ONE_LINE) == (NUM_ONE_LINE -1 ) ? '\n' : '\t');
    }

    if( len % NUM_ONE_LINE != (NUM_ONE_LINE -1) )
    {
        cout << '\n';
    }
}
