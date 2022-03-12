#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct node {
  int value;
  int priority;
  node *left;
  node *right;

  node() {}
  node(int value)
      : value(value),
        priority(rand() % (int)1e9),
        left(nullptr),
        right(nullptr) {}
};

class tree {
  pair<node *, node *> split(node *curr, int value) {
    pair<node *, node *> res = {nullptr, nullptr};
    if (curr) {
      if (curr->value > value) {
        res = split(curr->left, value);
        curr->left = res.second;
        res.second = curr;
      } else {
        res = split(curr->right, value);
        curr->right = res.first;
        res.first = curr;
      }
    }

    return res;
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
      return t1;
    } else {
      t2->left = merge(t1, t2->left);
      return t2;
    }
  }

 public:
  node *root = nullptr;

  node *insert(node *curr, int value) {
    pair<node *, node *> res = split(curr, value);
    res.first = merge(res.first, new node(value));

    return merge(res.first, res.second);
  }

  node *remove(node *curr, int value) {
    pair<node *, node *> res_big = split(curr, value);
    pair<node *, node *> res_small = split(res_big.first, value - 1);
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
      cout << curr->value;
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

  if (not strVec[0].compare("insert")) {
    treeInstance.root = treeInstance.insert(treeInstance.root, stoi(strVec[1]));
  } else if (not strVec[0].compare("delete")) {
    treeInstance.root = treeInstance.remove(treeInstance.root, stoi(strVec[1]));
  } else if (not strVec[0].compare("exists")) {
    node *curr = treeInstance.exists(treeInstance.root, stoi(strVec[1]));
    curr ? cout << "true\n" : cout << "false\n";
  } else if (not strVec[0].compare("next")) {
    node *curr = treeInstance.next(stoi(strVec[1]));
    curr ? cout << curr->value << "\n" : cout << "none\n";
  } else if (not strVec[0].compare("prev")) {
    node *curr = treeInstance.prev(stoi(strVec[1]));
    curr ? cout << curr->value << '\n' : cout << "none\n";
  }
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  srand(time(NULL));

  tree treeInstance;
  string line;

  while (getline(cin, line)) {
    solve(line, treeInstance);
  }

  return 0;
}
