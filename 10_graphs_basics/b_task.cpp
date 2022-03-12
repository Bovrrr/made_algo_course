#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// я хотел передавать везде const по ссылке эти строки, словари и тд(кроме
// result'а и used'а) но я замучался с этими ошибками passing ... as "this" ...
// поэтому убрал везде const
string Polycarp = "polycarp";
vector<string> const EMPTY_EDGES(0);

void dfs(map<string, vector<string>> &graph, string &node,
         map<string, bool> &used, int depth, int &result) {
  if (!used[node]) {
    used[node] = true;
    result = (result > ++depth) ? result : depth;

    for (string &edge : graph[node]) {
      dfs(graph, edge, used, depth, result);
    }
  }
}

int main(void) {
  int result = 1;

  // считываю количество репостов
  int repostsNumber;
  cin >> repostsNumber;

  // создаю map used
  map<string, bool> used;

  // считываю граф репостов
  map<string, vector<string>> graph;

  string point1, point2, reposted;
  for (int i = 0; i < repostsNumber; ++i) {
    cin >> point1;
    cin >> reposted;
    cin >> point2;

    // привожу к ловер кейсу
    transform(point1.begin(), point1.end(), point1.begin(),
              [](unsigned char c) { return std::tolower(c); });
    transform(point2.begin(), point2.end(), point2.begin(),
              [](unsigned char c) { return std::tolower(c); });

    // заполняю used
    used[point1] = false;
    used[point2] = false;

    if (EMPTY_EDGES != graph[point1]) {
      graph[point2].push_back(point1);
    } else {
      graph[point2].push_back(point1);
    }
  }

  // запускаю обход
  dfs(graph, Polycarp, used, 0, result);

  // вывожу длину максимальной цепочки репостов
  cout << result;
  return 0;
}
