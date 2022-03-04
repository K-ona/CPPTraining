// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <stack>

#include <string.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class Solution {
  using ll = long long; 
 public:
  long long subArrayRanges(vector<int>& nums) {
    int n = nums.size(); 
    vector<int> min_left(n), max_left(n), min_right(n), max_right(n); 

    std::stack<int> minStack, maxStack; 
    for (int i = 0; i < n; ++i) {
      while (!minStack.empty() and nums[minStack.top()] > nums[i]) {
        minStack.pop(); 
      }
      min_left[i] = minStack.empty() ? -1 : minStack.top(); 
      minStack.push(i); 

      while (!maxStack.empty() and nums[maxStack.top()] < nums[i]) {
        maxStack.pop(); 
      }
      max_left[i] = maxStack.empty() ? -1 : maxStack.top(); 
      maxStack.push(i); 
    }

    while(!minStack.empty()) minStack.pop(); 
    while(!maxStack.empty()) maxStack.pop(); 

    for (int i = n - 1; i >= 0; --i) {
      while (!minStack.empty() and nums[minStack.top()] >= nums[i]) {
        minStack.pop(); 
      }
      min_right[i] = minStack.empty() ? n : minStack.top(); 
      minStack.push(i); 

      while (!maxStack.empty() and nums[maxStack.top()] <= nums[i]) {
        maxStack.pop(); 
      }
      max_right[i] = maxStack.empty() ? n : maxStack.top(); 
      maxStack.push(i); 
    }

    ll res = 0; 
    for (int i = 0; i < n; ++i) {
      res += (i - max_left[i]) * nums[i] * (max_right[i] - i); 
      res -= (i - min_left[i]) * nums[i] * (min_right[i] - i); 
    }
    return res; 
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}