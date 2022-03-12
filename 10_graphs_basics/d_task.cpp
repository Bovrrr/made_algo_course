#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int>> readGraph(int &sizeV, int &sizeE) {
  vector<vector<int>> graph(sizeV, vector<int>(0));

  int a, b;
  for (int i = 0; i < sizeE; ++i) {
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
  }

  return graph;
}

vector<vector<int>> makeReverseGraph(vector<vector<int>> &originalGraph,
                                     int &sizeV) {
  vector<vector<int>> reverseGraph(sizeV);

  for (int node = 0; node < sizeV; ++node) {
    for (int &edge : originalGraph[node]) {
      reverseGraph[edge].push_back(node);
    }
  }

  return reverseGraph;
}

void dfsTopSort(vector<vector<int>> &graph, int &node, vector<int> &timeOut,
                vector<int> &used) {
  if (-1 == used[node]) {
    used[node] = 1;
    for (int &closeNode : graph[node]) {
      dfsTopSort(graph, closeNode, timeOut, used);
    }

    timeOut.push_back(node);
  }
}

void dfsColor(vector<vector<int>> &graph, int &node, vector<int> &colors,
              int &color) {
  if (-1 == colors[node]) {
    colors[node] = color;
    for (int &closeNode : graph[node]) {
      dfsColor(graph, closeNode, colors, color);
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю размеры графа(кол-во вершин и кол-во рёбер)
  int sizeV, sizeE;
  cin >> sizeV >> sizeE;

  // считываю граф
  vector<vector<int>> graph = readGraph(sizeV, sizeE);

  // создаю обратный граф
  vector<vector<int>> reversedGraph = makeReverseGraph(graph, sizeV);

  // заполняю вектор timeOut
  vector<int> timeOut(0);
  // аналог used в данном месте
  vector<int> colors(sizeV, -1);

  for (int node = 0; node < sizeV; ++node) {
    dfsTopSort(graph, node, timeOut, colors);
  }

  // запускаю раскраску обратного графа по компонентам сильной связности
  colors = vector<int>(sizeV, -1);

  reverse(timeOut.begin(), timeOut.end());

  int color = 0;
  for (int &node : timeOut) {
    if (-1 == colors[node]) {
      dfsColor(reversedGraph, node, colors, ++color);
    }
  }

  // считаю количество компонент сильной связности
  set<pair<int, int>> counter;

  for (int node = 0; node < sizeV; ++node) {
    for (int &edge : graph[node]) {
      if (colors[edge] != colors[node]) {
        counter.insert({colors[edge], colors[node]});
      }
    }
  }

  // вывожу ответ
  cout << counter.size();

  return 0;
}
