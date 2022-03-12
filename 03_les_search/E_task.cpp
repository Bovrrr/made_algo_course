#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int isInTime(int &time, int &n, int &x, int &y) {
  int counter = 0;
  int fastestXer = min(x, y);
  counter = (time >= fastestXer)
                ? (1 + (time - fastestXer) / x + (time - fastestXer) / y)
                : 0;
  return counter >= n;
}

int lower_bound(int &n, int &x, int &y) {
  int left = 0;
  int right = 1e9;

  while (left < right - 1) {
    int mid = (left + right) / 2;

    if (isInTime(mid, n, x, y))
      right = mid;
    else
      left = mid;
  }

  return right;
}

int main() {
  int n, x, y;
  cin >> n >> x >> y;

  cout << lower_bound(n, x, y);

  return 0;
}