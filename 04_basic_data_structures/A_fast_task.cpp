#include <iostream>

using namespace std;

struct Node {
  int value;
  Node *next = nullptr;

  Node(int value, Node *next = nullptr) {
    this->value = value;
    this->next = next;
  }
};

struct Stack {
  Node *head = nullptr;
};

void pushElem(Stack *stack, int &elem) {
  if (stack->head) {
    int prev = stack->head->value;
    stack->head = new Node(elem < prev ? elem : prev, stack->head);
  } else
    stack->head = new Node(elem);
};

void delElem(Stack *stack) {
  Node *cur = stack->head->next;
  delete stack->head;
  stack->head = cur;
}

void delStack(Stack *stack) {
  while (stack->head) delElem(stack);
  delete stack;
  stack = nullptr;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

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
        cout << stack->head->value << '\n';
        break;
    }
  }

  delStack(stack);

  return 0;
}
