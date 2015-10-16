#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
 
using namespace std;
 
int N, T = 0;
char inp[1500];
stack<char> empty;
vector<stack<char> > containers;
 
int add_to_stack(int i) {
    for(int j = 0; j < containers.size(); j++) {
        if(inp[i] <= containers[j].top()) {
            containers[j].push(inp[i]);
            return 0;
        }
    }
    containers.push_back(empty);
    containers[containers.size() - 1].push(inp[i]);
 
    return 1;
}
 
int main() {
    while(gets(inp), strcmp(inp, "end") != 0) {
        T++;
        N = strlen(inp);
        containers.clear();
 
        int ans = 0;
        for(int i = 0; i < N; i++) {
            ans += add_to_stack(i);
        }
        printf("Case %d: %d\n", T, ans);
    }
}