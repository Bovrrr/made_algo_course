#include <iostream>
#include <string>
#include <vector>

using namespace std;

// константы
int const MOD = 1000000007;
int const P = 257;

pair<vector<long long int>, vector<long long int>> buildPrefix(
    string const &str) {
  vector<long long int> hash(str.length(), str[0]);
  vector<long long int> powp(str.length(), 1);

  for (size_t i = 1; i < str.length(); ++i) {
    hash[i] = (hash[i - 1] * P + str[i]) % MOD;
    powp[i] = (powp[i - 1] * P) % MOD;
  }

  return {hash, powp};
}

int getHash(size_t const &a, size_t const &b, vector<long long int> &hash,
            vector<long long int> &powp) {
  return (0 == a)
             ? hash[b]
             : (hash[b] - (hash[a - 1] * powp[b - a + 1]) % MOD + MOD) % MOD;
}

void solve(size_t const &a, size_t const &b, size_t const &c, size_t const &d,
           vector<long long int> &hash, vector<long long int> &powp) {
  bool isEqual = (getHash(a, b, hash, powp) == getHash(c, d, hash, powp));

  cout << getHash(a, b, hash, powp) << ' ' << getHash(c, d, hash, powp) << endl;

  switch (isEqual) {
    case true:
      cout << "Yes" << '\n';
      break;

    case false:
      cout << "No" << '\n';
      break;
  }
}

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю строку
  string str;
  getline(cin, str);

  // считываю количество запросов
  size_t requestNumber;
  cin >> requestNumber;

  // строю хеши префиксов
  pair<vector<long long int>, vector<long long int>> hashAndPowp =
      buildPrefix(str);

  // for (long long int el : hashAndPowp.first)
  //{
  //    cout << el << ' ';
  //}
  // cout << endl;
  // for (long long int el : hashAndPowp.second)
  //{
  //    cout << el << ' ';
  //}
  // cout << endl;

  // считываю запросы и отвечаю на них
  size_t a, b, c, d;
  for (size_t i = 0; i < requestNumber; ++i) {
    cin >> a >> b >> c >> d;
    solve(--a, --b, --c, --d, hashAndPowp.first, hashAndPowp.second);
  }

  return 0;
}