#include <forward_list>
#include <vector>

using std::forward_list;
using std::vector;

class Solution {
  vector<forward_list<int>> hash{100000};

 public:
  int maximumGap(vector<int>& nums) {
    int hi = 0, lo = 1e9;
    for (const auto x : nums) {
      if (hi < x)
        hi = x;
      if (x < lo)
        lo = x;
    }
    if (hi == lo)
      return 0;

    int n = nums.size();
    double factor = 1. / (hi - lo) * (n - 1);
    for (const auto x : nums) {
      hash[factor * (x - lo)].push_front(x);
    }

    int ans = 0;
    int pre_hi = lo;
    for (const auto& list : hash) {
      if (list.empty())
        continue;
      int max = 0, min = 1e9;
      for (const auto x : list) {
        if (max < x)
          max = x;
        if (x < min)
          min = x;
      }
      ans = std::max(ans, min - pre_hi);
      pre_hi = max;
    }
    return ans;
  }
};

// 基数排序
class Solution {
 public:
  int maximumGap(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) {
      return 0;
    }
    int exp = 1;
    vector<int> buf(n);
    int maxVal = *max_element(nums.begin(), nums.end());

    while (maxVal >= exp) {
      vector<int> cnt(10);
      for (int i = 0; i < n; i++) {
        int digit = (nums[i] / exp) % 10;
        cnt[digit]++;
      }
      for (int i = 1; i < 10; i++) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; i--) {
        int digit = (nums[i] / exp) % 10;
        buf[--cnt[digit]] = nums[i];
      }
      copy(buf.begin(), buf.end(), nums.begin());
      exp *= 10;
    }

    int ret = 0;
    for (int i = 1; i < n; i++) {
      ret = max(ret, nums[i] - nums[i - 1]);
    }
    return ret;
  }
};