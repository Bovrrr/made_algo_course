#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

const double EPS = 1e-6;

double func(double x) { return x * x + sqrt(x); }

double bin_search(double y) {
  double left = 0.;
  double right = y;
  const int ITN = ceil(log2(right / EPS)) + 1;

  for (int i = 0; i < ITN; ++i) {
    double mid = (left + right) / 2.;

    if (func(mid) < y)
      left = mid;
    else
      right = mid;
  }

  return right;
}

int main() {
  double num;
  cin >> num;

  cout << setprecision(6) << fixed << bin_search(num);

  return 0;
}