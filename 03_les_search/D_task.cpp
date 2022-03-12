#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int func(vector<int> &rows, int &k, int &x) {
  int counter = 0;
  for (int &row : rows) counter += row / x;

  return counter < k;
}

int lower_bound(vector<int> &arr, int &k) {
  int left = 0;
  int right = 2 * ceil(accumulate(arr.begin(), arr.end(), 0) / k);

  while (left < right - 1) {
    int mid = (left + right) / 2;

    if (func(arr, k, mid))
      right = mid;
    else
      left = mid;
  }

  return right;
}

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> rows(n);
  for (int &row : rows) cin >> row;

  cout << lower_bound(rows, k) - 1;

  return 0;
}