#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<char> take_pos_column(const vector<string> &words, int pos) {
  vector<char> pos_column;

  for (const auto &word : words) pos_column.push_back(word[pos]);

  return pos_column;
}

vector<string> sort(vector<string> &words, int threshold, int pos) {
  if (pos < threshold) return words;

  vector<char> pos_column = take_pos_column(words, pos);
  char min = *min_element(begin(pos_column), end(pos_column));
  char max = *max_element(begin(pos_column), end(pos_column));
  int range = max - min + 1;

  vector<vector<string>> counters(range);

  for (int i = words.size() - 1; i >= 0; --i)
    counters[words[i][pos] - min].push_back(words[i]);

  int j = 0;

  for (int i = 0; i < range; ++i)
    while (counters[i].size() > 0) {
      words[j++] = counters[i].back();
      counters[i].pop_back();
    }

  return sort(words, threshold, pos - 1);
}

int main() {
  int words_cnt;
  int length;
  int iterations;

  cin >> words_cnt >> length >> iterations;

  vector<string> words(words_cnt);

  for (string &word : words) cin >> word;

  for (const string &word : sort(words, length - iterations, length - 1))
    cout << word << '\n';

  return 0;
}