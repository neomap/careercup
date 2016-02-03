#include <iostream>
#include <numeric>
#include <vector>
using std::vector;
using std::cout;
using std::endl;
using std::iota;
int n = 1;

template<typename T> 
void print_permutation(const vector<T>& v, vector<int> &idx, vector<bool> &mask);

int main() {
	std::vector<char> v (6);
	iota(v.begin(), v.end(), 'A');
	std::vector<bool> mask(6, false);
	std::vector<int> idx;
	print_permutation(v, idx, mask);

}

template<typename T> 
void print_permutation(const vector<T>& v, vector<int> &idx, vector<bool>& mask) {
	if (idx.size() == v.size()) {
		bool first = true;
		for(auto i: idx) {
			if (! first) {
				cout << " " << v[i];
			}
			else {
				cout << n++ <<"=>"<<v[i];
				first = false;
			}
		}
		cout << endl;
	}
	else {
		for (int i=0; i < mask.size(); ++i) {
				if (!mask[i]) {
					mask[i]  = true;
					idx.push_back(i);
					print_permutation(v, idx, mask);
					mask[i] = false;
					idx.pop_back();
				}
			}		
	}
}
