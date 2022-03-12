#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// загуглил границы long long'а в С++
int const MINUS_INF = numeric_limits<long long int>::min();

struct node {
  long long int value;
  long long int setValue;
  long long int addValue;
  bool setValueExist = false;
};

vector<string> split(const string &str) {
  stringstream ss(str);
  string word;
  vector<string> strVec;

  while (getline(ss, word, ' ')) strVec.push_back(word);

  return strVec;
}

void solve(string &line, vector<long long int> &arr, vector<long long int> &T) {
  vector<string> strVec = split(line);

  if (not strVec[0].compare("min")) {
  } else if (not strVec[0].compare("set")) {
  } else if (not strVec[0].compare("add")) {
  }
}

vector<node> buildTree(vector<long long int> &arr) {
  size_t treeSize = 1;
  while (treeSize < arr.size()) treeSize = (treeSize << 1);
  treeSize = (treeSize << 1);

  node etalon = {0, NULL};
  vector<node> tree(treeSize, etalon);

  for (size_t nodeIndex = 0; nodeIndex < arr.size(); ++nodeIndex)
    tree[nodeIndex + (treeSize >> 1) - 1].value = arr[nodeIndex];

  for (ssize_t nodeIndex = (treeSize >> 1) - 2; nodeIndex >= 0; --nodeIndex)
    tree[nodeIndex].value =
        tree[2 * nodeIndex + 1].value + tree[2 * nodeIndex + 2].value;
}

long long int rmq(ssize_t nodeIndex, ssize_t left, ssize_t right, ssize_t begin,
                  ssize_t end, vector<node> tree) {
  if (left > end || right < begin) return MINUS_INF;
  if (left >= begin && right <= end) return get(nodeIndex, tree);
  ssize_t mid = (left + right) / 2;
  return min(rmq(2 * nodeIndex + 1, left, mid, begin, end, tree),
             rmq(2 * nodeIndex + 2, mid + 1, right, begin, end, tree));
}

void updateAdd(ssize_t nodeIndex, ssize_t left, ssize_t right, ssize_t begin,
               ssize_t end, long long int value, vector<node> &tree) {
  push(nodeIndex, tree);
  if (left > end || right < begin) return;
  if (left >= begin && right <= end) {
    tree[nodeIndex].addValue += value;
  }
  ssize_t mid = (left + right) / 2;
  updateAdd(2 * nodeIndex + 1, left, mid, begin, end, value, tree);
  updateAdd(2 * nodeIndex + 2, mid + 1, right, begin, end, value, tree);
  tree[nodeIndex].value =
      min(get(2 * nodeIndex + 1, tree), get(2 * nodeIndex + 2, tree));
}

void updateSet(ssize_t nodeIndex, ssize_t left, ssize_t right, ssize_t begin,
               ssize_t end, long long int value, vector<node> &tree) {
  push(nodeIndex, tree);
  if (left > end || right < begin) {
    return;
  }
  if (left >= begin && right <= end) {
    tree[nodeIndex].value = (tree[nodeIndex].value < tree[nodeIndex].setValue)
                                ? tree[nodeIndex].value
                                : tree[nodeIndex].setValue;
  }
}

void push(ssize_t nodeIndex, vector<node> &tree) {
  if (left == right) {
    if (tree[nodeIndex].setValueExist) {
      tree[nodeIndex].value = tree[nodeIndex].setValue;
      tree[nodeIndex].setValueExist = false;
    }
    tree[nodeIndex].value += tree[nodeIndex].addValue;
  } else {
    tree[nodeIndex * 2 + 1].addValue += tree[nodeIndex].addValue;
    tree[nodeIndex * 2 + 2].addValue += tree[nodeIndex].addValue;
    ssize_t mid = (left + right) / 2;
    tree[nodeIndex].value =
        min(get(2 * nodeIndex + 1, tree), get(2 * nodeIndex + 2, tree));
  }
  tree[nodeIndex].addValue = 0;
}

long long int get(ssize_t nodeIndex, vector<node> &tree) {
  return (tree[nodeIndex].setValueExist)
             ? tree[nodeIndex].setValue
             : tree[nodeIndex].value + tree[nodeIndex].addValue;
}

int main() {
  size_t arrSize;
  cin >> arrSize;

  // считываю исходный массив arr
  vector<long long int> arr(arrSize, 0);
  for (size_t ind = 0; ind < arrSize; ++ind) cin >> arr[ind];

  vector<node> tree = buildTree(arr);

  //  string line;
  //  getline(cin, line);
  //  while (getline(cin, line))
  //    solve(line);

  return 0;
}
