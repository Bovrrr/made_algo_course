#include <iostream>

using namespace std;

void fill_array(int *arr, int size);
void insertion_sort(int *arr, int size);
void print_array(int *arr, int size);
void swap(int *arr, int j);

int main() {
  int numbers_amount = 0;
  cin >> numbers_amount;

  int *arr = new int[numbers_amount];
  fill_array(arr, numbers_amount);

  insertion_sort(arr, numbers_amount);
  print_array(arr, numbers_amount);

  return 0;
}

void fill_array(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    cin >> arr[i];
  }
}

void insertion_sort(int *arr, int size) {
  for (int i = 1; i < size; ++i) {
    int j = i;

    while (j > 0 && arr[j - 1] > arr[j]) {
      swap(arr, j);
      --j;
    }
  }
}

void print_array(int *arr, int size) {
  for (int i = 0; i < size; ++i) {
    cout << arr[i] << " ";
  }
}

void swap(int *arr, int j) {
  int temp;
  temp = arr[j];
  arr[j] = arr[j - 1];
  arr[j - 1] = temp;
}
