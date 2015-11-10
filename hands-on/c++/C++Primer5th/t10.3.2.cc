#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    const char* words[] = { "This", "is", "a", "true", "story", "about", "me", "when", "I", "am", "in", "the", "thirties", "I", "am", "in","a","situation"};
    vector<string> vs;
    copy(begin(words), end(words), back_inserter(vs));
    cout<< "original string:"<<endl;
    //for(const char* w : words) cout<<w<<" ";
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    sort(begin(vs),end(vs));
    auto uend=unique(begin(vs),end(vs));
    vs.erase(uend,end(vs));
    stable_sort(begin(vs),end(vs),
            [](const string& a, const string& b) {
             return a.length() < b.length();
            });
    cout<< "after stable_sort for length:"<<endl;
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    int sz=4;
    auto fp = find_if(vs.cbegin(),vs.cend(),
            [sz] (const string& a) { return a.length() == sz;});
    int count = vs.end() - fp;
    cout << count << " "<<" of length " << sz<<" or longer."<<endl;
    for_each(vs.begin(), vs.end(), [](const string& a) { cout<<a<<" ";});
    cout<<endl;
}
