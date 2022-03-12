#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool charIsDigit(char const elem) {
  return (elem - '0' >= 0 && elem - '0' < 10);
}

bool charIsBracket(char const elem) { return ('(' == elem || ')' == elem); }

bool charIsSign(char const elem) {
  return ('+' == elem || '-' == elem || '*' == elem);
}

void parse_expr(string &raw_expr, vector<string> &token_collection) {
  string cur_num = "";

  for (size_t i = 0; i < raw_expr.length() - 1; ++i) {
    if (charIsBracket(raw_expr[i]) || charIsSign(raw_expr[i])) {
      token_collection.push_back(string(1, raw_expr[i]));
    } else if (charIsDigit) {
      cur_num.push_back(raw_expr[i]);

      if (!charIsDigit(raw_expr[i + 1])) {
        token_collection.push_back(cur_num);
        cur_num = "";
      }
    }
  }
}

int main(void) {
  // быстрый ввод
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<string> token_collection;
  string raw_string;
  getline(cin, raw_string);

  parse_expr(raw_string, token_collection);
  for (string &str : token_collection) {
    cout << str << '\n';
  }

  return 0;
}