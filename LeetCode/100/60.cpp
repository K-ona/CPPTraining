// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

template <typename T>
inline decltype(auto) f(T N) {
  if (N == 1 or N == 0) return 1; 
  return N * f(N - 1);
}

class Solution {
  int n; 
  bool vis[10]; 
 public:
  string getPermutation(int n, int k) {
    char s[n + 1];
    this->n = n; 
    memset(vis, 0, sizeof (vis)); 
    DFS(s, 0, k); 
    s[n] = '\0'; 
    return s; 
  }

  void DFS(char* s, int ind, int k) {
    if (ind == n) return ; 
    int tmp = f(n - ind - 1); 
    int sep = (k - 1) / tmp; 
    int rem = k - sep * tmp; 
    for (int i = 1; i <= n; ++i) {
      if (!vis[i] and !(sep--)) {
        s[ind] = '0' + i; 
        vis[i] = true; 
        DFS(s, ind + 1, rem); 
        return ;
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

  Solution().getPermutation(3, 3);
  return 0;
}