#include <iostream>
#include <vector>

using namespace std;

enum Colors { white = 1, grey, black };

// завожу булеву переменную: есть ли цикл?
bool cycle = false;

void dfs(vector<vector<int>> &graph, int &point, vector<Colors> &colors,
         vector<int> &result) {
  if (Colors::grey != colors[point]) {
    colors[point] = Colors::grey;

    for (int neighbourNode : graph[point]) {
      if (Colors::black != colors[neighbourNode]) {
        dfs(graph, neighbourNode, colors, result);
      }
    }

    colors[point] = Colors::black;
    result.push_back(point);
  } else {
    ::cycle = true;
    return;
  }
}

int main(void) {
  // считываю размер графа(кол-во вершин и кол-во рёбер)
  int sizeV, sizeE;
  cin >> sizeV >> sizeE;

  // считываю граф
  vector<vector<int>> graph(sizeV, vector<int>(0));

  int a, b;
  for (int i = 0; i < sizeE; ++i) {
    cin >> a >> b;
    graph[a - 1].push_back(b - 1);
  }

  // создаю массив цветов вершин графа(заполню его white)
  vector<Colors> colors(sizeV, Colors::white);

  // завожу массив-ответ
  vector<int> result(0);

  for (int node = 0; node < sizeV; ++node) {
    if (Colors::black != colors[node]) dfs(graph, node, colors, result);
  }

  // вывожу ответ
  if (::cycle) {
    cout << -1;
  } else {
    for (int i = sizeV - 1; i >= 0; --i) {
      cout << result[i] + 1 << ' ';
    }
  }

  return 0;
}
