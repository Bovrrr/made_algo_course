#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int const modules[] = {23,     47,     97,     197,    397,    797,
                       1597,   3203,   6421,   12853,  25717,  51437,
                       102877, 205759, 411527, 823117, 1646237};

class Map {
  int capInd;
  int size;
  list<pair<string, string>> *elements;
  int const A = 607;

  int hashFunc(string str, int module) {
    int res = 0;
    for (int i = 0; i < str.length(); ++i)
      res = (res * A + (int)str[i]) % module;

    return res;
  }

  void insert(pair<string, string> &newElem,
              list<pair<string, string>> *elements_, int capInd_) {
    int index = hashFunc(newElem.first, modules[capInd_]);

    for (pair<string, string> &elem : elements_[index]) {
      if (not elem.first.compare(newElem.first)) {
        elem.second = newElem.second;
        return;
      }
    }

    elements_[index].push_front(newElem);
    ++size;
  }

  void remove(string remElem) {
    int index = hashFunc(remElem, modules[capInd]);
    for (pair<string, string> &elem : elements[index]) {
      if (not elem.first.compare(remElem)) {
        elements[index].remove(elem);
        --size;
        return;
      }
    }
  }

  void changeMapSize(bool increase) {
    ssize_t newCapInd = increase ? capInd + 1 : capInd - 1;

    if (-1 == newCapInd) return;

    size = 0;

    list<pair<string, string>> *elements_ =
        new list<pair<string, string>>[modules[newCapInd]];
    for (int i = 0; i < modules[capInd]; ++i) {
      for (pair<string, string> &elem : elements[i]) {
        insert(elem, elements_, newCapInd);
      }
    }

    list<pair<string, string>> *temp = elements;
    elements = elements_;
    delete[] temp;

    capInd = newCapInd;
  }

 public:
  Map() {
    capInd = 0;
    size = 0;
    elements = new list<pair<string, string>>[modules[capInd]];
  }

  void add(pair<string, string> newElem) {
    if (size < modules[capInd] * 3) {
      insert(newElem, elements, capInd);
    } else {
      changeMapSize(true);
      insert(newElem, elements, capInd);
    }
  }

  void erase(string remElem) {
    if (size > modules[capInd] / 2) {
      remove(remElem);
    } else {
      remove(remElem);
      changeMapSize(false);
    }
  }

  string get(string getElem) {
    int index = hashFunc(getElem, modules[capInd]);

    for (pair<string, string> &elem : elements[index]) {
      if (not elem.first.compare(getElem)) {
        return elem.second;
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
    pair<string, string> elem = {strVec[1], strVec[2]};
    map.add(elem);
  } else if (not strVec[0].compare("get")) {
    cout << map.get(strVec[1]) << endl;
  } else if (not strVec[0].compare("delete")) {
    map.erase(strVec[1]);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  Map map;
  string line;

  while (getline(cin, line)) {
    solve(line, map);
  }

  return 0;
}
