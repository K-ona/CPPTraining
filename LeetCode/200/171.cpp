class Solution {
 public:
  int trailingZeroes(int n) {
    int cnt = 0;
    for (; n; n /= 5) {
      cnt += n / 5;
    }
    return cnt;
  }
};