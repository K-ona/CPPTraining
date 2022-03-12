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

## [1847 Closest Room](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/1847.cpp)

1. 离线方法
先将所有query与rooms按size进行降序排序，再按阶段(一个minsize作为一个阶段)将符合条件的room的ID放入set，set代表当前可选的所有房间

## [53 Maximum Subarray](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/53.cpp)

1. 动态规划
用dp[r]表示以nums[r]结尾的最大子串和，则有dp[r] = max(dp[r - 1] + nums[r], nums[r])
表示此时有最大和的子串是否包含nums[r - 1], 若包含则dp[r] = dp[r - 1] + nums[r], 不包含则易知dp[r] = nums[r]

## [128 Longest Consecutive Sequence](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/128.cpp)

1. 由于是无序数组，所以需要遍历每个元素作为起始点
   - 用hash表以O(1)的时间查询某个值是否存在
   - 若x - 1存在则说明以x - 1（或前面更小的）为起始点可以遍历到x，并且比以x开头的序列更长，所以可以跳过这类x
   - 每个元素被count计算一次，为O(n)

## [134 Gas Station](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/134.cpp)

1. 每个气站减去到下个站的耗费，问题转化为：求使下列函数值始终大于0的起始点i。
$$ F[i, x] = \sum_{j=i}^{i + x} gas[j] $$
&emsp; 令i=0，函数最低点设为$x_k$，易知使函数最低点＞0即可
&emsp; &emsp;![示意图](../src/img/lc134.png "示意图" )
&emsp; 若函数最后一点为负易知无解，
&emsp; 否则令i=k,则可使函数最低点得到最大提升，提升值为函数最后一点与该点之差，所此时最低点仍小于0则无解，否则以k为起始点有解

## [137 Gas Station](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/137.cpp)

从二进制每一位的角度求是否只存在一个

## [139 Word Break](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/139.cpp)

1. 直接区间dp，dp[i][j]表示区间(i, j)是否满足，O(n^3)
2. 设dp[i]表示区间(0, i), O(n^2)

## [9 Palindrome Number](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/9.cpp)

1. 官方题解
   - 翻转后一半数字与前一半数字进行比对
   - 通过大小判断是否到达一半的位数

## [10 Regular Expression Matching](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/10.cpp)

1. 动态规划
   定义状态空间：$bool\ dp[n][m]$, $dp[i][j]$表示字符串的前i个字符能够被模式串的前j个字符完全匹配
   时间复杂度：$O(n^3)$

## [11 Container With Most Water](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/11.cpp)

1. 官方题解：双指针
   - 使用双指针指向容器的边界，每次移动较矮的一侧
   - [证明](https://leetcode-cn.com/problems/container-with-most-water/solution/sheng-zui-duo-shui-de-rong-qi-by-leetcode-solution/)

## [15 3Sum](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/15.cpp)

1. 官方题解：排序+双指针
   - 排序后，三重循环计算找到a+b+c=0的组合
   - 发现随着b增加，c一定减小
   - 双指针：b从小到大，c从大到小

## [22 Generate Parentheses](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/22.cpp)

1. 卡特兰数递推式
   - $T[0] = T[1] = 1$
   - $T[n] = \sum_{k=0}^{n-1}{T[k] \times T[n - 1 - k]}$
   - 对应此题则有：
      - $S[n] = \{\ (S[k])S[n - 1 - k] \ \}$
   - 递归求解即可

## [553 3Sum](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/553.cpp)

1. 区间dp
   保存各区间的最大最小值
2. 数学思维题
   - 从结果上看，最后等于前部分除以后部分
   - 前部分作为分子应该尽可能大，而最大为nums[0]即不除任何东西，因为nums元素都大于1
   - 同理后半部分不加括号时最小
   - 此时整体最大

## [2104 Sum of Subarray Ranges](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/2104.cpp)

1. 问题即为各区间最大值之和与最小值之和的差，解题关键在于将最大值之和与最小值之和分开求解，异步处理
   - 转换思路，求以每个元素为最大最小值的区间个数
   - 通过单调栈分别求出

## [32 Longest Valid Parentheses](https://github.com/K-ona/CPPTraining/blob/main/LeetCode/100/32.cpp)

1. 动规
   - 状态：dp[i]是以s[i]为起始位置的最长合法括号
   - dp[i] = 2 + dp[i + 1] + dp[i + 2 + dp[i + 1]] if (s[i + 1] == '(') else dp[i] = 2 + dp[i + 2] + dp[i + 2 + dp[i + 2]];
2. 使用栈
   - 用栈记录最后没有被匹配的右括号下标
3. 边界计数器
   - 用left计当前左括号的个数，right计右括号的个数
   - 相等于即为合法，更新答案
   - right大于left时，清零重新计数
