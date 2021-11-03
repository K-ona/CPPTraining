// created by Kona @VSCode
// 最长上升子序列模板题: https://www.acwing.com/problem/content/898/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

int arr[100005]; 
int dp[100005]; 

// O(n^2)
void Solve_n2(int N, int arr[], int dp[]) {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[i]) dp[i] = std::max(dp[j] + 1, dp[i]); 
        }
    }
    cout << *std::max_element(dp + 1, dp + N + 1) << endl; 
}

// O(nlogn)
void Solve_nlogn(int N, int arr[]) {
    // 思路: 由于最终答案子序列肯定是连续的（有长度为5的上升子序列就有长度为1,2,3,4的上升子序列）
    // 可用该数组ans[i]表示以ans[i]结尾的上升子序列长度为i
    // 对于长度都为i的各上升子序列，明显保留最小的ans[i]即可，因为较大的ans[i]可用的话，较小的ans[i]也可用
    vector<int> ans; ans.reserve(N + 5); 
    int top = 0; 
    ans[top++] = arr[1]; 

    for (int i = 2; i <= N; ++i) {
        if (arr[i] > ans[top - 1]) ans[top++] = arr[i]; 
        else {
            *std::lower_bound(ans.begin(), ans.begin() + top, arr[i]) = arr[i]; 
        }
    }
    cout << top << endl; 
}

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    int N; 
    cin >> N; 
    for (int i = 1; i <= N; ++i) {
        cin >> arr[i]; 
    }
    arr[0] = -1e9 - 7; 

    Solve_nlogn(N, arr); 

    return 0;
}