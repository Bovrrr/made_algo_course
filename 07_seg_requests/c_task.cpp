#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

ssize_t get_prev(ssize_t ind) { return (ind & (ind + 1)); }

ssize_t get_next(ssize_t ind) { return (ind | (ind + 1)); }

long long int get(ssize_t ind, vector<long long int> &T) {
  long long res;
  for (res = 0; ind >= 0; ind = get_prev(ind) - 1) {
    res += T[ind];
  }

  return res;
}

long long int rsq(ssize_t left, ssize_t right, vector<long long int> &T) {
  return (left == 0) ? get(right, T) : (get(right, T) - get(left - 1, T));
}

void add(ssize_t ind, long long int value, vector<long long int> &T) {
  for (ssize_t j = ind; j < T.size(); j = get_next(j)) {
    T[j] += value;
  }
}

void set(ssize_t ind, long long int value, vector<long long int> &arr,
         vector<long long int> &T) {
  long long dif = value - arr[ind];
  arr[ind] = value;
  add(ind, dif, T);
}

vector<string> split(const string &str) {
  stringstream ss(str);
  string word;
  vector<string> strVec;

  while (getline(ss, word, ' ')) strVec.push_back(word);

  return strVec;
}

void solve(string &line, vector<long long int> &arr, vector<long long int> &T) {
  vector<string> strVec = split(line);

  if (not strVec[0].compare("sum")) {
    cout << rsq(stoi(strVec[1]) - 1, stoi(strVec[2]) - 1, T) << '\n';
  } else if (not strVec[0].compare("set")) {
    set(stoi(strVec[1]) - 1, stoll(strVec[2]), arr, T);
  }
}

int main(void) {
  // для быстрых ввода/вывода
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  // заполняю массив
  ssize_t arrSize;
  cin >> arrSize;

  vector<long long int> T(arrSize, 0);

  vector<long long int> arr(arrSize, 0);
  long long curElem = 0;
  for (ssize_t ind = 0; ind < arrSize; ++ind) {
    cin >> curElem;
    set(ind, curElem, arr, T);
  }

  string line;
  getline(cin, line);
  while (getline(cin, line)) {
    solve(line, arr, T);
  }

  return 0;
}
