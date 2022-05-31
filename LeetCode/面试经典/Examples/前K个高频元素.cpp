// created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <map>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
 public:
  /**
   * @param nums: the given array
   * @param k: the given k
   * @return: the k most frequent elements
   */
  vector<int> topKFrequent(vector<int>& nums, int k) {
    std::unordered_map<int, int> cnt;
    for (int x : nums) {
      ++cnt[x]; 
    }
    std::priority_queue<std::pair<int, int>> PQ; 
    std::vector<int> res;
    res.reserve(k);  
    for (auto x: cnt) {
      PQ.push({x.second, x.first}); 
    }
    for (int i = 0; i < k; ++i) {
      res.push_back(PQ.top().second); 
      PQ.pop();
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