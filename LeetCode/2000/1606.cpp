// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <set>

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
  vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
    int n = arrival.size(); 
    std::set<int> free; 
    for (int i = 0; i < k; i++) {
      free.insert(i); 
    }
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>> > busy; 
    std::vector<int> res(k, 0); 
    int max_load = 0;
    for (int i = 0; i < n; ++i) {
      while (!busy.empty() and busy.top().first <= arrival[i]) {
        free.insert(busy.top().second);
        busy.pop();
      }
      if (free.empty()) 
        continue; 
      
      auto it = free.lower_bound(i % k); 

      if (it != free.end() and *it == i % k) {
        free.erase(i % k);
        busy.push({arrival[i] + load[i], i % k}); 
        ++res[i % k]; 
        max_load = std::max(max_load, res[i % k]);
      } else {
        if (it == free.end()) {
          it = free.begin(); 
        }
        ++res[*it];
        max_load = std::max(max_load, res[*it]);
        busy.push({arrival[i] + load[i], *it}); 
        free.erase(it);
      }
    }
    vector<int> ans; 
    ans.reserve(k);
    for (int i = 0; i < k; ++i) {
      if (res[i] == max_load) {
        ans.push_back(i); 
      }
    }
    return ans; 
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