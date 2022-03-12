#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct edge {
  int pointFrom;
  int pointTo;
  int weight;

  edge() : pointFrom(0), pointTo(0), weight(0) {}
  edge(int pointFrom, int pointTo, int weight)
      : pointFrom(pointFrom), pointTo(pointTo), weight(weight) {}

  bool operator<(const edge &rhs) const { return weight < rhs.weight; }
};

struct sets {
  vector<int> rank;
  vector<int> parent;

  sets(int pointSize) : rank(pointSize, 0), parent(pointSize) {
    for (int i = 0; i < pointSize; ++i) {
      parent[i] = i;
    }
  }

  int get(int elem) {
    if (elem != parent[elem]) {
      parent[elem] = get(parent[elem]);
    }
    return parent[elem];
  }

  void join(int elem_a, int elem_b) {
    elem_a = get(elem_a);
    elem_b = get(elem_b);

    if (elem_a == elem_b) {
      return;
    }

    if (rank[elem_a] > rank[elem_b]) {
      swap(elem_a, elem_b);
    }
    if (rank[elem_a] == rank[elem_b]) {
      rank[elem_b]++;
    }
    parent[elem_a] = elem_b;
  }
};

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int pointSize, edgeSize;
  int pointFrom;
  int pointTo;
  int weight;
  long long int sumOfMinOst = 0;

  cin >> pointSize >> edgeSize;

  vector<edge> graph(edgeSize);
  sets ourSet(pointSize);

  for (int i = 0; i < edgeSize; ++i) {
    cin >> pointFrom >> pointTo >> weight;
    graph[i] = {--pointFrom, --pointTo, weight};
  }

  sort(graph.begin(), graph.end());

  for (edge &edgeExamp : graph) {
    if (ourSet.get(edgeExamp.pointFrom) != ourSet.get(edgeExamp.pointTo)) {
      sumOfMinOst += edgeExamp.weight;
      ourSet.join(edgeExamp.pointFrom, edgeExamp.pointTo);
    }
  }

  cout << sumOfMinOst;

  return 0;
}