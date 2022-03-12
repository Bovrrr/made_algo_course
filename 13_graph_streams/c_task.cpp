#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
  int capacity;
  int flow;
};

vector<bool> &dfs(int point, int elem, vector<vector<int>> &graph,
                  vector<Edge> &edges, vector<bool> &used) {
  used[point] = true;

  if (point == elem) {
    return used;
  }

  for (int edge : graph[point]) {
    if (!used[edges[edge].to] && edges[edge].flow < edges[edge].capacity) {
      used = dfs(edges[edge].to, elem, graph, edges, used);
    }
  }

  return used;
}

void findFlow(int pointSize, int maxCap, vector<vector<int>> &graph,
              vector<Edge> &edges) {
  long long int result = 0;
  int curPower = floor(log2(maxCap));

  while (curPower >= 0) {
    vector<bool> used(pointSize, false);
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

  // return result;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int pointSize;
  int edgeSize;
  cin >> pointSize >> edgeSize;

  vector<vector<int>> graph(pointSize);
  vector<Edge> edges(2 * edgeSize);
  vector<bool> used(pointSize, false);
  vector<int> minEdges;

  int maxCap = 0;
  long long int minCap = 0;

  int a, b, c;
  for (int i = 0; i < edgeSize; ++i) {
    cin >> a >> b >> c;

    maxCap = (maxCap > c) ? maxCap : c;

    graph[a - 1].push_back(2 * i);
    graph[b - 1].push_back(2 * i + 1);

    edges[2 * i] = {a - 1, b - 1, c, 0};
    edges[2 * i + 1] = {b - 1, a - 1, c, 0};
  }

  findFlow(pointSize, maxCap, graph, edges);
  used = dfs(0, pointSize - 1, graph, edges, used);

  for (int i = 0; i < edgeSize; i += 2) {
    if (used[edges[i].from] != used[edges[i].to]) {
      minCap += edges[i].flow;
      minEdges.push_back(i / 2 + 1);
    }
  }

  cout << minEdges.size() << ' ' << minCap << '\n';

  for (int element : minEdges) {
    cout << element << ' ';
  }

  return 0;
}