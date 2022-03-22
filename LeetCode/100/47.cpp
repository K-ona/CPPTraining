// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
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
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res; 
    std::sort(nums.begin(), nums.end()); 
    
    std::vector<int> S;
    S.reserve(nums.size()); 
    
    vector<int> vis(nums.size(), 0); 
    track_back(res, nums, 0, S, vis); 
    res; 
  }

  void track_back(vector<vector<int>>& res, vector<int>& nums, 
                    int pos, std::vector<int>& St, vector<int>& vis) {
    if (pos == nums.size()) {
      res.push_back(St);
      cout << endl; 
      return ;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (vis[i] or (i and nums[i - 1] == nums[i] and !vis[i - 1])) continue;   
      St.push_back(nums[i]); 
      vis[i] = 1; 
      cout << nums[i]; 
      track_back(res, nums, pos + 1, St, vis); 
      vis[i] = 0; 
      St.pop_back(); 
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