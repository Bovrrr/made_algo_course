#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void fill_array(vector<int> &arr) {
  for (int &el : arr) cin >> el;
}

void print_array(vector<int> &arr) {
  for (const int &el : arr) cout << el << endl;
}

void swap(int &i, int &j) {
  int temp = i;
  i = j;
  j = temp;
}

int get_pivot(const vector<int> &arr, int left, int right) {
  int ind = left + rand() % (right - left + 1);
  return arr[ind];
}

vector<int> split(vector<int> &arr, int left, int right, int pivot) {
  while (left <= right) {
    while (arr[left] < pivot) {
      ++left;
    }

    while (arr[right] > pivot) {
      --right;
    }

    if (left <= right) {
      swap(arr[left], arr[right]);
      ++left;
      --right;
    }
  }

  vector<int> indexes{left, right};

  return indexes;
}

int find(vector<int> arr, int left, int right, int k) {
  if (right <= left) return arr[k];

  int pivot = get_pivot(arr, left, right);
  vector<int> indexes = split(arr, left, right, pivot);

  if (k < indexes[0])
    return find(arr, left, indexes[1], k);
  else
    return find(arr, indexes[0], right, k);
}

int main() {
  srand(time(NULL));

  int clons_number;
  cin >> clons_number;

  vector<int> arr(clons_number);
  fill_array(arr);

  int requests_number;
  cin >> requests_number;

  vector<int> request(3);
  vector<int> answers(requests_number);

  for (int i = 0; i < requests_number; ++i) {
    for (int j = 0; j < 3; ++j) cin >> request[j];

    answers[i] =
        find(arr, request[0] - 1, request[1] - 1, request[0] + request[2] - 2);
  }
  print_array(answers);

  return 0;
}
