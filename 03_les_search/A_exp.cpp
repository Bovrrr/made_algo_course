#include <iostream>
#include <vector>

using namespace std;

void fill_array(vector<int> &arr) {
  for (int &el : arr) cin >> el;
}

int find_nearest_el(vector<int> &arr, int el) {
  // ивариант (l, r]
  int left = -1;
  int right = arr.size();

  while (left < right - 1) {
    int m = (left + right) / 2;

    if (arr[m] == el)
      return arr[m];
    else if (arr[m] < el)
      left = m;
    else if (arr[m] > el)
      right = m;
  }

  if (left < 0) left = 0;
  if (right == arr.size()) right = arr.size() - 1;

  return abs(el - arr[left]) <= abs(el - arr[right]) ? arr[left] : arr[right];
}

int main() {
  int arr_size, requests_num;
  cin >> arr_size >> requests_num;

  vector<int> arr(arr_size);
  vector<int> requests(requests_num);

  fill_array(arr);
  fill_array(requests);

  for (int &el : requests) cout << find_nearest_el(arr, el) << endl;

  return 0;
}