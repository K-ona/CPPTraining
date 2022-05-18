class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int l = 1, r = m * n;
        while (l < r) {
            int mid = l + (r - l) / 2; 
            int res = n * (mid / n); 
            for (int i = mid / n + 1; i <= m; ++i) {
                res += mid / i; 
            }
            if (res < k) {
                l = mid + 1; 
            } else {
                r = mid; 
            }
        }
        return l; 
    }
};