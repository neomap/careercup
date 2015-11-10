#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// !! return type is bool, not int
bool isShorter(const string& a, const string& b){
    return a.length() <  b.length();
}

int main() {
    const char* words[] = { "This", "is", "a", "true", "story", "about", "me", "when", "I", "am", "in", "the", "thirties", "I", "am", "in","a","situation"};
    vector<string> vs(begin(words),end(words));
    //copy(begin(words), end(words), back_inserter(vs));
    cout<< "original string:"<<endl;
    //for(const char* w : words) cout<<w<<" ";
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    sort(begin(vs),end(vs));
    auto uend=unique(begin(vs),end(vs));
    cout<< "after unique operation:"<<endl;
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    vs.erase(uend,end(vs));
    cout<< "afer erase:"<<endl;
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    stable_sort(begin(vs),end(vs),isShorter);
    cout<< "after stable_sort for length:"<<endl;
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
}
