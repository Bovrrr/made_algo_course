#include <iostream>
#include <map>
#include <string>

using namespace std;
using ull = unsigned long long;

ull count_all(const string &word, const map<char, size_t> &origin) {
  ull ans = 0;
  map<char, size_t> substring;
  size_t substring_len = 0;

  for (size_t i = 0; i < word.length(); ++i) {
    if (!origin.count(word[i])) {  // if there is no such letter at all
      substring.clear();
      substring_len = 0;
      continue;
    }

    if (substring[word[i]] + 1 <= origin.at(word[i])) {
      substring[word[i]]++;
      substring_len++;
      ans += substring_len;
    } else {
      substring[word[i - substring_len]]--;  // i - substring_len is a first
                                             // letter taken
      substring_len--;
      i--;
    }
  }
  return ans;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  string word, cards;
  cin >> word >> cards;

  map<char, size_t> origin;

  for (const char &card : cards) origin[card]++;

  cout << count_all(word, origin);

  return 0;
}