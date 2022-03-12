#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int const NO_EDGE = (int)1e5;
int const MAX_INT = (int)2e31;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> d(n, vector<int>(n));
  vector<vector<int>> graph(n, vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> d[i][j];
      graph[i][j] = j;
      d[i][j] = (NO_EDGE == d[i][j]) ? MAX_INT : d[i][j];
    }
  }

  int start = -1;

  for (int k = 0; k < n; ++k) {
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
        if (d[u][k] + d[k][v] < d[u][v] and d[u][k] < MAX_INT and
            d[k][v] < MAX_INT) {

          d[u][v] = d[u][k] + d[k][v];
          graph[u][v] = graph[u][k];

          if (u == v and d[u][v] < 0) {
            start = u;
            break;
          }
        }
      }
      if (start > -1) {
        break;
      }
    }
    if (start > -1) {
      break;
    }
  }

  if (start > -1) {
    vector<int> res;
    int curr = graph[start][start];
    res.push_back(start);

    while (curr != start) {
      res.push_back(curr);
      curr = graph[curr][start];
    }

    cout << "YES" << '\n';
    cout << res.size() << '\n';

    for (auto vertex : res) {
      cout << vertex + 1 << " ";
    }
  } else {
    cout << "NO" << '\n';
  }

  return 0;
}
