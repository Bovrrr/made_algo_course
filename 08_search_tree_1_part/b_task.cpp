#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct node {
  int value;
  int height;
  node *left;
  node *right;

  node() {}
  node(int value) : value(value), height(1), left(nullptr), right(nullptr) {}
};

class tree {
 public:
  node *root = nullptr;

  node *insert(node *curr, int value) {
    if (not curr) {
      return new node(value);
    } else if (value < curr->value) {
      curr->left = insert(curr->left, value);
    } else if (value > curr->value) {
      curr->right = insert(curr->right, value);
    }

    return balance(curr);
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

  node *remove(node *curr, int value) {
    if (curr) {
      if (value < curr->value) {
        curr->left = remove(curr->left, value);
      } else if (value > curr->value) {
        curr->right = remove(curr->right, value);
      } else {
        if (not curr->left) {
          node *temp = curr;
          curr = curr->right;
          delete temp;
        } else if (not curr->right) {
          node *temp = curr;
          curr = curr->left;
          delete temp;
        } else {
          curr->value = findMax(curr->left)->value;
          curr->left = remove(curr->left, curr->value);
        }
      }
    }

    return curr ? balance(curr) : curr;
  }

  int height(node *curr) { return curr ? curr->height : 0; }

  int bfactor(node *curr) { return height(curr->right) - height(curr->left); }

  void fixHeight(node *curr) {
    int heightLeft = height(curr->left);
    int heightRight = height(curr->right);
    curr->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
  }

  node *smallRotateRight(node *p) {
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);  //чиним высоты, балансы
    fixHeight(q);  //чиним высоты, балансы

    return q;
  }

  node *smallRotateLeft(node *p) {
    node *q = p->right;
    p->right = q->left;
    q->left = p;
    fixHeight(p);
    fixHeight(q);

    return q;
  }

  node *findMax(node *curr) {
    while (curr->right) {
      curr = curr->right;
    }

    return curr;
  }

  node *balance(node *curr) {
    fixHeight(curr);
    if (2 == bfactor(curr)) {
      if (0 > bfactor(curr->right)) {
        curr->right = smallRotateRight(curr->right);
      }

      return smallRotateLeft(curr);
    }
    if (-2 == bfactor(curr)) {
      if (0 < bfactor(curr->left)) {
        curr->left = smallRotateLeft(curr->left);
      }

      return smallRotateRight(curr);
    }

    return curr;
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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  tree treeInstance;
  string line;
  while (getline(cin, line)) {
    solve(line, treeInstance);
  }

  return 0;
}
