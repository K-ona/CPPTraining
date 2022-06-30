class Solution {
 public:
  int numPrimeArrangements(int n) {
    vector<int> vis(n + 1);
    vector<long long> perm(n + 1);
    perm[0] = 1;
    const int mod = 1e9 + 7;
    for (int i = 1; i <= n; ++i) {
      perm[i] = (i * perm[i - 1]) % mod;
    }
    int pn = 0;
    for (int i = 2; i <= n; ++i) {
      if (!vis[i])
        ++pn;
      for (int j = i * i; j <= n; j += i) {
        vis[j] = 1;
      }
    }

    return (perm[pn] * perm[n - pn]) % mod;
  }
};