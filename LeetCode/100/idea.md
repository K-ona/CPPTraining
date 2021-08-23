# 解题思路

## 1818 Minimum Absolute Sum Difference

替换后的差为$min(|a_x - b_j|) - |a_j - b_j|$
遍历j，对于每一个j找到使该项最小的x即可，将nums1排序后，用lower_bound查找最接近nums[j]的左右两项，求最小值

## 1817 Finding the Users Active Minutes

两种思路

1. 对每用户进行排序与去重
2. unordered_map + set去重

## 1823 Find the Winner of the Circular Game

约瑟夫环问题

1. 模拟
2. dp
用f(n, k)表示在每次数k个情况下最后的坐标（范围为[0, n)）
易知第一个被选中的为第k-1个，若将第k个人重新编号为0，设剩下n-1个人进行游戏最后得到的坐标为x，易知x在原状态下坐标为$f(n, k) = y = (x + k) \% n = (f(n-1, k) + k) \% n$，即得递推式

## 1824 Minimum Sideway Jumps

1. DFS遍历，复杂度$\Omicron(3 * n) = \Omicron(n)$
2. DP，思路类似

## 1829 Maximum XOR for Each Query

易知异或结果最大值为$2^maximumBit - 1$

## 1830 Minimum Number of Operations to Make String Sorted

官方题解：[题解](https://leetcode-cn.com/problems/minimum-number-of-operations-to-make-string-sorted/solution/shi-zi-fu-chuan-you-xu-de-zui-shao-cao-z-qgra/)
