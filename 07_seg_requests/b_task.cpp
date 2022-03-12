#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int RMQ(int left, int right, const vector<vector<int>> &matrixOfMins,
        const vector<int> &logs) {
  int log_last = logs[right - left + 1];
  return min(matrixOfMins[left][log_last],
             matrixOfMins[right - (1 << log_last) + 1][log_last]);
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int const MOD = 16714589;

  // объявление и считывание входных данных
  int arrNum, reqNum, a_first, u, v;
  cin >> arrNum >> reqNum >> a_first >> u >> v;

  // генерация массива
  vector<int> arr(arrNum, a_first);
  for (size_t i = 1; i < arrNum; ++i) arr[i] = (23 * arr[i - 1] + 21563) % MOD;

  // создаю и заполняю вектор степеней двойки,
  // помещающихся между массиве
  vector<int> logs(arrNum + 1, 0);
  for (size_t i = 2; i < arrNum + 1; ++i)
    logs[i] = ((1 << (logs[i - 1] + 1)) <= i) ? logs[i - 1] + 1 : logs[i - 1];

  // создаю и заполняю матрицу matrixOfMins
  vector<vector<int>> matrixOfMins(arrNum, vector<int>(logs[arrNum] + 1));
  for (size_t i = 0; i < arrNum; ++i) matrixOfMins[i][0] = arr[i];

  for (size_t logNum = 1; logNum < logs[arrNum] + 1; ++logNum) {
    for (size_t left = 0; left < arrNum; ++left) {
      matrixOfMins[left][logNum] =
          (left + (1 << (logNum - 1)) < arrNum)
              ? min(matrixOfMins[left][logNum - 1],
                    matrixOfMins[left + (1 << (logNum - 1))][logNum - 1])
              : matrixOfMins[left][logNum - 1];
    }
  }

  int r = 0;
  for (size_t i = 1; i < reqNum; ++i) {
    r = RMQ(min(u, v) - 1, max(u, v) - 1, matrixOfMins, logs);
    u = ((17 * u + 751 + r + 2 * i) % arrNum) + 1;
    v = ((13 * v + 593 + r + 5 * i) % arrNum) + 1;
  }

  cout << u << ' ' << v << ' '
       << RMQ(min(u, v) - 1, max(u, v) - 1, matrixOfMins, logs);

  return 0;
}
