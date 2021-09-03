# 部分题解题思路

## [1818 Minimum Absolute Sum Difference](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1818.cpp)

替换后的差为$min(|a_x - b_j|) - |a_j - b_j|$
遍历j，对于每一个j找到使该项最小的x即可，将nums1排序后，用lower_bound查找最接近nums[j]的左右两项，求最小值

## [1817 Finding the Users Active Minutes](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1817.cpp)

两种思路

1. 对每用户进行排序与去重
2. unordered_map + set去重

## [1823 Find the Winner of the Circular Game](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1823.cpp)

约瑟夫环问题

1. 模拟
2. dp
用f(n, k)表示在每次数k个情况下最后的坐标（范围为[0, n)）
易知第一个被选中的为第k-1个，若将第k个人重新编号为0，设剩下n-1个人进行游戏最后得到的坐标为x，易知x在原状态下坐标为$f(n, k) = y = (x + k) \% n = (f(n-1, k) + k) \% n$，即得递推式

## [1824 Minimum Sideway Jumps](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1824.cpp)

1. DFS遍历，复杂度$\Omicron(3 * n) = \Omicron(n)$
2. DP，思路类似

## [1829 Maximum XOR for Each Query](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1829.cpp)

易知异或结果最大值为$2^maximumBit - 1$

## [1830 Minimum Number of Operations to Make String Sorted](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1830.cpp)

官方题解：[题解](https://leetcode-cn.com/problems/minimum-number-of-operations-to-make-string-sorted/solution/shi-zi-fu-chuan-you-xu-de-zui-shao-cao-z-qgra/)

## [1835 Find XOR Sum of All Pairs Bitwise AND](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1835.cpp)

先求第一项，设$res=(a\space \& \space b[0])\space xor \space(a\space \& \space b[1])\space xor ... \space  xor\space(a\space \& \space b[n - 1]) $

从固定项$a$入手，考虑$a\space \& \space b[0] \space xor \ a\space \& \space b[1]$
因为与$a$的操作是$\&$，所以$a\space \& \space b[0]$最多只会使a二进制表示中的1减少，$a\space \& \space b[1]$同理

如果$b[0]$和$b[1]$的第$i$位对$a$的第$i$位有相同影响，则两者异或后将消除该影响，例如$a=0110110,\ a\  \& \ b[0] = 0110100,\ a\ \& \ b[1] = 0110010$，异或结果为$0000110$, $b[0]$和$b[1]$对a的前两个1的影响相同，则异或后为0，否则为1,

这种影响是否相同可以用b[1]与b[0]的异或结果表示，其异或为1的位表示其影响不同，所以对应位置结果为1，于是
$$
a\space \& \space b[0] \space xor \ a\space \& \space b[1] = a\ \& \ (b[0]\ xor\ b[1])
$$

## [1838 Frequency of the Most Frequent Element](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1838.cpp)

官方题解：[题解](https://leetcode-cn.com/problems/frequency-of-the-most-frequent-element/solution/zui-gao-pin-yuan-su-de-pin-shu-by-leetco-q5g9/)

## [1839 Longest Substring Of All Vowels in Order](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1839.cpp)

用l, r分别表示当前子串的左右边界
若word[r + 1]等于word[r]或word[r]的下一个元音时，r++
否则重新找l（当前r后面第一个为'a'的位置），重复上述步骤知道当前r达到word的边界

## [53 Maximum Subarray](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/53.cpp)
