#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int const EMPTY = (int)2e9;
int const RIP = (int)-2e9;

const int modules[] = {23,     47,     97,     197,    397,    797,
                       1597,   3203,   6421,   12853,  25717,  51437,
                       102877, 205759, 411527, 823117, 1646237};

class Set {
 public:
  int *elements = nullptr;
  int size;
  int ripCnt;
  int capInd;
  int changeCoef;

  void remove(int elem) {
    for (int i = hashFunc(elem, modules[capInd]); elements[i] != EMPTY;
         i = next(i)) {
      if (elements[i] == elem) {
        elements[i] = RIP;
        --size;
        ++ripCnt;
        return;
      }
    }
  }

  void insert(int *elements_, int elem, int module) {
    int i = hashFunc(elem, module);
    while (elements_[i] != EMPTY) {
      if (elements_[i] == elem) {
        return;
      }

      i = next(i);
    }

    elements_[i] = elem;
    ++size;
  }

  void changeSetSize(int new_capacity) {
    size = 0;

    int *elements_ = new int[new_capacity];
    empty(elements_, new_capacity);

    for (int i = 0; i < capacity; ++i) {
      if (elements[i] != RIP and elements[i] != EMPTY) {
        insert(elements_, elements[i], new_capacity);
      }
    }

    int *temp = elements;
    elements = elements_;
    delete[] temp;

    capacity = new_capacity;
    ripCnt = 0;
  }

  int next(int index) { return (index + 1) % modules[capInd]; }

  int hashFunc(int elem, int module) { return abs(elem) % module; }

  void empty(int *array, int size_) {
    for (int i = 0; i < size_; ++i) array[i] = EMPTY;
  }

 public:
  Set() {
    size = 0;
    ripCnt = 0;
    capInd = 0;
    changeCoef = 2;
    elements = new int[modules[capInd]];

    empty(elements, modules[capInd]);
  }

  void add(int elem) {
    if (ripCnt + size < modules[capInd] / changeCoef) {
      insert(elements, elem, modules[capInd]);
    } else {
      changeSetSize(modules[capInd] * changeCoef);
      insert(elements, elem, modules[capInd]);
    }
  }

  void erase(int elem) {
    if (size >= modules[capInd] / (changeCoef * 4)) {
      remove(elem);
    } else {
      remove(elem);
      changeSetSize(modules[capInd] / changeCoef);
    }
  }

  bool exists(int elem) {
    for (int i = hashFunc(elem, modules[capInd]); elements[i] != EMPTY;
         i = next(i)) {
      if (elem == elements[i]) {
        return true;
      }
    }

    return false;
  }
};

string arr[] = {"insert", "delete", "exists"};

void printArr(int *array, int size) {
  for (int i = 0; i < size; ++i) cout << array[i] << ' ';
  cout << endl;
}

vector<string> split(const string &str) {
  stringstream ss(str);
  string word;
  vector<string> stringArray;

  while (getline(ss, word)) stringArray.push_back(word);

  return stringArray;
}

void solve(Set &set, string &line) {
  int elem;
  cin >> elem;

  if (line.find(arr[0]) != string::npos)
    set.add(elem);
  else if (line.find(arr[1]) != string::npos)
    set.erase(elem);
  else if (line.find(arr[2]) != string::npos)
    (set.exists(elem)) ? cout << "true" << endl : cout << "false" << endl;
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  Set set;
  string command;

  while (cin >> command) {
    // printArr(set.elements, set.capacity);
    solve(set, command);
    // printArr(set.elements, set.capacity);
  }

  return 0;
}
