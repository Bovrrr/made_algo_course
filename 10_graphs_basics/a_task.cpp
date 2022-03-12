#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>> &graph, int node, vector<int> &colors, int color) {
  if (not colors[node]) {
    colors[node] = color;
    for (int neighbor : graph[node]) {
      dfs(graph, neighbor, colors, color);
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  // считываю размеры
  int n, m;
  cin >> n >> m;

  // считываю граф
  vector<vector<int>> graph(n, vector<int>(0));
  int a, b;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    if (not(a == b)) {  // проверка на петлю
      graph[a - 1].push_back(b - 1);
      graph[b - 1].push_back(a - 1);
    }
  }

  // разукрашиваю граф в компоненты связности
  vector<int> colors(n, 0);
  int compCount = 0;

  for (int i = 0; i < n; ++i) {
    if (not colors[i]) {
      dfs(graph, i, colors, ++compCount);
    }
  }

  // вывожу количество компонент и цвета вершин
  cout << compCount << '\n';
  for (int color : colors) {
    cout << color << ' ';
  }

  return 0;
}
