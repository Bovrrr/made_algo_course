#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int func(vector<int> &rows, int &k, int &x) {
  int counter = 0;
  for (int &row : rows) counter += row / x;

  return counter >= k;
}

int lower_bound(vector<int> &arr, int &k) {
  int left = 0;
  int right = 1e9;

  while (left < right - 1) {
    int mid = (left + right) / 2;

    if (func(arr, k, mid))
      left = mid;
    else
      right = mid;
  }

  return left;
}

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> rows(n);
  for (int &row : rows) cin >> row;

  cout << lower_bound(rows, k);

  return 0;
}