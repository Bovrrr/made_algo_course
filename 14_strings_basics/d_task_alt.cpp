#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
 private:
  int const ALPH_SIZE = 26;
  int size;
  vector<vector<int>> next;
  vector<int> distFromRoot;

 public:
  Trie(int wordNum) : size(1) {
    next.resize(1);
    next[0].resize(ALPH_SIZE, 0);
    distFromRoot.resize(wordNum, -1);
  }

  void insert(string &str, int wordNum) {
    int dist = 0;

    for (char &ch : str) {
      ch -= 'a';

      if (next[dist][ch] == 0) {
        next[dist][ch] = size++;
      }

      if (next.size() < size) {
        vector<int> nextLevelVec(ALPH_SIZE, 0);
        next.push_back(nextLevelVec);
      }
      dist = next[dist][ch];
    }

    distFromRoot.resize(dist + 1, -1);
    distFromRoot[dist] = wordNum;
  }

  vector<int> getSubstring(string const &str, int left) {
    int dist = 0;
    vector<int> result;

    for (int i = left; i < str.size(); ++i) {
      char ch = str[i];
      ch -= 'a';

      if (0 == next[dist][ch]) {
        break;
      }

      dist = next[dist][ch];

      if (-1 != distFromRoot[dist]) {
        result.push_back(distFromRoot[dist]);
      }
    }
    return result;
  }
};

vector<bool> getResult(int const &wordNum, string const &text, Trie &trie) {
  vector<bool> result(wordNum, false);

  for (int i = 0; i < text.size(); ++i) {
    for (int const &element : trie.getSubstring(text, i)) {
      result[element] = true;
    }
  }

  return result;
}

void printResult(vector<bool> const &result) {
  for (bool const &element : result) {
    switch (element) {
      case true:
        cout << "Yes" << '\n';
        break;

      case false:
        cout << "No" << '\n';
        break;
    }
  }
}

int main() {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю текст
  string text;
  cin >> text;

  // считываю количество слов
  int wordNum;
  cin >> wordNum;

  // инстаншу и инициализирую бор
  Trie trie = Trie(wordNum);
  string word;

  // считываю и заполняю бор
  for (int i = 0; i < wordNum; ++i) {
    cin >> word;
    trie.insert(word, i);
  }

  vector<bool> result = getResult(wordNum, text, trie);

  // вывожу ответы
  printResult(result);

  return 0;
}