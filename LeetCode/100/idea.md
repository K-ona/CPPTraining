# 解题思路

## 1818 Minimum Absolute Sum Difference

替换后的差为$min(|a_x - b_j|) - |a_j - b_j|$
遍历j，对于每一个j找到使该项最小的x即可，将nums1排序后，用lower_bound查找最接近nums[j]的左右两项，求最小值

## 1817 Finding the Users Active Minutes

两种思路

1. 对每用户进行排序与去重
2. unordered_map + set去重
