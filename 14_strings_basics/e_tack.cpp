#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

size_t const P = 257;
size_t const MOD = (int)1e9 + 7;
size_t const MAX_LENGTH = 10'000;

long long getHash(const vector<long long> &hash, const vector<long long> &powp,
                  size_t left, size_t right) {
  return (0 < left) ? (hash[right] -
                       (hash[left - 1] * powp[right - left + 1]) % MOD + MOD) %
                          MOD
                    : hash[right];
}

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

int main() {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // считываю количество слов
  size_t strNum;
  cin >> strNum;

  size_t minLength = MAX_LENGTH;
  vector<string> stringCollection(strNum);
  vector<vector<long long>> hash(strNum);
  vector<vector<long long>> powp(strNum);

  for (size_t i = 0; i < strNum; ++i) {
    cin >> stringCollection[i];

    pair<vector<long long>, vector<long long>> hashAndPowp =
        buildPrefix(stringCollection[i]);
    hash[i] = hashAndPowp.first;
    powp[i] = hashAndPowp.second;

    minLength = min(minLength, stringCollection[i].size());
  }

  ssize_t left = 1;
  ssize_t right = minLength + 1;
  string subString;

  while (left < right) {
    bool isExist = false;
    ssize_t middle = (right + left) / 2;
    set<long long> common_hash;

    for (size_t i = 0; i < stringCollection[0].size() - middle + 1; ++i) {
      common_hash.insert(getHash(hash[0], powp[0], i, i + middle - 1));
    }

    for (size_t i = 1; i < stringCollection.size() - 1; ++i) {
      set<long long> tmp_hash;

      for (size_t k = 0; k < stringCollection[i].size() - middle + 1; ++k) {
        auto pos =
            common_hash.find(getHash(hash[i], powp[i], k, k + middle - 1));

        if (pos != common_hash.end()) {
          tmp_hash.insert(*pos);
        }
      }
      common_hash = tmp_hash;

      if (common_hash.empty()) {
        break;
      }
    }

    if (not common_hash.empty()) {
      size_t last = stringCollection.size() - 1;

      for (size_t i = 0; i < stringCollection[strNum - 1].size() - middle + 1;
           ++i) {
        auto pos = common_hash.find(
            getHash(hash[last], powp[last], i, i + middle - 1));

        if (pos != common_hash.end()) {
          subString = stringCollection[strNum - 1].substr(i, middle);
          isExist = true;
          break;
        }
      }
    }

    if (true == isExist) {
      left = middle + 1;
    } else {
      right = middle;
    }
  }

  cout << subString << '\n';

  return 0;
}
