#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string &line) {
  stringstream ss(line);
  vector<string> result;
  string cur_sub_str;

  while (getline(ss, cur_sub_str, ' ')) {
    result.push_back(cur_sub_str);
  }

  return result;
}

struct element {
  int maxOfSet;
  int minOfSet;
  int sizeOfSet;

  element() : sizeOfSet(1) {}
};

struct sets {
  int totalSize;
  vector<int> rang;
  vector<int> parent;
  vector<element> elements;

  // init
  sets(int totalSize)
      : totalSize(totalSize),
        rang(vector<int>(totalSize, 0)),
        parent(vector<int>(totalSize)),
        elements(vector<element>(totalSize)) {
    for (int i = 0; i < totalSize; ++i) {
      parent[i] = i;
      elements[i].maxOfSet = i;
      elements[i].minOfSet = i;
    }
  }

  // print set parameters
  element &takeSetParams(int elem) { return elements[get(elem)]; }

  // get
  int get(int elem) {
    if (elem != parent[elem]) {
      parent[elem] = get(parent[elem]);
    }
    return parent[elem];
  }

  // join
  void join(int elem_a, int elem_b) {
    elem_a = get(elem_a);
    elem_b = get(elem_b);
    if (elem_a == elem_b) {
      return;
    }

    if (rang[elem_a] > rang[elem_b]) {
      swap(elem_a, elem_b);
    }
    if (rang[elem_a] == rang[elem_b]) {
      rang[elem_b]++;
    }
    parent[elem_a] = elem_b;

    elements[elem_b].maxOfSet =
        (elements[elem_b].maxOfSet > elements[elem_a].maxOfSet)
            ? elements[elem_b].maxOfSet
            : elements[elem_a].maxOfSet;
    elements[elem_b].minOfSet =
        (elements[elem_b].minOfSet < elements[elem_a].minOfSet)
            ? elements[elem_b].minOfSet
            : elements[elem_a].minOfSet;
    elements[elem_b].sizeOfSet += elements[elem_a].sizeOfSet;
  }
};

void solve(string &line, sets &ourSet) {
  vector<string> commandParams = split(line);

  if (!commandParams[0].compare("union")) {
    ourSet.join(stoi(commandParams[1]) - 1, stoi(commandParams[2]) - 1);
  } else if (!commandParams[0].compare("get")) {
    element setParams = ourSet.takeSetParams(stoi(commandParams[1]) - 1);
    cout << setParams.minOfSet + 1 << ' ' << setParams.maxOfSet + 1 << ' '
         << setParams.sizeOfSet << '\n';
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int totalSize;
  cin >> totalSize;

  sets ourSet(totalSize);

  string line;
  getline(cin, line);
  while (getline(cin, line)) {
    solve(line, ourSet);
  }

  return 0;
}