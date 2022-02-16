# 单调队列

  适于解决在dp过程中状态有新增、删除的情况，简化决策的筛选

## [最大子序和问题](https://www.acwing.com/problem/content/137/)

朴素做法：
for (int i = 0; i < n; ++i) {
  &emsp; for (int j = i - m + 1; j < i; ++j) {
    &emsp;&emsp; ans = S[i] - min(S[j]);
  &emsp;}
}
return ans; n

每次状态变量i增大1，决策变量j的的范围有增加和减少
本例相当于一个滑动窗口，需要维护窗口内的最小值
考虑当前窗口为 $$ { S[j_1], ..., S[j_2] } $$ 显然有$S[j_2]$的生命周期大于$S[j_1]$的生命周期
若此时有$S[j_2] < S[j_1]$ 则$S[j_1]$ 不可能为当前的最优解，可以删除
所以窗口中的元素应满足递增的规律
对于新到来的$S[i]$，若$S[i] < S[j_2]$, 曾可从$S[j_2]$开始删除元素，直到窗口剩下的元素皆小于$S[i]$
整个过程即为单调队列解法的全过程

单调队列做法：

int l = 1, r = 1;
q[1] = 0; // 队列记录下标即可
for (int i = 1; i <= n; ++i) {
  &emsp; while(l <= r and q[l] < i - m) l++; 
  &emsp; ans = max(ans, s[i] - s[q[l]]); 
  &emsp; while(l <= r and s[q[r]] >= s[i]) r--; 
  &emsp; q[++r] = i; 
}
return ans; 

## [Fence]()

