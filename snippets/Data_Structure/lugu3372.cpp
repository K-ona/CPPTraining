// created by Kona @VSCode
// 线段树练习题*模板题：https://www.luogu.com.cn/problem/P3372
// 1. 将某区间每一个数加上 k
// 2. 求出某区间每一个数的和
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

namespace KonaImpl {
// 区间更新区间查询线段树模板（区间长度为1即为单点查询）
// 模板题：http://poj.org/problem?id=3468、https://www.luogu.com.cn/problem/P3372
namespace SectionSumSegTree {
// 最好设为实际节点数的4倍（可能会接近*2*2）
template <typename Sz_T, typename Val_T>
struct node {
  Sz_T l, r, siz;
  Val_T w, laz;
};

// 建树，注意从节点1开始
template <typename Sz_T, typename Val_T>
void build(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[], Sz_T val[]) {
  T[rt].l = l, T[rt].r = r, T[rt].siz = r - l + 1, T[rt].laz = 0;
  if (l == r) {
    T[rt].w = val[l];
  } else {
    Sz_T mid = (l + r) / static_cast<Sz_T>(2);
    build(rt + rt, l, mid, T, val);
    build(rt + rt + 1, mid + 1, r, T, val);
    push_up(rt, T);
  }
}

// 通过子区间计算该区间值
template <typename Sz_T, typename Val_T>
void push_up(Sz_T rt, node<Sz_T, Val_T> T[]) {
  T[rt].w = T[rt + rt].w + T[rt + rt + 1].w;
}

// 将当前lazy标记，下压传递给左右子区间
template <typename Sz_T, typename Val_T>
void push_down(Sz_T rt, node<Sz_T, Val_T> T[]) {
  if (T[rt].laz) {
    T[rt + rt].w += T[rt + rt].siz * T[rt].laz;
    T[rt + rt].laz += T[rt].laz;
    T[rt + rt + 1].w += T[rt + rt + 1].siz * T[rt].laz;
    T[rt + rt + 1].laz += T[rt].laz;
    T[rt].laz = static_cast<Val_T>(0);  // 取消当前区间标记
  }
}

// 区间[l, r]每个元素加上x
template <typename Sz_T, typename Val_T>
void add(Sz_T rt, Sz_T l, Sz_T r, Val_T x, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r;
  if (l <= L && R <= r) {
    T[rt].w += T[rt].siz * x;
    T[rt].laz += x;
    return;
  }
  push_down(rt, T);
  Sz_T mid = (L + R) / static_cast<Sz_T>(2);
  if (l <= mid)
    add(rt + rt, l, r, x, T);
  if (mid < r)
    add(rt + rt + 1, l, r, x, T);
  push_up(rt, T);
}

// 区间求和
template <typename Sz_T, typename Val_T>
Val_T sum(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r;
  if (l <= L && R <= r)
    return T[rt].w;
  push_down(rt, T);
  Sz_T mid = (L + R) / static_cast<Sz_T>(2);
  Val_T res = static_cast<Val_T>(0);
  if (l <= mid)
    res += sum(rt + rt, l, r, T);
  if (mid < r)
    res += sum(rt + rt + 1, l, r, T);
  return res;
}

}  // namespace SectionSumSegTree
}  // namespace KonaImpl

int v[100005];
KonaImpl::SectionSumSegTree::node<int, ll> T[100005 * 4];

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> v[i];
  }

  KonaImpl::SectionSumSegTree::build(1, 1, n, T, v); 
  while (q--) {
    int c;
    int l, r;
    ll x; 
    cin >> c;
    switch (c) {
      case 2:
        cin >> l >> r; 
        cout << KonaImpl::SectionSumSegTree::sum(1, l, r, T) << endl;  
        break;
      default:
        cin >> l >> r >> x; 
        KonaImpl::SectionSumSegTree::add(1, l, r, x, T); 
        break;
    }
  }

  return 0;
}