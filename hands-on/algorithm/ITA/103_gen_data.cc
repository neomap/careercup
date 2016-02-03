#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int COUNT_PER_LINE = 16;
void gen_sort_data(ostream& os, size_t size);

int main(int argc, char** argv)
{
    int size = 1024;
    if( argc > 1)
    {
        size = atoi(argv[1]);
    }
    gen_sort_data(cout, size);
}

void gen_sort_data(ostream& os, size_t size)
{
  srand(clock());
  
  for(int i=0; i< size; ++i)
  {
    os << rand()
       << ((i % COUNT_PER_LINE) == (COUNT_PER_LINE - 1) ? '\n' : '\t');
  }
}
