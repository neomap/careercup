#include <cstdio>
#include <iostream>
#include <limits>

using namespace std;

double solve(double C, double F, double X) {
  double rate = 2.0; // two per second
  double hyp_time = X / rate;
  double best_time = numeric_limits<double>::max();
  double current_time = 0.0f;
  while(hyp_time < best_time) {
    best_time = hyp_time;
    double next_farm_time = C/rate;
    current_time += next_farm_time;
    rate += F;
    hyp_time = current_time + X/rate;
  }
  return best_time;
}

int main() {
  int T;
  cin >> T;
  for (int i=1; i<=T; ++i) {
    double C, F, X;
    cin >> C >> F >> X;
    double time = solve(C,F,X);
    printf("Case #%d: %.7f\n", i, time);
  }
  return 0;
}
