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
  int const A = 577;
  int const P = 2440003;
  int *elements = nullptr;
  int size;
  int ripCnt;
  int capInd;

  int hashFunc(int elem, int module) {
    return (0 > elem) ? (A * (elem % P)) % module + module
                      : (A * (elem % P)) % module;
  }

  int next(int index, int module) { return (index + 1) % module; }

  void empty(int *elements_, int size_) {
    for (int i = 0; i < size_; ++i) elements_[i] = EMPTY;
  }

  void changeSetSize(bool increase) {
    int newCapInd = increase ? capInd + 1 : capInd - 1;

    if (-1 == newCapInd) return;

    size = 0;
    ripCnt = 0;

    int *elements_ = new int[modules[newCapInd]];
    empty(elements_, modules[newCapInd]);
    for (int i = 0; i < modules[capInd]; ++i) {
      if (elements[i] != RIP && elements[i] != EMPTY)
        insert(elements[i], elements_, modules[newCapInd]);
    }

    int *temp = elements;
    elements = elements_;
    delete[] temp;

    capInd = newCapInd;
  }

  void insert(int elem, int *elements_, int module) {
    int index = hashFunc(elem, module);

    while (elements_[index] != EMPTY) {
      if (elements_[index] == elem) return;

      index = next(index, module);
    }

    elements_[index] = elem;
    ++size;
  }

  void remove(int elem) {
    for (int i = hashFunc(elem, modules[capInd]); elements[i] != EMPTY;
         i = next(i, modules[capInd])) {
      if (elements[i] == elem) {
        elements[i] = RIP;
        --size;
        ++ripCnt;
        return;
      }
    }
  }

 public:
  Set() {
    size = 0;
    ripCnt = 0;
    capInd = 0;
    elements = new int[modules[capInd]];

    empty(elements, modules[capInd]);
  }

  void add(int elem) {
    if (size + ripCnt < modules[capInd] / 2) {
      insert(elem, elements, modules[capInd]);
    } else {
      changeSetSize(true);
      insert(elem, elements, modules[capInd]);
    }
  }

  void erase(int elem) {
    if (!exists(elem)) return;

    if (size >= modules[capInd] / 8) {
      remove(elem);
    } else {
      remove(elem);
      changeSetSize(false);
    }
  }

  bool exists(int elem) {
    for (int index = hashFunc(elem, modules[capInd]); elements[index] != EMPTY;
         index = next(index, modules[capInd])) {
      if (elem == elements[index]) return true;
    }

    return false;
  }
};

vector<string> split(const string &str) {
  stringstream ss(str);
  string word;
  vector<string> stringArray;

  while (getline(ss, word, ' ')) stringArray.push_back(word);

  return stringArray;
}

void solve(string &line, Set &set) {
  vector<string> strVec = split(line);

  if (not strVec[0].compare("insert"))
    set.add(stoi(strVec[1]));
  else if (not strVec[0].compare("exists"))
    set.exists(stoi(strVec[1])) ? cout << "true" << '\n'
                                : cout << "false" << '\n';
  else if (not strVec[0].compare("delete"))
    set.erase(stoi(strVec[1]));
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  Set set;
  string line;

  while (getline(cin, line)) solve(line, set);

  return 0;
}
