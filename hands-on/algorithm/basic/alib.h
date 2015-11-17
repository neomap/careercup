#ifndef __A_LIB__
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

namespace al {

    template<class InputIter, class OutputIter, class Predicate>
    void copy_if(InputIter first, InputIter last, OutputIter result, Predicate pred) {
        while (first != last ) {
            if ( pred(*first)) *result++ = *first;
            first++;
        }
    }

    class sw{
            clock_t _last;
        public:
            void start() { _last = std::clock();}
            void reset() { _last = std::clock();}
            double elapse() { return (std::clock() - _last)*1.0/CLOCKS_PER_SEC;}
            void end(const string& task="") { std::cout << (task.size() !=0? task+" ":"")<<"elapse:"<<elapse() << " seconds"<<std::endl;}
    };
}


#endif // __A_LIB__
