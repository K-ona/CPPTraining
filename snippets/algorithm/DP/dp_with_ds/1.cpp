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

// 1. 贪心做法
int R[1000005]; 
void solve() {
    int N, T;
    cin >> N >> T;
    memset(R, 0, sizeof(R));
    for (int i = 0; i < N; i++) {
        int l, r;
        cin >> l >> r;
        R[l] = std::max(R[l], r);
    }
    int l = 1, p = 1, cnt = 0;
    while (l <= T) {
        int maxr = 0;
        while (p <= l) maxr = std::max(maxr, R[p]),p++;
        if (l == maxr + 1) break;
        l = maxr + 1;
        cnt++;
    }
    if (l <= T) cout << -1 << '\n';
    else cout << cnt << '\n';
}

// 2. 线段树维护最值

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

namespace SectionSumSegTree {
// 设为实际节点数的4倍
template<typename Sz_T, typename Val_T>
struct node
{
  Sz_T l, r, siz; 
  Val_T w; 
};

// 通过子区间计算该区间值
template<typename Sz_T, typename Val_T>
inline void push_up(Sz_T rt, node<Sz_T, Val_T> T[]) {
  T[rt].w = std::min(T[lc(rt)].w, T[rc(rt)].w); 
}

template<typename Sz_T, typename Val_T>
inline void build(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[]) {
  T[rt].l = l, T[rt].r = r, T[rt].siz = r - l + 1; 
  if (l == r) {
    T[rt].w = 25005; 
  }
  else {
    Sz_T mid = (l + r) >> 1; 
    build(lc(rt), l, mid, T); 
    build(rc(rt), mid + 1, r, T); 
    push_up(rt, T); 
  }
}

template<typename Sz_T, typename Val_T>
inline void add(Sz_T rt, Sz_T pos, Val_T x, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r; 
  if (L == R && L == pos) {
    T[rt].w = std::min(T[rt].w, x); 
    return ;
  }
  Sz_T mid = (L + R) >> 1; 
  if (pos <= mid) add(lc(rt), pos, x, T);
  if (mid < pos) add(rc(rt), pos, x, T);
  push_up(rt, T); 
}

template<typename Sz_T, typename Val_T>
inline Val_T min(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[]) {
  if (l > r) return static_cast<Val_T>(25005); 
  Sz_T L = T[rt].l, R = T[rt].r; 
  if (l <= L && R <= r) return T[rt].w; 
  // push_down(rt, T); 
  Sz_T mid = (L + R) >> 1; 
  Val_T res = static_cast<Val_T>(25005); 
  if (l <= mid) res = std::min(res, min(lc(rt), l, r, T)); 
  if (mid < r) res = std::min(res, min(rc(rt), l, r, T)); 
  return res; 
}


}  // namespace SectionSumSegTree

using namespace SectionSumSegTree; 
node<int, int> T[1000005 * 5];  

struct A
{
  int s, t; 
}cow[25005];

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  // solve(); 
  // exit(0);
  
  int N, t; 
  cin >> N >> t; 
  for (int i = 0; i < N; ++i) { 
    cin >> cow[i].s >> cow[i].t; 
  }

  std::sort(cow, cow + N, [&](auto first, auto second) {
    if (first.t != second.t) return first.t < second.t; 
    return first.s < second.s; 
  }); 
  
  build(1, 0, t, T); 
  add(1, 0, 0, T); 
  for (int i = 0; i < N; ++i) { 
    int tmp = 1 + min(1, cow[i].s - 1, cow[i].t, T); 
    tmp = std::min(tmp, min(1, cow[i].t, cow[i].t, T)); 
    tmp = std::min(tmp, 25005); 
    add(1, cow[i].t, tmp, T); 
  }

  if (min(1, t, t, T) < 25005) {
    cout << min(1, t, t, T) << endl; 
  } else {
    cout << -1 << endl; 
  }
  return 0;
}