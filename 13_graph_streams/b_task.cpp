#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int const MAX_INT = (int)2e31;

struct Edge {
  int from;
  int to;
  int capacity;
  int flow;
};

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю размеры графа
  size_t pointSize, edgeSize;
  cin >> pointSize >> edgeSize;

  int maxCap = 0;

  // считал граф
  vector<vector<int>> graph(pointSize);
  vector<Edge> edges(2 * edgeSize);
  vector<bool> used(pointSize, false);

  int a, b, c;
  for (int i = 0; i < edgeSize; ++i) {
    cin >> a >> b >> c;

    maxCap = (maxCap > c) ? maxCap : c;

    graph[a - 1].push_back(2 * i);
    graph[b - 1].push_back(2 * i + 1);

    edges[2 * i] = {a - 1, b - 1, c, 0};
    edges[2 * i + 1] = {b - 1, a - 1, c, 0};
  }

  int result = 0;
  int curPower = floor(log2(maxCap));

  while (curPower >= 0) {
    used.assign(pointSize, false);
    used[0] = true;

    queue<int> edgeOrd;
    edgeOrd.push(0);
    int curPoint = 0;

    vector<int> pathPoint(pointSize);

    int delta = (1 << curPower);

    while (!edgeOrd.empty() && curPoint != pointSize - 1) {
      curPoint = edgeOrd.front();
      edgeOrd.pop();

      for (int &edge : graph[curPoint]) {
        if (!used[edges[edge].to] && edges[edge].flow < edges[edge].capacity &&
            delta <= edges[edge].capacity - edges[edge].flow) {
          edgeOrd.push(edges[edge].to);
          used[edges[edge].to] = true;
          pathPoint[edges[edge].to] = edge;
        }
      }
    }

    if (pointSize - 1 == curPoint) {
      result += delta;

      while (0 != curPoint) {
        edges[pathPoint[curPoint]].flow += delta;
        edges[pathPoint[curPoint] ^ 1].flow -= delta;
        curPoint = edges[pathPoint[curPoint]].from;
      }
    } else {
      --curPower;
    }
  }

  cout << result << '\n';

  for (int i = 0; i < edgeSize; ++i) {
    cout << edges[2 * i].flow << '\n';
  }

  return 0;
}