// created by Kona @VSCode
#include "../../include/utility.hpp"

// 区间更新区间查询线段树模板（区间长度为1即为单点查询）
// 模板题：http://poj.org/problem?id=3468、https://www.luogu.com.cn/record/9549488
namespace KonaImpl {

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define mid_seg(l, r) ((l + r) >> 1)

namespace SectionSumSegTree {
// 设为实际节点数的4倍
template<typename Sz_T, typename Val_T>
struct node
{
  Sz_T l, r, siz; 
  Val_T w, laz; 
};

// 通过子区间计算该区间值
template<typename Sz_T, typename Val_T>
inline void push_up(Sz_T rt, node<Sz_T, Val_T> T[]) {
  T[rt].w = T[lc(rt)].w + T[rc(rt)].w; 
}

// 将当前lazy标记，下压传递给左右子区间
template<typename Sz_T, typename Val_T>
inline void push_down(Sz_T rt, node<Sz_T, Val_T> T[]) {
  if (T[rt].laz) {
    T[lc(rt)].w += T[lc(rt)].siz * T[rt].laz; 
    T[lc(rt)].laz += T[rt].laz; 
    T[rc(rt)].w += T[rc(rt)].siz * T[rt].laz; 
    T[rc(rt)].laz += T[rt].laz; 
    T[rt].laz = static_cast<Val_T>(0); // 取消当前区间标记
  }
}

// 建树，注意从节点1开始
template<typename Sz_T, typename Val_T>
inline void build(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[], Sz_T val[]) {
  T[rt].l = l, T[rt].r = r, T[rt].siz = r - l + 1, T[rt].laz = 0; 
  if (l == r) {
    T[rt].w = val[l]; 
  }
  else {
    Sz_T mid = mid_seg(l, r); 
    build(lc(rt), l, mid, T, val); 
    build(rc(rt), mid + 1, r, T, val); 
    push_up(rt, T); 
  }
}

// 区间[l, r]每个元素加上x
template<typename Sz_T, typename Val_T>
inline void add(Sz_T rt, Sz_T l, Sz_T r, Val_T x, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r; 
  if (l <= L && R <= r) {
    T[rt].w += T[rt].siz * x; 
    T[rt].laz += x;
    return ;
  }
  push_down(rt, T); 
  Sz_T mid = mid_seg(L, R); 
  if (l <= mid) add(lc(rt), l, r, x, T);
  if (mid < r) add(rc(rt), l, r, x, T);
  push_up(rt, T); 
}

// 区间求和
template<typename Sz_T, typename Val_T>
inline Val_T sum(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r; 
  if (l <= L && R <= r) return T[rt].w; 
  push_down(rt, T); 
  Sz_T mid = mid_seg(L, R); 
  Val_T res = static_cast<Val_T>(0); 
  if (l <= mid) res += sum(rt + rt, l, r, T); 
  if (mid < r) res += sum(rt + rt + 1, l, r, T); 
  return res; 
}

}  // namespace SectionSumSegTree
} // namespace KonaImpl