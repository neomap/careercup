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

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    const char* null = "null";
    class Codec {
    public:

        // Encodes a tree to a single string.
        string serialize(TreeNode* root) {
            queue<TreeNode*> q;
            vector<string> labels;
            if (!root) return "[]";
            q.push(root);
            while (!q.empty()) {
                auto nd = q.front();
                q.pop();
                labels.push_back(!nd? null: to_string(nd->val));
                // the following conditions are important
                if (nd && (nd->left || nd->right || !q.empty())) {
                    q.push(nd->left);
                    q.push(nd->right);
                }
            }
            ostringstream oss;
            oss << '[';
            copy(labels.begin(), labels.end()-1, ostream_iterator<string>(oss, ","));
            oss<<*labels.rbegin()<<"]";
            //cout<<oss.str()<<endl;
            return oss.str();
        }

        // Decodes your encoded data to tree.
        TreeNode* deserialize(string data) {
            vector<string> strs;
            if (data =="[]") return NULL;
            auto it = data.begin()+1; //ignore [
            while (it != data.end()) {//ignore ]
                auto next = find(it, data.end(), ',');
                if (next != data.end()) {
                    strs.push_back(data.substr(it - data.begin(), next - it));
                    it = next+1;
                } else break;
            }
            strs.push_back(data.substr(it-data.begin(), data.end()-it-1));
            //copy(strs.begin(), strs.end(), ostream_iterator<string>(cout," "));
            //cout <<endl;
            queue<TreeNode*> q;
            auto it2 = strs.begin();
            auto root = new TreeNode(stoi(*it2++));
            q.push(root);
            while (!q.empty() && it2 != strs.end()) {
                auto nd = q.front();
                q.pop();
                auto left = *it2++;
                if (left != null ) {
                    nd->left = new TreeNode(stoi(left));
                    q.push(nd->left);
                }
                if (it2 == strs.end()) break;
                auto right = *it2++;
                if (right != null) {
                    nd->right = new TreeNode(stoi(right));
                    q.push(nd->right);
                }
            }
            return root;
        }
    };

}


#endif // __A_LIB__
