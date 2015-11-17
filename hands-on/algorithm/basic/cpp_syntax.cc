#include <vector>
template<class T>
void foo()
{
    typename T::iter it;
    typedef typename T::iter TI;
    std::vector<int>::iterator it2;
}

int main() {}
