# Solution idea of Educational Round 93

## A

对于三角形有：任意两边之和大于第三边，a + b > c
反过来，不构成三角形的三边满足：最小两条边之和小于等于第三边
$$x_0 + x_0 \leq x_n$$
上述条件满足，则找到答案，否则没有答案

## B

贪心，每个人拿最多的1

## C

令$p_i = \sum^{j\space=\space i - 1}_{j \space= \space0}{a_j}$
则要求满足$p_r - p_l = r - l$的区间数
==变换该式得：$$p_r - r = p_l - l$$==
可先预处理出$p_i - i \space ,i \in [1, n]$，根据相同值个数求最后答案
需要注意的是，若$p_i - i = 0$，说明区间[0, i)自然满足条件，因此预设$p_0 - 0 = 0$

## D

注意不是贪心，用动态规划解决
dp[r][g][b] = max(dp[r][g-1][b-1] + G[g]*B[b], dp[r-1][g][b-1] + R[r]*B[b],dp[r-1][g-1][b] + R[r] * G[g])
