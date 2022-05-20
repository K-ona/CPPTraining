class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    int cnt = 0;
    int res = 1e9 + 7;
    for (auto num : nums) {
      if (num == res)
        ++cnt;
      else {
        if (--cnt < 0) {
          res = num;
          cnt = 1;
        }
      }
    }
    return res;
  }
};