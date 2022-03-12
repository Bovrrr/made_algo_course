#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int const MAX_INT = (int)2e31;

struct Edge {
  int from;
  int to;
  short int capacity;
  int flow;
};

int pushFlow(int point, int target, int curFlow, vector<vector<int>> &graph,
             vector<Edge> &edges, vector<bool> &used) {
  used[point] = true;

  if (point == target) {
    return curFlow;
  }

  for (int &edgeTo : graph[point]) {
    if (!used[edges[edgeTo].to] &&
        (edges[edgeTo].flow < edges[edgeTo].capacity)) {
      int nextFlow = min(curFlow, edges[edgeTo].capacity - edges[edgeTo].flow);
      int delta =
          pushFlow(edges[edgeTo].to, target, nextFlow, graph, edges, used);

      if (delta > 0) {
        edges[edgeTo ^ 1].flow -= delta;
        edges[edgeTo].flow += delta;

        return delta;
      }
    }
  }

  return 0;
}

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю размеры графа
  size_t pointSize, edgeSize;
  cin >> pointSize >> edgeSize;

  // считал граф
  vector<vector<int>> graph(pointSize);
  vector<Edge> edges(2 * edgeSize);
  vector<bool> used(pointSize, false);

  int a, b;
  short int c;
  for (int i = 0; i < edgeSize; ++i) {
    cin >> a >> b >> c;
    graph[a - 1].push_back(2 * i);
    graph[b - 1].push_back(2 * i + 1);

    edges[2 * i] = {a - 1, b - 1, c, 0};
    edges[2 * i + 1] = {b - 1, a - 1, c, 0};
  }

  int result = 0;

  while (true) {
    used.assign(pointSize, false);
    int delta = pushFlow(0, pointSize - 1, MAX_INT, graph, edges, used);

    if (0 < delta) {
      result += delta;
    } else {
      break;
    }
  }

  cout << result;

  return 0;
}