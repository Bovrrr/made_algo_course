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
    graph[b - 1].push_back(a - 1);
  }

  return graph;
}

void dfs(vector<vector<int>> &graph, vector<bool> &used, vector<int> &timeIn,
         vector<int> &up, set<int> &artPoints, int &currNode, int &parentNode,
         int &timeOrder) {
  int childrenCount = 0;
  timeIn[currNode] = ++timeOrder;
  up[currNode] = timeOrder;
  used[currNode] = true;

  for (int node : graph[currNode]) {
    if (used[node] and (node != parentNode)) {
      up[currNode] = min(timeIn[node], up[currNode]);
    } else if (not used[node]) {
      dfs(graph, used, timeIn, up, artPoints, node, currNode, timeOrder);
      ++childrenCount;
      up[currNode] = min(up[node], up[currNode]);

      if (timeIn[currNode] <= up[node] and -1 != parentNode) {
        artPoints.insert(currNode);
      }
    }
  }

  // ▪ Почему этого недостаточно?
  // ▪ Корень!
  if (-1 == parentNode and 1 < childrenCount) {
    artPoints.insert(currNode);
  }
}

void dfs(vector<vector<int>> &graph, vector<bool> &used, vector<int> &timeIn,
         vector<int> &up, set<int> &artPoints, int &currNode, int &&parentNode,
         int &timeOrder) {
  int childrenCount = 0;
  timeIn[currNode] = ++timeOrder;
  up[currNode] = timeOrder;
  used[currNode] = true;

  for (int node : graph[currNode]) {
    if (used[node] and (node != parentNode)) {
      up[currNode] = min(timeIn[node], up[currNode]);
    } else if (not used[node]) {
      dfs(graph, used, timeIn, up, artPoints, node, currNode, timeOrder);
      ++childrenCount;
      up[currNode] = min(up[node], up[currNode]);

      if (timeIn[currNode] <= up[node] and -1 != parentNode) {
        artPoints.insert(currNode);
      }
    }
  }

  // ▪ Почему этого недостаточно?
  // ▪ Корень!
  if (-1 == parentNode and 1 < childrenCount) {
    artPoints.insert(currNode);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю размеры графа
  int sizeV, sizeE;
  cin >> sizeV >> sizeE;

  // считываю граф
  vector<vector<int>> graph = readGraph(sizeV, sizeE);

  // создаю массив used
  vector<bool> used(sizeV, false);
  // создаю массив времён входа в вершины
  vector<int> timeIn(sizeV, 0);
  // создаю массив вершин, до которых можно подняться
  vector<int> up(sizeV, 0);
  // создаю множество артикулейшн поинтс
  set<int> artPoints;

  int timeOrder = 0;

  for (int node = 0; node < sizeV; ++node) {
    if (!used[node]) {
      dfs(graph, used, timeIn, up, artPoints, node, -1, timeOrder);
    }
  }

  cout << artPoints.size() << endl;
  for (int node : artPoints) {
    cout << node + 1 << ' ';
  }

  return 0;
}