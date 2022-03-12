#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void print_array(const vector<int> &arr);
void count_sort(vector<int> &arr);

int main() {
  string raw_data;
  getline(cin, raw_data);
  stringstream data(raw_data);
  vector<int> nums;
  int num;

  while (data >> num) {
    nums.push_back(num);
  }

  count_sort(nums);
  print_array(nums);

  return 0;
}

void print_array(const vector<int> &arr) {
  for (const int &num : arr) {
    cout << num << " ";
  }
}

void count_sort(vector<int> &arr) {
  int min_el = *min_element(begin(arr), end(arr));
  int max_el = *max_element(begin(arr), end(arr));
  int range = max_el - min_el + 1;
  vector<int> cnt(range, 0);

  for (int i = 0; i < arr.size(); ++i) cnt[arr[i] - min_el]++;

  int j = 0;

  for (int i = 0; i < range; ++i) {
    while (cnt[i] > 0) {
      arr[j++] = i + min_el;
      cnt[i]--;
    }
  }
}
