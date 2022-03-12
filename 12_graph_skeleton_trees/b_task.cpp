#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct sets {
  vector<int> rank;
  vector<int> parent;
  vector<int> experience;

  sets(int totalSize)
      : rank(vector<int>(totalSize, 0)),
        parent(vector<int>(totalSize)),
        experience(vector<int>(totalSize, 0)) {
    for (int i = 0; i < totalSize; ++i) {
      parent[i] = i;
    }
  }

  pair<int, int> get(int elem, int exp = 0) {
    if (elem != parent[elem]) {
      pair<int, int> elemAndExp = get(parent[elem], exp);
      parent[elem] = elemAndExp.first;
      experience[elem] += elemAndExp.second;

      exp = experience[elem];
    }

    return {parent[elem], exp};
  }

  int getExp(int elem) {
    int elemExp = 0;

    while (elem != parent[elem]) {
      elemExp += experience[elem];
      elem = parent[elem];
    }
    elemExp += experience[elem];

    return elemExp;
  }

  void add(int elem, int exp) {
    int clanNum = get(elem).first;
    experience[clanNum] += exp;
  }

  void join(int elem_a, int elem_b) {
    elem_a = get(elem_a).first;
    elem_b = get(elem_b).first;
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

    experience[elem_a] -= experience[elem_b];
  }
};

void solve(int const &pointSize, int const &edgeSize) {
  // создаю кланы
  sets clans(pointSize);
  // строка команд
  string command;
  // параметры команд
  int a, b;

  // простой цикл с условиями
  for (int i = 0; i < edgeSize; ++i) {
    cin >> command;

    if (not command.compare("join")) {
      cin >> a >> b;
      clans.join(a - 1, b - 1);
    } else if (not command.compare("add")) {
      cin >> a >> b;
      clans.add(a - 1, b);
    } else if (not command.compare("get")) {
      cin >> a;
      cout << clans.getExp(a - 1) << '\n';
    }
  }
}

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю размеры графа
  int pointSize, edgeSize;
  cin >> pointSize >> edgeSize;

  solve(pointSize, edgeSize);

  return 0;
}