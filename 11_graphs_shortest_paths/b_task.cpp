#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int const MAX_INT = (int)2e31;

struct Edge {
  Edge(int u, int v, int w) : u(u), v(v), w(w){};

  int u;
  int v;
  int w;
};

const pair<int, int> START_VERTEX = {0, 0};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  int m;

  int u;
  int v;
  int w;

  cin >> n >> m;

  vector<vector<Edge>> graph(n);

  for (int i = 0; i < m; ++i) {
    cin >> u >> v >> w;
    --u;
    --v;

    graph[u].push_back({u, v, w});
    graph[v].push_back({v, u, w});
  }

  set<pair<int, int>> q;
  vector<int> dist(n, MAX_INT);
  vector<bool> used(n, false);
  dist[0] = 0;

  q.insert(START_VERTEX);

  while (!q.empty()) {
    pair<int, int> min_v = *(q.begin());
    int curr = min_v.second;
    q.erase(min_v);
    used[curr] = true;

    for (auto &edge : graph[curr]) {
      if (!used[edge.v]) {
        q.erase({dist[edge.v], edge.v});
        dist[edge.v] = min(dist[edge.v], dist[curr] + edge.w);
        q.insert({dist[edge.v], edge.v});
      }
    }
  }

  for (int &w : dist) {
    cout << w << ' ';
  }

  return 0;
}