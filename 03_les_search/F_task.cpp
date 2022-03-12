#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double dist_p(double x, double y) { return sqrt(pow(x, 2) + pow(1. - y, 2)); }
double dist_f(double x, double y) { return sqrt(pow(y, 2) + pow(1. - x, 2)); }

double time(double &x, double &y, int &Vp, int &Vf) {
  return dist_p(x, y) / Vp + dist_f(x, y) / Vf;
}

double ternary_search_min(int &Vp, int &Vf, double &y) {
  const double EPS = 1e-4;
  const int ITN = ceil(log2(1 / EPS) / log2(1.5)) + 1;

  double left = 0.;
  double right = 1.;

  for (int i = 0; i < ITN; ++i) {
    double m1 = left + (right - left) / 3;
    double m2 = right - (right - left) / 3;

    if (time(m1, y, Vp, Vf) < time(m2, y, Vp, Vf))
      right = m2;
    else
      left = m1;
  }

  return left;
}

int main() {
  int Vp, Vf;
  double y;
  cin >> Vp >> Vf >> y;

  cout << setprecision(4) << fixed << ternary_search_min(Vp, Vf, y);

  return 0;
}