// created by Kona @VSCode
// 环形dp例题：https://www.acwing.com/problem/content/description/291/
// 思路：从两个点的距离定义可以看出一个点的状态与另外所有点之间都可以进行转移
// 为使距离计算一致化，将环拉直后再重复一遍，此时i, j之间的距离可定义为：在条件i - N / 2 < j < i下, dist(i, j) = i - j
// 此时 ans[i] = max{ a[i] + a[j] + i - j }= a[i] + i + max{ a[j] - j }
// 使用数据结构优化快速计算：堆、单调队列

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

int a[2000005];
int q[2000005]; 

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  int n; 
  cin >> n; 
  for (int i = 0; i < n; ++i) {
    cin >> a[i]; 
    a[i + n] = a[i]; 
  }

  int l = 1, r = 1; 
  int ans = 0; 
  for (int i = 0; i < 2 * n; ++i) {
    while (l <= r && i - q[l] > n / 2) ++l; 
    ans = std::max(ans, a[i] + i + a[q[l]] - q[l]); 
    // cout << i << " " << q[l] << " ans == " << ans << endl; 
    while (l <= r && a[q[r]] - q[r] <= a[i] - i) --r; 
    q[++r] = i; 
  }
  cout << ans << endl; 
  return 0;
}