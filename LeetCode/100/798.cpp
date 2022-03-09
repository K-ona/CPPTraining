// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

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
 public:
  int bestRotation(vector<int>& nums) {
    std::deque<int> DQ; 
    int n = nums.size(); 
    
    for (int i = 0; i < n; ++i) {
      if (nums[i] <= i) {
        DQ.push_back(nums[i]); 
      }
    }
    
    int res = DQ.size(); 
    for (int i = 0; i < n - 1; ++i) {
      
    }

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