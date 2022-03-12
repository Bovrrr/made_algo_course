#include <algorithm>
#include <iostream>

using namespace std;

int const MIN = -1;
int const MAX = (int)1e9 + 1;

struct node {
  int value;
  int height;
  int subTreeMin;
  int subTreeMax;
  long long int sum;
  node *left;
  node *right;

  node() {}
  node(int value)
      : value(value),
        height(1),
        subTreeMax(value),
        subTreeMin(value),
        sum(value),
        left(nullptr),
        right(nullptr) {}
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

  long long int getSum(node *curr) { return curr ? curr->sum : 0; }

  void fixSum(node *curr) {
    curr->sum = curr->value + getSum(curr->left) + getSum(curr->right);
  }

  int getMin(node *curr) { return curr ? curr->subTreeMin : MAX; }

  void fixMin(node *curr) {
    curr->subTreeMin =
        min(getMin(curr->left), min(getMin(curr->right), getMin(curr)));
  }

  int getMax(node *curr) { return curr ? curr->subTreeMax : MIN; }

  void fixMax(node *curr) {
    curr->subTreeMax =
        max(getMax(curr->left), max(getMax(curr->right), getMax(curr)));
  }

  long long int countSum(node *curr, int left, int right) {
    if (not curr) {
      return 0;
    } else if (right < curr->value) {
      return countSum(curr->left, left, right);
    } else if (left > curr->value) {
      return countSum(curr->right, left, right);
    } else if (curr->subTreeMin >= left and curr->subTreeMax <= right) {
      return curr->sum;
    }

    return curr->value + countSum(curr->left, left, right) +
           countSum(curr->right, left, right);
  }

  int height(node *curr) { return curr ? curr->height : 0; }

  int bfactor(node *curr) { return height(curr->right) - height(curr->left); }

  void fixHeight(node *curr) {
    int heightLeft = height(curr->left);
    int heightRight = height(curr->right);
    curr->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
    fixMax(curr);
    fixMin(curr);
    fixSum(curr);
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
};

void solve(tree &treeInstance, long long int &querySum) {
  char oper;
  int firstValue;
  int secondValue;

  cin >> oper;
  switch (oper) {
    case '+':
      cin >> firstValue;
      treeInstance.root =
          (MIN == querySum)
              ? treeInstance.insert(treeInstance.root, firstValue)
              : treeInstance.insert(treeInstance.root,
                                    (int)((firstValue + querySum) % (int)1e9));
      break;

    case '?':
      cin >> firstValue >> secondValue;
      querySum =
          treeInstance.countSum(treeInstance.root, firstValue, secondValue);
      cout << querySum << '\n';
      break;
  }
  querySum = ('?' == oper) ? querySum : MIN;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  tree treeInstance;
  long long int querySum = 0;

  int numOper;
  cin >> numOper;

  for (int i = 0; i < numOper; ++i) {
    solve(treeInstance, querySum);
  }

  return 0;
}
