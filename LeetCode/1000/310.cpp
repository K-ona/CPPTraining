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
  void dfs(int u,
           vector<int>& dist,
           vector<int>& parent,
           const vector<vector<int>>& adj) {
    for (auto& v : adj[u]) {
      if (dist[v] < 0) {
        dist[v] = dist[u] + 1;
        parent[v] = u;
        dfs(v, dist, parent, adj);
      }
    }
  }

  int findLongestNode(int u,
                      vector<int>& parent,
                      const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    dist[u] = 0;
    dfs(u, dist, parent, adj);
    int maxdist = 0;
    int node = -1;
    for (int i = 0; i < n; i++) {
      if (dist[i] > maxdist) {
        maxdist = dist[i];
        node = i;
      }
    }
    return node;
  }

  vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) {
      return {0};
    }
    vector<vector<int>> adj(n);
    for (auto& edge : edges) {
      adj[edge[0]].emplace_back(edge[1]);
      adj[edge[1]].emplace_back(edge[0]);
    }
    vector<int> parent(n, -1);
    /* 找到距离节点 0 最远的节点  x */
    int x = findLongestNode(0, parent, adj);
    /* 找到距离节点 x 最远的节点  y */
    int y = findLongestNode(x, parent, adj);
    /* 找到节点 x 到节点 y 的路径 */
    vector<int> path;
    parent[x] = -1;
    while (y != -1) {
      path.emplace_back(y);
      y = parent[y];
    }
    int m = path.size();
    if (m % 2 == 0) {
      return {path[m / 2 - 1], path[m / 2]};
    } else {
      return {path[m / 2]};
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