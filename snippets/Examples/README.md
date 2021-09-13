# 经典面试例题

## [在数组中找到第k大的元素](https://www.lintcode.com/problem/5/)

1. 用快排的思想，快排在每一次partition时会确定一个元素的位置，即若该位置是i，则该位置上元素为第i小的元素

2. 使用库函数：std::nth_element (头文件\#include <bits/stl_algo.h> 或 \<algorithm>)

3. 若k远小于n，则可使用优先级队列保存最大的k个元素
