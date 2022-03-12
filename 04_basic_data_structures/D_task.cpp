#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Heap {
 public:
  pair<int, int> *elements = new pair<int, int>[1000000];
  int size = 0;

  void insert(pair<int, int> &elems) {
    int i = size;
    elements[size++] = elems;

    while (i > 0 and elements[i].first < elements[i - 1].first) {
      swap(elements[i], elements[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  pair<int, int> removeMin() {
    pair<int, int> ans = elements[0];
    swap(elements[0], elements[--size]);
    int i = 0;

    while (2 * i + 1 < size) {
      pair<int, int> cur = elements[i];
      pair<int, int> left = elements[2 * i + 1];
      pair<int, int> right;
      if (2 * i + 2 >= size) {
        right.first = 2e9;
        right.second = 0;
      } else {
        right = elements[2 * i + 2];
      }

      if (left.first < right.first and left.first < cur.first) {
        swap(elements[i], elements[2 * i + 1]);
        i = 2 * i + 1;
      } else if (cur.first > right.first) {
        swap(elements[i], elements[2 * i + 2]);
        i = 2 * i + 2;
      } else {
        break;
      }
    }

    return ans;
  }

  void decrease(int operNum, int var) {
    int i = 0;
    for (i = 0; i < size; ++i) {
      if (operNum == elements[i].second) {
        elements[i].first = var;
        break;
      }
    }

    while (i % size != 0 and elements[i].first < elements[(i - 1) / 2].first) {
      swap(elements[i], elements[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }
};

vector<string> split(string str_to_split, char delim) {
  stringstream ss(str_to_split);
  string item;
  vector<string> splitted_strings;

  while (getline(ss, item, delim)) splitted_strings.push_back(item);

  return splitted_strings;
}

vector<string> strings{"push", "extract-min", "decrease-key"};

void func(Heap &heap, string &str, int &operNum) {
  if (not str.compare(strings[0])) {
    pair<int, int> elem;
    cin >> elem.first;
    elem.second = operNum;
    heap.insert(elem);
  } else if (not str.compare(strings[1])) {
    if (heap.size == 0) {
      cout << '*' << endl;
    } else {
      pair<int, int> elem = heap.removeMin();
      cout << elem.first << " " << elem.second << endl;
    }
  } else if (not str.compare(strings[2])) {
    int opNum, value;
    cin >> opNum >> value;
    heap.decrease(opNum, value);
  }
}

int main() {
  string str;
  Heap heap;
  int operNum = 0;

  while (getline(cin, str, ' ')) {
    ++operNum;
    func(heap, str, operNum);
  }

  return 0;
}
