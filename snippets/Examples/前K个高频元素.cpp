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

  }
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