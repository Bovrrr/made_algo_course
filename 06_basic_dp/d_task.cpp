#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Min(int &a, int &b, int &c) {
  int min = (a > b) ? b : a;
  return (min > c) ? c : min;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  string a, b;
  getline(cin, a);
  getline(cin, b);

  int n = a.length();
  int m = b.length();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (ssize_t i = 0; i < n + 1; ++i) {
    dp[i][0] = i;
  }
  for (ssize_t j = 0; j < m + 1; ++j) {
    dp[0][j] = j;
  }

  for (ssize_t i = 1; i < n + 1; ++i) {
    for (ssize_t j = 1; j < m + 1; ++j) {
      if (a[i - 1] == b[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = Min(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]) + 1;
    }
  }

  cout << dp[n][m];

  return 0;
}
