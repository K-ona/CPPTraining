// created by Kona @VSCode
// 树形dp例题：https://www.acwing.com/problem/content/289/
// 本题树为无根树，
// 1. 枚举根节点，平方复杂度
// 2. 二次扫描换根，每次根向领接点变化，减少重复的计算，O(2 * n)
// 先选一个根（自底向上）扫描一遍，再自顶向下与领点换根，每次交换复杂度为O(1)

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

const int maxn = 2e5 + 5;
int cnt;
int to[2 * maxn], next[maxn * 2], w[maxn * 2], head[maxn];

int d[maxn], f[maxn], deg[maxn];

void add(int x, int y, int z) {
  to[++cnt] = y;
  w[cnt] = z;
  next[cnt] = head[x];
  head[x] = cnt;
}

// 第一次扫描，算出d[]
void cal(int u, int pre) {
  // cout << u << " " << pre << endl; 
  d[u] = 0; 
  for (int i = head[u]; i; i = next[i]) {
    int v = to[i];
    if (v == pre)
      continue;
    cal(v, u);
    if (deg[v] == 1)
      d[u] += w[i];
    else
      d[u] += std::min(w[i], d[v]);
  }
}

void dfs(int u, int pre) {
  for (int i = head[u]; i; i = next[i]) {
    int v = to[i];
    if (v == pre)
      continue;
    f[v] = d[v]; 
    if (deg[v] > 1 && deg[u] > 1) {
      f[v] += std::min(w[i], f[u] - std::min(w[i], d[v]));
    } else if (deg[u] > 1 && deg[v] == 1) {
      f[v] += std::min(w[i], f[u] - w[i]); 
    } else {
      f[v] += w[i]; 
    }
    dfs(v, u); 
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int _;
  for (cin >> _; _--; ) {
    cnt = 0; 
    memset(head, 0, sizeof(head)); 
    memset(deg, 0, sizeof(deg)); 

    int n;
    cin >> n; 
    for (int i = 1, x, y, z; i < n; ++i) {
      cin >> x >> y >> z;
      ++deg[x];
      ++deg[y];
      add(x, y, z);
      add(y, x, z);
    }
    cal(1, 0); 
    f[1] = d[1];
    dfs(1, 0); 

    cout << *std::max_element(f + 1, f + 1 + n) << endl; 
  }

  return 0;
}