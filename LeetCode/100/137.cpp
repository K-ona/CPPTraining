// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
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
    int singleNumber(vector<int>& nums) {
        int res = 0; 
        int len = nums.size();
        for (int i = 0; i < 32; ++i) {
           int cnt = 0; 
           for (const auto &num: nums) {
               num & (1 << i) ? ++cnt : 0; 
           }
           res |= (cnt % 3) << i; 
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