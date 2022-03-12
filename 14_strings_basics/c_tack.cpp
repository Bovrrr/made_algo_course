#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> pFunc(string const &str) {
  vector<int> p(str.length(), 0);

  for (int i = 1; i < str.length(); ++i) {
    int k = p[i - 1];

    while (k > 0 && str[i] != str[k]) {
      k = p[k - 1];
    }

    p[i] = (str[i] == str[k]) ? k + 1 : k;
  }

  return p;
}

vector<int> kmp(string const &substr, string const &str) {
  string bigString = substr + '#' + str;

  int substrLength = substr.length();
  int strLength = str.length();

  vector<int> result;
  vector<int> p = pFunc(bigString);

  for (int i = 0; i < strLength; ++i) {
    if (substrLength == p[substrLength + i + 1]) {
      result.push_back(i);
    }
  }

  return result;
}

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю подстроку и строку
  string str, substr;
  getline(cin, substr);
  getline(cin, str);

  vector<int> answer = kmp(substr, str);

  cout << answer.size() << '\n';
  for (int &ind : answer) {
    cout << ind - substr.length() + 2 << ' ';
  }

  return 0;
}