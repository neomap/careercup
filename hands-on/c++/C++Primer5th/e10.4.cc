#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

using namespace std;

int myfunc(int a, int b) { return a+b*2;}
struct myclass
{
    int operator ()(int a, int b) { return a+b*3;}
} myobj;

int main()
{
    int a[] = {1,2,3,4,5,6};
    vector<int> vi(6);
    copy(a,a+6,vi.begin());
    std::cout<<"accumulation of array:" << accumulate(a,a+6,0)<<endl;
    std::cout<<"accumulation of vector:" << accumulate(vi.cbegin(),vi.cend(),0)<<endl;
    std::cout<<"accumulation with std::minus:" << accumulate(vi.cbegin(),vi.cend(),0, std::minus<int>())<<endl;
    std::cout<<"accumulation with function:" << accumulate(vi.cbegin(),vi.cend(),0, myfunc)<<endl;
    std::cout<<"accumulation with custom function object:" << accumulate(vi.cbegin(),vi.cend(),0, myobj)<<endl;
}
