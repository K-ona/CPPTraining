class Solution {
public:
    int mySqrt(int x) {
      if (x == 0) return 0;
      long long l = 1, r = (long long)x + 1;
      while (l < r) {
        int m = l + (r - l) / 2; 
        if (1ll * m * m <= x) {
          l = m + 1;
        } else {
          r = m;
        }
      }
      return l - 1;
    }
};