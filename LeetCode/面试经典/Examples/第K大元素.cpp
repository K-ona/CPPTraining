// created by Kona @VSCode
// 1. 快速排序
// 2. 直接使用STL库函数nth_element <algorithm>
// 3. 若k远小于n，则可使用优先级队列保存最大的k个元素

#include <vector> 
#include <queue>
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
  template<typename T>
  inline T quick_select(typename vector<T>::iterator first, typename vector<T>::iterator last) {
    if (first != last) {
      auto p = partition<T>(first, last); 
      if (p - begin == k) {
          return *p; 
      }
      if (p - begin > k) return quick_select<T>(first, p);
      return quick_select<T>(p + 1, last);
    }
  }

  template<typename T>
  inline typename vector<T>::iterator partition( vector<T>::iterator first,
                         vector<T>::iterator end) {
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

  /**
   * @param nums: an integer unsorted array
   * @param k: an integer from 1 to n
   * @return: the kth largest element
   */
  int kthLargestElement2(vector<int> &nums, int k) {
      // write your code here
      std::priority_queue<int, vector<int>, std::greater<int>> PQ; 
      for (auto x: nums) {
          if (PQ.size() < k || x > PQ.top())
              PQ.push(x); 
          if (PQ.size() > k) {
              PQ.pop();  
          }
      }
      return PQ.top(); 
  }

  int kthLargestElement(int k, vector<int>&& nums) {
    // write your code here
    begin = nums.begin(); this->k = nums.size() - k; f = false; 
    return quick_select<int>(nums.begin(), nums.end()); 
  }

};

int main() {
  Solution().kthLargestElement(2, {3,2,1,5,6,4}); 

}