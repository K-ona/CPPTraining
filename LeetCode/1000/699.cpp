#include <vector>
#include <unordered_map>

namespace KonaImpl {

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

namespace SectionMaxSegTree {
// 设为实际节点数的4倍
template <typename Sz_T, typename Val_T>
struct node {
  Sz_T l, r, siz;
  Val_T max, laz;
};

// 通过子区间计算该区间值
template <typename Sz_T, typename Val_T>
inline void push_up(Sz_T rt, node<Sz_T, Val_T> T[]) {
  T[rt].max = std::max(T[lc(rt)].max, T[rc(rt)].max);
}

// 将当前lazy标记，下压传递给左右子区间
template <typename Sz_T, typename Val_T>
inline void push_down(Sz_T rt, node<Sz_T, Val_T> T[]) {
  if (T[rt].laz) {
    T[lc(rt)].laz = T[rt].laz;
    T[lc(rt)].max = T[rt].laz;

    T[rc(rt)].laz = T[rt].laz;
    T[rc(rt)].max = T[rt].laz;
    T[rt].laz = static_cast<Val_T>(0);  // 取消当前区间标记
  }
}

// 建树，注意从节点1开始
template <typename Sz_T, typename Val_T>
inline void build(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[]) {
  T[rt].l = l, T[rt].r = r, T[rt].siz = r - l + 1, T[rt].laz = 0;
  if (l == r) {
    T[rt].max = 0;
  } else {
    Sz_T mid = (l + r) >> 1;
    build(lc(rt), l, mid, T);
    build(rc(rt), mid + 1, r, T);
    push_up(rt, T);
  }
}

// 区间[l, r]每个元素变为x
template <typename Sz_T, typename Val_T>
inline void update(Sz_T rt, Sz_T l, Sz_T r, Val_T x, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r;
  if (l <= L && R <= r) {
    T[rt].max = x;
    T[rt].laz = x;
    return;
  }
  push_down(rt, T);
  Sz_T mid = (L + R) >> 1;
  if (l <= mid)
    update(lc(rt), l, r, x, T);
  if (mid < r)
    update(rc(rt), l, r, x, T);
  push_up(rt, T);
}

// 区间查询最大值
template <typename Sz_T, typename Val_T>
inline Val_T Max(Sz_T rt, Sz_T l, Sz_T r, node<Sz_T, Val_T> T[]) {
  Sz_T L = T[rt].l, R = T[rt].r;
  if (l <= L && R <= r)
    return T[rt].max;
  push_down(rt, T);
  Sz_T mid = (L + R) >> 1;
  Val_T res = static_cast<Val_T>(0);
  if (l <= mid)
    res = std::max(res, Max(rt + rt, l, r, T));
  if (mid < r)
    res = std::max(res, Max(rt + rt + 1, l, r, T));
  return res;
}

}  // namespace SectionMaxSegTree
}  // namespace KonaImpl


using std::vector;
using namespace KonaImpl; 
using namespace KonaImpl::SectionMaxSegTree; 

node<int, int> nd[80000]; 

class Solution {
 public:
  vector<int> fallingSquares(vector<vector<int>>& positions) {
    vector<int> nums; 
    nums.reserve(positions.size() * 2); 
    for (auto& item : positions) {
      nums.emplace_back(item[0]);
      nums.emplace_back(item[1] + item[0] - 1);
    }
    std::sort(nums.begin(), nums.end()); 
    int n = std::unique(nums.begin(), nums.end()) - nums.begin(); 
    // nums.resize(n);

    std::unordered_map<int, int> M; 
    for (int i = 0; i < n; ++i) M[nums[i]] = i; 

    vector<int> res; 
    res.reserve(positions.size()); 

    build(1, 0, n - 1, nd);
    for (const auto& item: positions) {
      int max = Max(1, M[item[0]], M[item[1] + item[0] - 1], nd); 
      max += item[1]; 
      update(1, M[item[0]], M[item[1] + item[0] - 1], max, nd); 
      res.emplace_back(Max(1, 0, n - 1, nd));
    }
    return res; 
  }
};