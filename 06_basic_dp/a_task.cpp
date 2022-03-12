#include <iostream>
#include <vector>

using namespace std;

pair<int, int> findMax(int k, vector<int> arr, int ind) {
  pair<int, int> maxInd;
  maxInd.first = arr[ind - 1];
  int i = 1;
  maxInd.second = ind - i;

  for (; i <= k && ind - i > -1; ++i) {
    if (arr[ind - i] > maxInd.first) {
      maxInd.first = arr[ind - i];
      maxInd.second = ind - i;
    }
  }

  return maxInd;
}

int main() {
  // inits
  int n;
  int k;
  cin >> n >> k;
  vector<int> arr(n);
  for (ssize_t i = 1; i < n - 1; ++i) {
    cin >> arr[i];
  }

  // algo
  for (size_t i = 1; i < n; ++i) {
    int max = findMax(k, arr, i).first;
    arr[i] += max;
  }

  vector<int> res;
  ssize_t maxInd;
  res.push_back(n);
  for (ssize_t i = n - 1; i > 0; i = maxInd) {
    maxInd = findMax(k, arr, i).second;
    res.push_back(maxInd + 1);
  }
  // couts
  cout << arr[n - 1] << '\n';
  cout << res.size() - 1 << '\n';

  for (ssize_t i = res.size() - 1; i >= 0; --i) {
    cout << res[i] << ' ';
  }

  return 0;
}
