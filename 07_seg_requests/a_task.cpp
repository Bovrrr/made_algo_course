#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long int getSum(int left, int right, vector<long long int> &arrSum) {
  return (left > 0) ? (arrSum[right] - arrSum[left - 1]) : arrSum[right];
}

int main() {
  int const mod_A = (1 << 16);
  int const mod_B = (1 << 30);

  int arrSize, x, y, a_zero;
  cin >> arrSize >> x >> y >> a_zero;

  vector<long long int> arrSum(arrSize, 0);
  arrSum[0] = a_zero;
  long long int curElem = a_zero;
  for (ssize_t i = 1; i < arrSize; ++i) {
    curElem = (x * curElem + y) % mod_A;
    arrSum[i] = curElem + arrSum[i - 1];
  }

  int reqNum, z, t, b_zero;
  cin >> reqNum >> z >> t >> b_zero;

  if (0 == reqNum) {
    cout << 0;
  } else {
    vector<long long int> arrC(reqNum * 2, 0);
    arrC[0] = b_zero % arrSize;
    long long int elemCur = b_zero;

    for (ssize_t i = 1; i < 2 * reqNum; ++i) {
      elemCur = (z * elemCur + t) % mod_B;
      arrC[i] = elemCur % arrSize;
    }

    long long int result = 0;
    for (ssize_t i = 0; i < reqNum; ++i) {
      result += getSum(min(arrC[i * 2], arrC[i * 2 + 1]),
                       max(arrC[i * 2], arrC[i * 2 + 1]), arrSum);
    }
    cout << result;
  }

  return 0;
}
