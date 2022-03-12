#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void fill_array(vector<int> &arr) {
  for (int &el : arr) cin >> el;
}

int lower_bound(vector<int> &arr, int el) {
  int left = -1;
  int right = arr.size();
  int m = 0;

  while (left < right - 1) {
    m = left + (right - left) / 2;

    if (el <= arr[m])
      right = m;
    else
      left = m;
  }

  return right;
}

int main() {
  int arr_size, requests_num;
  cin >> arr_size;

  vector<int> arr(arr_size);
  fill_array(arr);
  sort(arr.begin(), arr.end());

  int req_num;
  cin >> req_num;

  vector<int> answers(req_num);

  int left, right;
  for (int i = 0; i < req_num; ++i) {
    cin >> left >> right;
    answers[i] = lower_bound(arr, right + 1) - lower_bound(arr, left);
  }

  for (const int &el : answers) cout << el << " ";

  return 0;
}