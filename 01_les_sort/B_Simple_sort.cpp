#include <iostream>

using namespace std;

void fill_array(int *arr, int size);
void print_array(int *arr, int size);
int *merge_sort(int *arr, int size);
int *merge(int *arr_left, int *arr_right, int size_left, int size_right);

int main() {
  int numbers_amount = 0;
  cin >> numbers_amount;

  int *arr = new int[numbers_amount];
  fill_array(arr, numbers_amount);

  int *arr_new = merge_sort(arr, numbers_amount);
  delete[] arr;
  print_array(arr_new, numbers_amount);

  return 0;
}

void fill_array(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    cin >> arr[i];
  }
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    cout << arr[i] << " ";
  }
}

int *merge(int *arr_left, int *arr_right, int size_left, int size_right) {
  int i = 0;
  int j = 0;
  int *arr_c = new int[size_left + size_right];

  while (i + j < size_left + size_right) {
    if (j == size_right || (i < size_left && arr_left[i] < arr_right[j])) {
      arr_c[i + j] = arr_left[i];
      ++i;
    } else {
      arr_c[i + j] = arr_right[j];
      ++j;
    }
  }

  return arr_c;
}

int *merge_sort(int *arr, int size) {
  if (size == 1) {
    return arr;
  }

  int l_size = size / 2;
  int r_size = size - l_size;

  int *left_subarray = arr;
  int *right_subarray = arr + l_size;

  left_subarray = merge_sort(left_subarray, l_size);
  right_subarray = merge_sort(right_subarray, r_size);

  return merge(left_subarray, right_subarray, l_size, r_size);
}
