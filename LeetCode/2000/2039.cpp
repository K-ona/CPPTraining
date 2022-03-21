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
    int n = patience.size(); 
    for (auto &x: G) x.clear(); 
    for (auto e: edges) {
      G[e[0]].push_back(e[1]); 
      G[e[1]].push_back(e[0]); 
    }

    memset(dis, 0x3f, sizeof dis); 
    cal_dis(G, 0); 

    int res = 0; 
    
    for (int i = 1; i < n; ++i) {
      int time = 2 * dis[i]; 
      int sc = (time - 1) / patience[i] * patience[i]; 

      res = std::max(res, sc + time + 1); 
    //   cout << i << " " << dis[i] << " " << sc + time + 1 << endl; 
    }
    return res; 
  }

  void cal_dis(std::vector<int> G[], int root) {
    std::queue<int> Q; 
    Q.push(root); 
    dis[root] = 0; 
  
    while (!Q.empty()) {
      root = Q.front(); Q.pop(); 
      for (auto v: G[root]) {
        if (dis[v] > dis[root] + 1) {
          dis[v] = dis[root] + 1; 
          Q.push(v); 
        }
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

