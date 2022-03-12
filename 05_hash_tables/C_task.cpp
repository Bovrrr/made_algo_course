#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int modules[] = {23,     47,     97,     197,    397,    797,
                       1597,   3203,   6421,   12853,  25717,  51437,
                       102877, 205759, 411527, 823117, 1646237};

struct quadr {
  string first;
  string second;

  quadr *next_ = nullptr;
  quadr *prev_ = nullptr;

  bool operator==(const quadr &other) {
    return (!first.compare(other.first) && !second.compare(other.second));
  }
};

class Map {
 public:
  int A;
  int capInd;
  int size;
  list<quadr> *elements;
  quadr *last;

  int hashFunc(string str, int module) {
    int res = 0;

    for (int i = 0; i < str.length(); ++i)
      res = (res * A + (int)str[i]) % module;

    return res;
  }

 public:
  void insert(quadr &newElem) {
    int index = hashFunc(newElem.first, modules[capInd]);

    for (quadr &elem : elements[index]) {
      if (not elem.first.compare(newElem.first)) {
        elem.second = newElem.second;
        return;
      }
    }

    elements[index].push_front(newElem);
    elements[index].front().prev_ = last;
    last = &(elements[index].front());
    ++size;
  }

  void remove(string remElem) {
    int index = hashFunc(remElem, modules[capInd]);
    for (quadr &elem : elements[index]) {
      if (not elem.first.compare(remElem)) {
        if (elem.prev_) elem.prev_->next_ = elem.next_;
        if (elem.next_) elem.next_->prev_ = elem.prev_;

        elements[index].remove(elem);
        --size;
        if (!size) {
          last = nullptr;
        }
        return;
      }
    }
  }

  Map() {
    A = 577;
    last = nullptr;
    capInd = 12;
    size = 0;
    elements = new list<quadr>[modules[capInd]];
  }

  string next(string str) {
    int index = hashFunc(str, modules[capInd]);
    for (quadr &elem : elements[index]) {
      if (not elem.first.compare(str) and elem.next_) return elem.next_->second;
    }

    return "none";
  }

  string prev(string str) {
    int index = hashFunc(str, modules[capInd]);
    for (quadr &elem : elements[index]) {
      if (not elem.first.compare(str) and elem.prev_) return elem.prev_->second;
    }

    return "none";
  }

  string get(string getElem) {
    int index = hashFunc(getElem, modules[capInd]);

    for (quadr &elem : elements[index]) {
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
    quadr elem = {strVec[1], strVec[2]};
    map.insert(elem);
  } else if (not strVec[0].compare("get")) {
    cout << map.get(strVec[1]) << endl;
  } else if (not strVec[0].compare("delete")) {
    map.remove(strVec[1]);
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
