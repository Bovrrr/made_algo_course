#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ull = unsigned long long;
const int LAT_SYM_AMOUNT = 26;

ull count_all(const string &word, const vector<int> &origin) {
  ull ans = 0;
  vector<int> substring(LAT_SYM_AMOUNT, 0);
  size_t substring_len = 0;

  for (size_t i = 0; i < word.length(); ++i) {
    if (!origin[word[i] - 'a']) {
      substring = vector<int>(LAT_SYM_AMOUNT, 0);
      substring_len = 0;
      continue;
    }

    if (substring[word[i] - 'a'] + 1 <= origin[word[i] - 'a']) {
      substring[word[i] - 'a']++;
      substring_len++;
      ans += substring_len;
    } else {
      substring[word[i - substring_len] - 'a']--;
      substring_len--;
      i--;
    }
  }
  return ans;
}

int main() {
  int n, m;
  cin >> n >> m;
  string word, cards;
  cin >> word >> cards;

  vector<int> origin(LAT_SYM_AMOUNT);

  for (const char &card : cards) origin[card - 'a']++;

  cout << count_all(word, origin);

  return 0;
}