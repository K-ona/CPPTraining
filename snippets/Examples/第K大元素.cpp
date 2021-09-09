// created by Kona @VSCode
// 1. 快速排序
// 2. 直接使用STL库函数nth_element <algorithm>

#include <vector> 
using std::vector; 
class Solution {
  vector<int>::iterator begin; 
  int k; 
  int ans; 
  bool f; 
 public:
  /**
   * @param k: An integer
   * @param nums: An array
   * @return: the Kth largest element
   */
  inline void quick_sort(vector<int>::iterator first, vector<int>::iterator end) {
    if (f) return ; 
    if (first != end) {
      vector<int>::iterator p = partition(first, end); 
      if (p - begin == k) {
          ans = *p, f = true; 
          return ;
      }
      if (p - begin > k) quick_sort(first, p);
      else quick_sort(p + 1, end);
    }
  }

  inline vector<int>::iterator partition(vector<int>::iterator first,
                                        vector<int>::iterator end) {
    auto x = --end;
    auto lf = first;
    for (auto it = first; it != x; ++it) {
      if (*it <= *x) {
        std::swap(*it, *(lf++));
      }
    }
    std::swap(*x, *lf);
    return lf;
  }

  int kthLargestElement(int k, vector<int>& nums) {
    // write your code here
    begin = nums.begin(); this->k = nums.size() - k; f = false; 
    quick_sort(nums.begin(), nums.end()); 
    return ans; 
  }

};