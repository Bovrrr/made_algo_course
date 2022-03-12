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
  int id;

  Edge(int from, int to, int capacity, int flow, int id)
      : from(from), to(to), capacity(capacity), flow(flow), id(id){};
};

vector<bool> &usedCount(int point, int elem, vector<vector<Edge *>> &graph,
                        vector<bool> &used) {
  used[point] = true;

  if (point == elem) {
    return used;
  }

  for (Edge *edge : graph[point]) {
    if (!used[edge->to] && edge->flow < edge->capacity) {
      used = usedCount(edge->to, elem, graph, used);
    }
  }

  return used;
}

void findFlow(int const pointSize, int maxCap, vector<vector<Edge *>> &graph) {
  int result = 0;
  int curPow = floor(log2(maxCap));

  while (curPow >= 0) {
    queue<int> edgeOrd;
    edgeOrd.push(0);
    int curPoint = 0;
    vector<bool> used(pointSize, false);
    vector<Edge *> pathPoint(pointSize);
    used[0] = true;
    int delta = (1 << curPow);

    while (!edgeOrd.empty() && curPoint != pointSize - 1) {
      curPoint = edgeOrd.front();
      edgeOrd.pop();

      for (Edge *edge : graph[curPoint]) {
        if (!used[edge->to] && edge->flow < edge->capacity &&
            edge->capacity - edge->flow >= delta) {
          edgeOrd.push(edge->to);
          used[edge->to] = true;
          pathPoint[edge->to] = edge;
        }
      }
    }

    if (curPoint == pointSize - 1) {
      result += delta;
      while (0 != curPoint) {
        Edge *edge = pathPoint[curPoint];
        edge->flow += delta;
        graph[edge->to][edge->id]->flow -= delta;
        curPoint = edge->from;
      }
    } else {
      --curPow;
    }
  }
}

int main() {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int pointSize;
  int edgeSize;
  cin >> pointSize >> edgeSize;

  vector<vector<Edge *>> graph(pointSize);
  vector<Edge *> edges;
  vector<bool> used(pointSize, false);

  int minCap = 0;
  int maxCap = 0;

  int a, b, c;
  for (int i = 0; i < edgeSize; ++i) {
    cin >> a >> b >> c;
    --a;
    --b;
    maxCap = (maxCap > c) ? maxCap : c;

    Edge *edge = new Edge(a, b, c, 0, graph[b].size());
    graph[a].push_back(edge);
    edges.push_back(edge);

    Edge *reverseEdge = new Edge(b, a, c, 0, graph[a].size() - 1);
    graph[b].push_back(reverseEdge);
  }

  findFlow(pointSize, maxCap, graph);
  used = usedCount(0, pointSize - 1, graph, used);

  vector<int> minEdges;
  for (int i = 0; i < edges.size(); ++i) {
    if (used[edges[i]->to] != used[edges[i]->from]) {
      minCap += edges[i]->capacity;
      minEdges.push_back(i + 1);
    }
  }

  cout << minEdges.size() << ' ' << minCap << '\n';

  for (int elem : minEdges) {
    cout << elem << ' ';
  }

  return 0;
}