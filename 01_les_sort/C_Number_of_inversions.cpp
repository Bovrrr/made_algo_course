#include <cstring>
#include <iostream>

using namespace std;

void fill_array(int *arr, int size);
unsigned long long int merge(int *arr, int *arr_left, int *arr_right,
                             int size_left, int size_right);
unsigned long long int merge_sort(int *arr, int size);

int main() {
  int numbers_amount = 0;
  cin >> numbers_amount;

  int *arr = new int[numbers_amount];
  fill_array(arr, numbers_amount);

  unsigned long long int ans = merge_sort(arr, numbers_amount);
  cout << ans;

  return 0;
}

void fill_array(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    cin >> arr[i];
  }
}

unsigned long long int merge(int *arr, int *arr_left, int *arr_right,
                             int size_left, int size_right) {
  int i = 0;
  int j = 0;
  unsigned long long int cnt = 0;

  while (i + j < size_left + size_right) {
    if (j == size_right || (i < size_left && arr_left[i] < arr_right[j])) {
      arr[i + j] = arr_left[i];
      ++i;
    } else {
      arr[i + j] = arr_right[j];
      ++j;
      cnt += size_left - i;
    }
  }

  return cnt;
}

unsigned long long int merge_sort(int *arr, int size) {
  if (size == 1) {
    return 0;
  }

  int l_size = size / 2;
  int r_size = size - l_size;

  int *left_subarray = new int[l_size];
  int *right_subarray = new int[r_size];

  left_subarray = (int *)memcpy(left_subarray, arr, l_size * sizeof(int));
  right_subarray =
      (int *)memcpy(right_subarray, arr + l_size, r_size * sizeof(int));

  return merge_sort(left_subarray, l_size) +
         merge_sort(right_subarray, r_size) +
         merge(arr, left_subarray, right_subarray, l_size, r_size);
}
