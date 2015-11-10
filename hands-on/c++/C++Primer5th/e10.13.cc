#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// !! return type is bool, not int
bool isShorter(const string& a){
    return a.length() < 5  ;
}

int main() {
    const char* words[] = { "This", "is", "a", "true", "story", "about", "me", "when", "I", "am", "in", "the", "thirties", "I", "am", "in","a","situation"};
    vector<string> vs;
    copy(begin(words), end(words), back_inserter(vs));
    cout<< "original string:"<<endl;
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    auto pend = partition(vs.begin(),vs.end(),isShorter);
    cout<< "after partition operation (by length 5):"<<endl;
    for(const string& w : vs) cout<<w<<" ";
    cout<<endl;
    cout<< "words less than 5 chars:"<<endl;
    copy(vs.begin(),pend, std::ostream_iterator<string>(cout," "));
    cout<<endl;
}
