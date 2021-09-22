// created by Kona @VSCode

// 01背包、完全背包、多重背包 模板
#include "../../../include/utility.h"
namespace KonaImpl {
namespace knapsack {

// 01背包，倒序更新保证只选一次
inline void update_01(int V, int v, int w, int dp[]) {
  for (int j = V; j >= v; --j) {
    dp[j] = KonaImpl::max(dp[j], dp[j - v] + w);
  }
}

// 完全背包，顺序更新使可选多次
inline void update_cmp(int V, int v, int w, int dp[]) {
  for (int j = v; j <= V; ++j) {
    dp[j] = KonaImpl::max(dp[j], dp[j - v] + w);
  }
}

// 多重背包，二进制拆分数量
inline void update_mul_bibit(int V, int v, int w, int s, int dp[]) {
  for (int p = 1; p <= s; s -= p, p <<= 1) {
    update_01(V, p * v, p * w, dp);
  }
  if (s)
    update_01(V, s * v, s * w, dp);
}

}  // namespace MySort
} // namespace KonaImpl
