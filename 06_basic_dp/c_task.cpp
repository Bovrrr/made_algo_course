#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  // inits
  int n;
  cin >> n;

  vector<int> arr(n);
  for (int &el : arr) {
    cin >> el;
  }

  vector<int> dp(n, 0);

  int maxLen = 0;
  for (ssize_t i = 0; i < n; ++i) {
    for (ssize_t j = 0; j < i; ++j) {
      dp[i] = (arr[j] < arr[i] && dp[j] > dp[i]) ? dp[j] : dp[i];
    }
    dp[i]++;
    maxLen = (dp[i] > maxLen) ? dp[i] : maxLen;
  }

  cout << maxLen << '\n';

  stack<int> stack;

  for (ssize_t i = n - 1; i >= 0 && maxLen >= 1; --i) {
    if (dp[i] == maxLen) {
      stack.push(arr[i]);
      --maxLen;
    }
  }

  while (!stack.empty()) {
    cout << stack.top() << ' ';
    stack.pop();
  }

  return 0;
}
