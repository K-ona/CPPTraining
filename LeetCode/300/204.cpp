int prime[400005];
bool vis[5000005];
int cnt;

// 埃氏筛
class Solution {
  static void fun(int n = 5000000) {
    if (cnt)
      return;
    cnt = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < n; ++i) {
      if (!vis[i])
        prime[cnt++] = i;
      for (int j = i + i; j < n; j += i) {
        vis[j] = true;
      }
    }
  }

 public:
  int countPrimes(int n) {
    fun();
    return std::lower_bound(prime, prime + cnt, n) - prime;
  }
};

// 线性筛
class Solution {
 public:
  int countPrimes(int n) {
    vector<int> primes;
    vector<int> isPrime(n, 1);
    for (int i = 2; i < n; ++i) {
      if (isPrime[i]) {
        primes.push_back(i);
      }
      for (int j = 0; j < primes.size() && i * primes[j] < n; ++j) {
        isPrime[i * primes[j]] = 0;
        if (i % primes[j] == 0) {
          break;
        }
      }
    }
    return primes.size();
  }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode.cn/problems/count-primes/solution/ji-shu-zhi-shu-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。