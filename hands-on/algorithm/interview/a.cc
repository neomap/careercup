#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        int n = wordList.size();
        vector<vector<int>> adj(n+2);
        vector<string> words(n+2);
        words[0] = beginWord;
        if (beginWord == endWord) return 2;
        copy(wordList.begin(), wordList.end(), words.begin()+1);
        words[n+1] = endWord;
        for (int i=0; i< n+1; ++ i) {
            for (int j=i+1; j<n+2;++j) {
                int  dc = 0;
                for (int k=0; k<beginWord.size() && dc<2; ++k) {
                    if (words[i][k] != words[j][k]) ++dc;
                }
                if (dc == 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
                cout << "adj for"<<i<<":";
                copy(adj[i].begin(), adj[i].end(), ostream_iterator<int>(cout, " "));
                cout <<endl;
        }
        
        // bfs search from 0 to n+1
        cout << "seach start..."<<endl;
        int step = 0;
        queue<int> q;
        q.push(0);
        q.push(-1);
        vector<int> color(n+2, 0);
        while (step < n+2 && !q.empty()) {
            int cur = q.front();
            q.pop();
            if (cur == -1) {
                step++;
                cout << "++ step" <<endl;
                if (!q.empty()) q.push(-1);
                continue;
            }
            color[cur] = 1;
            cout << "visit :"<< words[cur]<<endl;
            if (cur == n+1) break; // find the target word
            for (int i=0; i< adj[cur].size(); ++i) {
                if (!color[adj[cur][i]]) q.push(adj[cur][i]);
            }
        }
        if (!color[n+1]) return 0;
        return step+1;
    }
};

// int main() {
//     unordered_set<string> wd {"hot","dot","dog","lot","log"};
//     Solution sol;
//     cout << "ladder length:"<<sol.ladderLength("hit", "cog", wd)<<endl;
// }