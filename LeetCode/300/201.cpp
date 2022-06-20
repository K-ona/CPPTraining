class Solution {
 public:
  int rangeBitwiseAnd(int left, int right) {
    unsigned res = 0;
    for (int i = 0; i < 32; ++i) {
      unsigned sep = 1u << i;
      if (right - left < sep)
        res |= sep & left & right;
    }
    return res;
  }
};