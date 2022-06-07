#include <vector>

using std::vector; 

int psz; 
int h; 
class Solution {
  bool check(vector<int>& piles, int k) {
    int cnt = 0;
    for (int i = 0; i < psz; ++i) {
      cnt += (piles[i] + k - 1) / k; 
    } 
    return cnt <= h; 
  }

 public:
  int minEatingSpeed(vector<int>& piles, int h) {
    int l = 1, r = 1e9; 
    ::psz = piles.size(); 
    ::h = h; 
    while (l < r) {
      int mid = (l + r) >> 1; 
      if (!check(piles, mid)) {
        l = mid + 1;
      } else {
        r = mid;  
      }
    } 
    return l; 
  }
};