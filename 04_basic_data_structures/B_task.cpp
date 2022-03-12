#include <cstring>
#include <iostream>

using namespace std;

class Stack {
  int *elements = nullptr;
  int size;
  int capacity;

 public:
  Stack() {
    size = 0;
    capacity = 2;
    elements = new int[capacity];
  }

  ~Stack() { delete[] elements; }

  void pushBack(int elem) {
    if (size + 1 > capacity) {
      elements = (int *)realloc(elements, capacity * 2 * sizeof(int));
      capacity *= 2;
    }

    elements[size] = elem;
    ++size;
  }

  int pop() {
    if (size - 1 < capacity / 4) {
      elements = (int *)realloc(elements, capacity / 2 * sizeof(int));
      capacity /= 2;
    }
    return elements[--size];
  }
};

int main() {
  string str;
  getline(cin, str);
  Stack stack;
  int rhs, lhs;

  for (const auto &el : str) {
    if (isdigit(el)) {
      stack.pushBack(el - '0');
    } else if (string{"+-\\*"}.find(el) != string::npos) {
      switch (el) {
        case '+': {
          int rhs = stack.pop();
          int lhs = stack.pop();
          stack.pushBack(lhs + rhs);
          break;
        }
        case '-': {
          int rhs = stack.pop();
          int lhs = stack.pop();
          stack.pushBack(lhs - rhs);
          break;
        }
        case '/': {
          int rhs = stack.pop();
          int lhs = stack.pop();
          stack.pushBack(lhs / rhs);
          break;
        }
        case '*': {
          int rhs = stack.pop();
          int lhs = stack.pop();
          stack.pushBack(lhs * rhs);
          break;
        }
      }
    }
  }
  cout << stack.pop() << '\n';
  return 0;
}
