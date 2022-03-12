#include <algorithm>
#include <iostream>

using namespace std;

class Queue {
  int *elements;
  int begin;
  int end;
  int capacity;

 public:
  Queue() {
    begin = 0;
    end = 0;
    capacity = 2;
    elements = new int[capacity];
  }

  int size() { return (end + capacity - begin) % capacity; }
  int next(int ind) { return (ind + 1) % capacity; }

  void changeElementsSize(int size_) {
    rotate(elements, elements + begin, elements + capacity);
    elements = (int *)realloc(elements, size_ * sizeof(int));
  }

  void pushBack(int elem) {
    if (next(end) == begin) {
      changeElementsSize(capacity * 2);

      end = size();
      begin = 0;
      capacity *= 2;
    }

    elements[end] = elem;
    end = next(end);
  }

  int pop() {
    int elem = elements[begin];
    begin = next(begin);

    if (size() < capacity / 4) {
      changeElementsSize(capacity / 2);

      end = size();
      begin = 0;
      capacity /= 2;
    }

    return elem;
  }
};

int main() {
  int operNum;
  cin >> operNum;

  Queue queue;

  for (int i = 0; i < operNum; ++i) {
    int elem;
    char sign;

    cin >> sign;

    switch (sign) {
      case '+':
        cin >> elem;
        queue.pushBack(elem);
        break;
      case '-':
        cout << queue.pop() << '\n';
        break;
    }
  }

  return 0;
}
