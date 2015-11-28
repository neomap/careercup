#ifndef __A_LIB__
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <deque>
#include <chrono>
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

    unsigned seed() {
        return chrono::system_clock::now().time_since_epoch().count();
    }

    struct bnode {
        int val;
        bnode *left;
        bnode *right;
        bnode(int val):val(val){
            left = right = NULL;
        }
    };
    class btree{
        private:
            bnode *_root;
            void build_tree(const char* input) {
            }
        public:
            btree(const char* input) {
                }
            bnode* get_root() const { return _root;}

    };
}


#endif // __A_LIB__
