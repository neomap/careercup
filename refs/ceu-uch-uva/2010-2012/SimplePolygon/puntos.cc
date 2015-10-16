#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_POINTS 100000

#define EPSILON 1e-10

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::sort;

struct Point {
  int id;
  double  x, y;
  double angular;

  bool operator<(const Point &other) const {
    return angular - EPSILON < other.angular + EPSILON;
  }
};

Point points[MAX_POINTS];

int main()
{
  int c;
  cin >> c;
  for (int i=0; i<c; ++i) {
    double mx=0, my=0;
    int n;
    cin >> n;
    
    for (int j=0; j<n; ++j) {
      cin >> points[j].x >> points[j].y;
      points[j].id  = j;
      mx	   += points[j].x;
      my	   += points[j].y;
    }
    
    mx /= n;
    my /= n;
    for (int j=0; j<n; ++j) {
      Point	&p = points[j];
      p.angular	   = atan2(p.y - my, p.x - mx);
    }
    
    sort(points, points+n);
    
    //cout << points[0].id;
    for (int j=0; j<n; ++j) cout << points[j].x << " " << points[j].y << endl; //cout << " " << points[j].id;
    cout << endl;
  }
}
