#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct node {
  int value;
  int priority;
  int size;
  node *left;
  node *right;

  node() {}
  node(int value)
      : value(value),
        priority(rand() % (int)1e9),
        size(1),
        left(nullptr),
        right(nullptr) {}
};

class tree {
  pair<node *, node *> split(node *curr, int pos) {
    pair<node *, node *> res = {nullptr, nullptr};
    if (curr) {
      if (getSize(curr->left) > pos) {
        res = split(curr->left, pos);
        curr->left = res.second;
        fix(curr);
        return {res.first, curr};
      } else {
        res = split(curr->right, pos - getSize(curr->left) - 1);
        curr->right = res.first;
        fix(curr);
        return {curr, res.second};
      }
    } else {
      return res;
    }
  }

  node *merge(node *t1, node *t2) {
    if (!t1) {
      return t2;
    }
    if (!t2) {
      return t1;
    }
    if (t1->priority > t2->priority) {
      t1->right = merge(t1->right, t2);
      fix(t1);
      return t1;
    } else {
      t2->left = merge(t1, t2->left);
      fix(t2);
      return t2;
    }
  }

  void fix(node *curr) {
    curr->size = getSize(curr->left) + getSize(curr->right) + 1;
  }

 public:
  int getSize(node *curr) { return curr ? curr->size : 0; }

  node *root = nullptr;

  node *insert(node *curr, int pos, int value) {
    pair<node *, node *> res = split(curr, pos);
    res.first = merge(res.first, new node(value));

    return merge(res.first, res.second);
  }

  node *remove(node *curr, int pos) {
    pair<node *, node *> res_big = split(curr, pos);
    pair<node *, node *> res_small = split(res_big.first, pos - 1);
    delete res_small.second;

    return merge(res_small.first, res_big.second);
  }

  node *exists(node *curr, int value) {
    if (curr) {
      if (value == curr->value) {
        return curr;
      } else if (value < curr->value) {
        return exists(curr->left, value);
      } else {
        return exists(curr->right, value);
      }
    } else {
      return nullptr;
    }
  }

  node *next(int value) {
    node *curr = root;
    node *res = nullptr;

    while (curr) {
      if (curr->value > value) {
        res = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    return res;
  }

  node *prev(int value) {
    node *curr = root;
    node *res = nullptr;

    while (curr) {
      if (value > curr->value) {
        res = curr;
        curr = curr->right;
      } else {
        curr = curr->left;
      }
    }

    return res;
  }

  void printTree(node *curr) {
    if (curr) {
      printTree(curr->left);
      cout << curr->value << ' ';
      printTree(curr->right);
    }
  }
};

vector<string> split(const string &str) {
  stringstream ss(str);
  string word;
  vector<string> strVec;

  while (getline(ss, word, ' ')) strVec.push_back(word);

  return strVec;
}

void solve(const string &line, tree &treeInstance) {
  vector<string> strVec = split(line);

  if (not strVec[0].compare("add")) {
    treeInstance.root = treeInstance.insert(
        treeInstance.root, stoi(strVec[1]) - 1, stoi(strVec[2]));
  } else if (not strVec[0].compare("del")) {
    treeInstance.root =
        treeInstance.remove(treeInstance.root, stoi(strVec[1]) - 1);
  }
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  srand(time(NULL));

  int arraySize, requestsSize;
  cin >> arraySize >> requestsSize;

  tree treeInstance;
  int currElem;

  for (ssize_t i = 0; i < arraySize; ++i) {
    cin >> currElem;
    treeInstance.root = treeInstance.insert(treeInstance.root, i, currElem);
  }

  string line;
  getline(cin, line);

  for (ssize_t i = 0; i < requestsSize; ++i) {
    getline(cin, line);
    solve(line, treeInstance);
  }

  cout << treeInstance.getSize(treeInstance.root) << '\n';
  treeInstance.printTree(treeInstance.root);

  return 0;
}
