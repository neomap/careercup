#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void PrintSubset(const vector<int> &v, int s, vector<int>& set, int k);

int main() {
	std::vector<int> v(10);
	std::iota(v.begin(),v.end(), 1);
	std::vector<int> vs;
	PrintSubset(v, 0, vs, 3);
}

void PrintSubset(const vector<int>& v, int s, vector<int>& set, int k) {
	if (set.size() == k) {
		copy(set.begin(),set.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	else if (s < v.size()) {
		set.push_back(v[s]);
		PrintSubset(v,s+1,set,k);
		set.pop_back();
		PrintSubset(v, s+1, set, k);
	}
}
