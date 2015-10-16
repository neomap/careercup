#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
using namespace std;

class key { 
	vector<int> pattern;

	public:

		key(string word){
			map<char,int> asign_letter;
			int nextindex=0;

				for(unsigned int x=0; x < word.size(); x++){
					char c=word[x];
					if(asign_letter.find(c) == asign_letter.end()){
						asign_letter[c] = nextindex++;
					}
					pattern.push_back(asign_letter[c]);
				}
		} 

  bool operator < (const key &other) const {
    // a => *this (pattern)
    // b => other.pattern
		if(pattern.size() < other.pattern.size()){return true;}
		if(pattern.size() > other.pattern.size()){return false;}
    for(unsigned int x=0; x < pattern.size(); x++){
			if(pattern[x] < other.pattern[x]){ return true; }
			if(pattern[x] > other.pattern[x]){ return false; }		
		}
		return false;
  }
	bool operator == (const key &other) const {
    // a => *this (pattern)
    // b => other.pattern
		if(pattern.size() != other.pattern.size()){return false;}
    for(unsigned int x=0; x < pattern.size(); x++){
			if(pattern[x] != other.pattern[x]){ return false; }		
		}
		return true;
  }
};

map<key,list<string> > dictionary; 

void print(list<string> &l) {
  for(list<string>::iterator it = l.begin(); it!=l.end(); ++it) {
    cout << *it << endl;
  }
}

int main(){

  string word;
  int num_words;
  cin >> num_words;

  for(int x=0; x < num_words; x++){
	  cin >> word;
    key K(word);
    dictionary[K].push_back(word);
  }

  while(cin >> word) {
    key K(word);
    print(dictionary[K]);
}
}
