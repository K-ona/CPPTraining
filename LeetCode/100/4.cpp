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
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int k = static_cast<int>(nums1.size() + nums2.size()) / 2; 
    uint32_t pad1 = 0, pad2 = 0; 
    while (k && pad1 < nums1.size() && pad2 < nums2.size()) {
      if (nums1[pad1 + k / 2] <= nums2[pad2 + k / 2]) {
        pad1 += k / 2; 
        pad1 = std::min(nums1.size(), pad1); 
      } else {
        pad2 += k / 2; 
        pad2 = std::min(nums2.size(), pad2); 
      }
      k -= k / 2; 
      k = std::max(0, k); 
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