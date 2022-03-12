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

vector<int> M[100005];
class Solution {
  int size{0}; 
 public:
  int countHighestScoreNodes(vector<int>& parents) {
    size = static_cast<int>(parents.size()); 
    for (int i = 0; i < size; ++i) {
        M[i].clear(); 
    }
    for (int i = 1; i < size; ++i) M[parents[i]].push_back(i); 
    map<ll, int> cnt; 
    DFS(M, 0, cnt); 
    return cnt.rbegin()->second; 
  }

  int DFS(vector<int> (&M)[100005], int cur, map<ll, int>& cnt) {
    if (M[cur].size() == 0) {
      ++cnt[size - 1]; 
      return 1; 
    }
    long long tmp = 1; 
    int sum = 1; 
    for (auto v: M[cur]) {
      int csize = DFS(M, v, cnt);
      tmp *= csize; 
      sum += csize; 
    }
    ++cnt[tmp * std::max(1, size - sum)]; 
    return sum;
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