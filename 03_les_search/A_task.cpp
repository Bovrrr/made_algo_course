#include <iostream>
#include <vector>

using namespace std;

void fill_array(vector<int> &arr) {
  for (int &el : arr) cin >> el;
}

int find_nearest_el(vector<int> &arr, int el) {
  int left = -1;
  int right = arr.size() - 1;

  while (left < right - 1) {
    int mid = (left + right) / 2;

    if (arr[mid] < el)
      left = mid;
    else if (arr[mid] > el)
      right = mid;
    else
      return arr[mid];
  }

  left = (left < 0) ? 0 : left;

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
