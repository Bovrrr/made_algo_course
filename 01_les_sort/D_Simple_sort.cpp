#include <ctime>
#include <iostream>

using namespace std;

void fill_array(int *arr, int size);
void print_array(int *arr, int size);
void swap(int i, int j);
int get_pivot(int *arr, int left, int right);
int *split(int *arr, int left, int right, int pivot);
void qsort(int *arr, int left, int right);

int main() {
  srand(time(NULL));

  int numbers_amount = 0;
  cin >> numbers_amount;

  int *arr = new int[numbers_amount];
  fill_array(arr, numbers_amount);

  qsort(arr, 0, numbers_amount - 1);
  print_array(arr, numbers_amount);
  delete[] arr;

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

void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}

int get_pivot(int *arr, int left, int right) {
  int ind = left + rand() % (right - left + 1);
  return arr[ind];
}

int *split(int *arr, int left, int right, int pivot) {
  while (left <= right) {
    while (arr[left] < pivot) {
      ++left;
    }

    while (arr[right] > pivot) {
      --right;
    }

    if (left <= right) {
      swap(arr + left, arr + right);
      left++;
      --right;
    }
  }

  int *indexes = new int[2]{left, right};

  return indexes;
}

void qsort(int *arr, int left, int right) {
  if (right <= left) {
    return;
  }

  int pivot = get_pivot(arr, left, right);
  int *indexes = split(arr, left, right, pivot);

  qsort(arr, left, indexes[1]);
  qsort(arr, indexes[0], right);

  delete[] indexes;
}