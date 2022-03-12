#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> zFuncBuild(string const &str) {
  vector<int> z(str.length());
  int left = 0;
  int right = 0;

  for (int i = 1; i < str.length(); ++i) {
    z[i] = max(0, min(right - i, z[i - left]));

    while (i + z[i] < str.length() && str[z[i]] == str[i + z[i]]) {
      z[i]++;
    }

    if (i + z[i] > right) {
      left = i;
      right = i + z[i];
    }
  }
  return z;
}

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю строку
  string str;
  getline(cin, str);

  // считаю p
  vector<int> p = zFuncBuild(str);

  // вывожу p с нужными индексами
  for (int i = 1; i < str.length(); ++i) {
    cout << p[i] << ' ';
  }

  return 0;
}