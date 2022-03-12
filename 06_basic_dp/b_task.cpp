#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getEl(vector<vector<pair<int, char>>> matrix, ssize_t i, ssize_t j) {
  if ((i >= 0 && i < matrix.size()) && (j >= 0 && j < matrix[0].size())) {
    return matrix[i][j].first;
  } else {
    return -60000;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // inits
  ssize_t n, m;
  cin >> n >> m;

  vector<vector<int>> matrix(n, vector<int>(m, 0));

  for (vector<int> &row : matrix) {
    for (int &el : row) {
      cin >> el;
    }
  }

  pair<int, char> templ = {0, ' '};
  vector<vector<pair<int, char>>> dp(n, vector<pair<int, char>>(m, templ));

  // base
  dp[0][0].first = matrix[0][0];
  dp[0][0].second = ' ';
  // for 0 row
  for (ssize_t j = 1; j < m; ++j) {
    dp[0][j].first = dp[0][j - 1].first + matrix[0][j];
    dp[0][j].second = 'R';
  }
  // for 0 column
  for (ssize_t i = 1; i < n; ++i) {
    dp[i][0].first = dp[i - 1][0].first + matrix[i][0];
    dp[i][0].second = 'D';
  }

  // for the rest of matrix
  for (ssize_t i = 1; i < n; ++i) {
    for (ssize_t j = 1; j < m; ++j) {
      if (dp[i - 1][j] > dp[i][j - 1]) {
        dp[i][j].first = dp[i - 1][j].first + matrix[i][j];
        dp[i][j].second = 'D';
      } else {
        dp[i][j].first = dp[i][j - 1].first + matrix[i][j];
        dp[i][j].second = 'R';
      }
    }
  }

  cout << dp[n - 1][m - 1].first << '\n';

  string answer = "";

  ssize_t i = n - 1;
  ssize_t j = m - 1;

  while (i >= 0 && j >= 0) {
    answer.push_back(dp[i][j].second);
    if (dp[i][j].second == 'D') {
      --i;
    } else {
      --j;
    }
  }

  for (ssize_t i = answer.length() - 1; i >= 0; --i) {
    cout << answer[i];
  }

  return 0;
}
