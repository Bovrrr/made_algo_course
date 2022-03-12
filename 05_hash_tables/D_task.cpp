#include <iostream>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

const int modules[] = {23,     47,     97,     197,    397,    797,
                       1597,   3203,   6421,   12853,  25717,  51437,
                       102877, 205759, 411527, 823117, 1646237};

string const EMPTY = "*";
string const RIP = "#";

class Set {
 public:
  string *elements = nullptr;
  int size;
  int ripCnt;
  int capInd;

  int hashFunc(string str, int module) {
    int res = 0;
    int A = 577;
    for (int i = 0; i < str.length(); ++i)
      res = (res * A + (int)str[i]) % module;

    return res;
  }

  int next(int index, int module) { return (index + 1) % module; }

  void empty(string *elements_, int size_) {
    for (int i = 0; i < size_; ++i) elements_[i] = EMPTY;
  }

  void changeSetSize(bool increase) {
    int newCapInd = increase ? capInd + 1 : capInd - 1;

    if (-1 == newCapInd) return;

    size = 0;
    ripCnt = 0;

    string *elements_ = new string[modules[newCapInd]];
    empty(elements_, modules[newCapInd]);
    for (int i = 0; i < modules[capInd]; ++i) {
      if (elements[i].compare(RIP) && elements[i].compare(EMPTY))
        insert(elements[i], elements_, modules[newCapInd]);
    }

    string *temp = elements;
    elements = elements_;
    delete[] temp;

    capInd = newCapInd;
  }

  void insert(string elem, string *elements_, int module) {
    int index = hashFunc(elem, module);

    while (elements_[index].compare(EMPTY)) {
      if (not elements_[index].compare(elem)) return;

      index = next(index, module);
    }

    elements_[index] = elem;
    ++size;
  }

  void remove(string elem) {
    for (int i = hashFunc(elem, modules[capInd]); elements[i] != EMPTY;
         i = next(i, modules[capInd])) {
      if (not elements[i].compare(elem)) {
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
    elements = new string[modules[capInd]];

    empty(elements, modules[capInd]);
  }

  void add(string elem) {
    if (size + ripCnt < modules[capInd] / 2) {
      insert(elem, elements, modules[capInd]);
    } else {
      changeSetSize(true);
      insert(elem, elements, modules[capInd]);
    }
  }

  void erase(string elem) {
    if (!exists(elem)) return;

    if (size >= modules[capInd] / 8) {
      remove(elem);
    } else {
      remove(elem);
      changeSetSize(false);
    }
  }

  bool exists(string elem) {
    for (int index = hashFunc(elem, modules[capInd]);
         elements[index].compare(EMPTY); index = next(index, modules[capInd])) {
      if (not elem.compare(elements[index])) return true;
    }

    return false;
  }
};

class Map {
  int capInd;
  int size;
  list<pair<string, Set>> *elements;

  int hashFunc(string str, int module) {
    int res = 0;
    int A = 607;
    for (int i = 0; i < str.length(); ++i)
      res = (res * A + (int)str[i]) % module;

    return res;
  }

 public:
  Map() {
    capInd = 0;
    size = 0;
    elements = new list<pair<string, Set>>[modules[capInd]];
  }

  void insert(pair<string, string> &newElem) {
    int index = hashFunc(newElem.first, modules[capInd]);

    for (pair<string, Set> &elem : elements[index]) {
      if (not elem.first.compare(newElem.first)) {
        elem.second.add(newElem.second);
        return;
      }
    }
    Set newSet;
    pair<string, Set> newPair = {newElem.first, newSet};
    newSet.add(newElem.second);
    elements[index].push_front(newPair);
    ++size;
  }

  void removeElem(string remElem) {
    int index = hashFunc(remElem, modules[capInd]);
    for (pair<string, Set> &elem : elements[index]) {
      if (not elem.first.compare(remElem)) {
        elem.second.erase(remElem);
        --size;
        return;
      }
    }
  }

  void removeAll(string remElem) {
    int index = hashFunc(remElem, modules[capInd]);
    for (pair<string, Set> &elem : elements[index]) {
      if (not elem.first.compare(remElem)) {
        size -= elem.second.size;
        elements[index].remove(elem);
        return;
      }
    }
  }

  string get(string getElem) {
    int index = hashFunc(getElem, modules[capInd]);

    for (pair<string, Set> &elem : elements[index]) {
      if (not elem.first.compare(getElem)) {
        cout << elem.second.size << '\n';
        for (int i = 0; i < elem.second.size; ++i) {
          if (not RIP.compare(elem.second.elements[i]) and
              not EMPTY.compare(elem.second.elements[i]))
            cout << elem.second.elements[i] << '\n';
        }
        return "";
      }
    }

    return "none";
  }
};

vector<string> split(const string &str) {
  stringstream ss(str);
  string word;
  vector<string> strVec;

  while (getline(ss, word, ' ')) strVec.push_back(word);

  return strVec;
}

void solve(string &line, Map &map) {
  vector<string> strVec = split(line);

  if (not strVec[0].compare("put")) {
    pair<string, string> newElem = {strVec[1], strVec[2]};
    map.insert(newElem);
  } else if (not strVec[0].compare("get")) {
    cout << map.get(strVec[1]);
  } else if (not strVec[0].compare("delete")) {
    map.removeElem(strVec[1]);
  } else if (not strVec[0].compare("deleteAll")) {
    map.removeAll(strVec[1]);
  }
}

int main() {
  Map map;
  string line;

  while (getline(cin, line)) {
    solve(line, map);
  }

  return 0;
}