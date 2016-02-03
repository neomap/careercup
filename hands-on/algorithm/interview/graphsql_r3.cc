#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

struct event {
    int timestamp;
    int eventId;

   friend bool operator < (const event& a, const event& b) {
        return a.timestamp < b.timestamp;
    }
    friend ostream& operator << (ostream& os,const event& ev) {
        os<< "time:" <<ev.timestamp<<" event:"<<ev.eventId<<endl;
        return os;
    }
};

vector<event> query(vector<event>& all, int eventId, int prevn, int nextn) {
    // the map should be cached
    unordered_map<int, int> idmap;
    for (int i=0; i<all.size(); ++i) {
        idmap[all[i].eventId]=i;
    }
    
    // find the id for that eventId
    if (idmap.count(eventId) == 0) {
        return {};
    }
    
    int index = idmap[eventId];
    vector<event> ret;
    int start = max (0, index - prevn);
    int end = min((int)all.size(), index+nextn+1);
    for (int i=start; i<end; ++i) {
        ret.push_back(all[i]);
    }
    return ret;
}

int main() {
    // your code goes here
    // events has already been sorted by its timestamp;
    std::vector<event> events = {{10,101}, {2, 202}, {30,303}, {4,404}};
    sort(events.begin(), events.end());
    auto ret = query(events, 202, 1, 1);
    copy(ret.begin(), ret.end(), ostream_iterator<event>(cout, " "));
    return 0;
}

