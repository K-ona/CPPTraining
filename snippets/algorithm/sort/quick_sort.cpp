// created by Kona @VSCode
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#include "../../../include/utility.h"
namespace KonaImpl {
namespace MySort {

// 针对RandomAccessIterator, 元素之间可以比大小
template <class RandomAccessIterator>
inline void quick_sort(RandomAccessIterator first, RandomAccessIterator end) {
  using ptr = RandomAccessIterator;
  if (first != end) {
    ptr p = KonaImpl::partition(first, end); 
    quick_sort(first, p); 
    quick_sort(p + 1, end); 
  }
}

}  // namespace MySort
} // namespace KonaImpl

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */
  vector<int> test{1, 3, 2, 5, 0, -23}; 
  using namespace KonaImpl::MySort; 
  quick_sort(test.begin(), test.end()); 
  for (auto x: test) {
    cout << x << " "; 
  }

  return 0;
}