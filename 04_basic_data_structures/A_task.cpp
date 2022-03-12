#include <iostream>

using namespace std;

struct Node {
  int value;
  int minValue;
  Node *next = nullptr;
};

struct Stack {
  Node *head = nullptr;
  int size = 0;
};

void pushElem(Stack *stack, int &elem) {
  if (stack->head) {
    stack->head = new Node;
    stack->head->value = elem;
    stack->head->minValue = elem;
  } else {
    Node *cur = stack->head;
    Node *newElem = new Node;
    newElem->next = cur;
    stack->head = newElem;
    newElem->value = elem;

    stack->head->minValue = (stack->head->value <= stack->head->next->minValue)
                                ? elem
                                : stack->head->next->minValue;
  }
};

void delElem(Stack *stack) {
  if (stack->head != nullptr) {
    Node *cur = stack->head->next;
    delete stack->head;
    stack->head = cur;
  }
}

int showMinElem(Stack *stack) { return stack->head->minValue; }

int main() {
  int operNum;
  cin >> operNum;

  Stack *stack = new Stack;

  int operType;
  int elem;

  for (int i = 0; i < operNum; ++i) {
    cin >> operType;
    switch (operType) {
      case 1:
        cin >> elem;
        pushElem(stack, elem);
        break;
      case 2:
        delElem(stack);
        break;
      case 3:
        cout << showMinElem(stack) << endl;
        break;
    }
  }

  return 0;
}
