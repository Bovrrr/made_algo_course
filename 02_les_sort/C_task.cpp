#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void fill_array(vector<vector<char>> &arr);
void print_array(vector<vector<char>> &arr);
vector<char> take_sort_vector(vector<vector<char>> &arr, int el);
vector<vector<char>> i_el_sort(vector<vector<char>> &arr, int threshold,
                               int el);

int main() {
  int strings_num;
  int string_length;
  int sorts_num;

  cin >> strings_num >> string_length >> sorts_num;

  vector<vector<char>> arr(strings_num, vector<char>(string_length));

  fill_array(arr);
  print_array(arr);
  cout << endl;
  arr = i_el_sort(arr, string_length - sorts_num, string_length - 1);
  print_array(arr);

  return 0;
}

vector<char> take_sort_vector(const vector<vector<char>> &arr, int el) {
  vector<char> vect(arr.size());

  for (int i = 0; i < arr.size(); ++i) {
    vect[i] = arr[i][el];
  }

  return vect;
}

void fill_array(vector<vector<char>> &arr) {
  for (vector<char> &str : arr) {
    for (char &elem : str)
      cin >> elem;
  }
}

void print_array(vector<vector<char>> &arr) {
  for (vector<char> &str : arr) {
    for (char &elem : str) {
      cout << elem;
    }
    cout << endl;
  }
}

vector<vector<char>> i_el_sort(vector<vector<char>> &arr, int threshold,
                               int el) {
  if (el < threshold)
    return arr;

  vector<char> i_el_sort_vec = take_sort_vector(arr, el);

  char max_el = *max_element(begin(i_el_sort_vec), end(i_el_sort_vec));
  char min_el = *min_element(begin(i_el_sort_vec), end(i_el_sort_vec));

  int range = max_el - min_el + 1;

  int *cnt = new int[range];
  int *char_indexes = new int[range];
  vector<vector<char>> arr_(arr.size(), vector<char>(arr[0].size()));

  for (int i = 0; i < i_el_sort_vec.size(); ++i)
    cnt[i_el_sort_vec[i] - 'a']++;

  char_indexes[0] = 0;
  for (int i = 1; i < range; ++i)
    char_indexes[i] = char_indexes[i - 1] + cnt[i - 1];

  for (int i = 0; i < arr.size(); ++i)
    arr_[char_indexes[i_el_sort_vec[i] - 'a']++] = arr[i];

  delete[] cnt;
  delete[] char_indexes;

  return i_el_sort(arr_, threshold, el - 1);
}
