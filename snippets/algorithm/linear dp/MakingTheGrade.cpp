// created by Kona @VSCode
// 分析问题性质+离散化+dp, sO(n^2)：https://www.acwing.com/problem/content/description/275/
// 性质：存在一组最优解B,使得B中每一个元素都存在于A中 （https://www.acwing.com/solution/content/4956/）

// 另有结合堆的做法复杂度为O(nlogn) (https://www.acwing.com/solution/content/6895/)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cstring>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

int dp[2005][2005]; 
int Solve(int a[], int n, const vector<int>& nums, int m, int p[]) {
    for (int i = 0; i < n; ++i) {
        int min = INT32_MAX; 
        for (int j = 0; j < m; ++j) {
            min = i ? std::min(min, dp[i - 1][j]): 0; 
            dp[i][j] = min + abs(a[i] - nums[j]); 
        }
    }
    return *std::min_element(*(dp + n - 1), *(dp + n - 1) + n); 
}

int a[2005]; 

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int N; 
    cin >> N; 
    for (int i = 0; i < N; ++i) {
        cin >> a[i]; 
    }
    vector<int> nums(a, a + N); 
    std::sort(nums.begin(), nums.end()); 
    int m = std::unique(nums.begin(), nums.end()) - nums.begin(); 
    decltype(a) p; 
    for (int i = 0; i < N; ++i) {
        p[i] = std::lower_bound(nums.begin(), nums.begin() + m, a[i]) - nums.begin(); 
    }
    memset(dp, 0x3f, sizeof dp); 
    int res = Solve(a, N, nums, m, p); 
    std::reverse(a, a + N); 
    res = std::min(res, Solve(a, N, nums, m, p)); 
    cout << res << endl; 
    return 0;
}