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

vector<int> G[100005]; 
int dis[100005]; 

class Solution {
 public:
  int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
    for (auto &x: G) x.clear(); 
    for (auto e: edges) {
      G[e[0]].push_back(e[1]); 
      G[e[1]].push_back(e[0]); 
    }

    memset(dis, 0x3f, sizeof dis); 
    cal_dis(0, 0); 

    int res = 0; 

    

    return 0; 
  }

  void cal_dis(int root, int d) {
    dis[root] = std::min(dis[root], d); 
    for (auto u: G[root]) {
      if (dis[u] != 0x3f3f3f3f) {
        cal_dis(u, d + 1); 
      }
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

