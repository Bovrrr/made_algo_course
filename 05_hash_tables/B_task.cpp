#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Map {
  LinkedList *elements = nullptr;
  int size;
  int capacity;

  size_t hashFunc(string str) {
    int res;

    return res;
  }

 public:
  Map() {
    size = 0;
    capacity = 8;
    elements = new LinkedList[capacity];
  }

  void add() {}
};

class Node {
 public:
  string value;
  Node *next;

  Node() { next = nullptr; }

  Node(string value_, Node *next_) {
    value = value_;
    next = next_;
  }
};

class LinkedList {
  Node *head;
  int size;

 public:
  LinkedList() {
    head = nullptr;
    size = 0;
  }

  bool elemExists(string elem) {
    bool elemExists = false;
    Node *cur = head->next;
    while (cur) {
      if (cur->value == elem) {
        elemExists = true;
      }
    }

    return elemExists;
  }

  string get(string elem) {
    Node *cur = head->next;
    while (cur) {
      if (cur->value == elem) {
        return cur->value;
      }
    }
  }

  void add(string elem) {
    if (not head) {
      if (not elemExists(elem)) {
        Node *new_elem = new Node(elem, head->next);
        head->next = new_elem;
        ++size;
      }
    } else {
      head->next = new Node(elem, nullptr);
      ++size;
    }
  }

  void remove(string elem) {
    if (elemExists(elem)) {
      Node *prevCur = head;
      Node *cur = head->next;

      while (cur) {
        if (cur->value == elem) {
          prevCur->next = cur->next;
          delete cur;
        }

        prevCur = cur;
        cur = cur->next;
      }
    }
  }

  void deleteList() {
    while (head) {
      Node *cur = head;
      head = head->next;
      delete cur;
    }
  }
};

vector<string> split(const string &str) {
  stringstream ss(str);

  string word;
  vector<string> stringArray;
  while (getline(ss, word)) {
    stringArray.push_back(word);
  }

  return stringArray;
}

void solve() {
  string line;
  vector<string> strVec;
  while (getline(cin, line)) {
    strVec = split(line);
    if (not strVec[0].compare("put")) {
      // add elem
    } else if (not strVec[0].compare("get")) {
      // get elem
    } else if (not strVec[0].compare("delete")) {
      // delete elem
    }
  }
}

int main() {
  solve();

  return 0;
}