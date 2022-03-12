#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int const MAX_INT = (int)2e31;

struct edge {
  int x;
  int y;
  int edgeNumber;

  edge() : x(0), y(0), edgeNumber(0) {}
  edge(int x, int y, int edgeNumber) : x(x), y(y), edgeNumber(edgeNumber) {}

  double takeDist(edge &rhs) const {
    return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
  }

  bool operator<(edge const &rhs) const { return x < rhs.x; }
  bool operator==(edge const &rhs) const { return x == rhs.x and y == rhs.y; }
};

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю размер графа
  int pointSize;
  cin >> pointSize;

  // считываю граф
  int x, y;
  vector<edge> graph(pointSize);
  for (int i = 0; i < pointSize; ++i) {
    cin >> x >> y;
    graph[i] = {x, y, i};
  }

  vector<bool> used(pointSize, false);
  vector<double> weightArr(pointSize, MAX_INT);

  weightArr[0] = 0.;
  edge currEdge = graph[0];

  // создаю ответ, который потом выведу
  double sumOfMinOst = 0.;

  for (int i = 0; i < pointSize; ++i) {
    used[currEdge.edgeNumber] = true;
    double minDist = MAX_INT;
    edge anotherEdge = currEdge;

    for (edge &edgeExamp : graph) {
      if (!used[edgeExamp.edgeNumber]) {
        weightArr[edgeExamp.edgeNumber] =
            min(weightArr[edgeExamp.edgeNumber], edgeExamp.takeDist(currEdge));

        if (minDist > weightArr[edgeExamp.edgeNumber]) {
          minDist = weightArr[edgeExamp.edgeNumber];
          anotherEdge = edgeExamp;
        }
      }
    }

    if (MAX_INT == minDist) {
      break;
    }

    currEdge = anotherEdge;
    sumOfMinOst += minDist;
  }

  cout << sumOfMinOst;

  return 0;
}