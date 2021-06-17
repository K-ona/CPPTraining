//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <stack>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

int l[100005];
int r[100005];

class Solution {
public:
    int maximumScore(std::vector<int>& nums, int k) {
        // std::stack<int> St;
        int St[100005]; 
        int top = -1;  
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (!(~top) || nums[St[top]] <= nums[i]) {
                St[++top] = i; 
            }
            else {
                while(top >= 0 && nums[St[top]] > nums[i]) {
                    r[St[top]] = i - 1; 
                    // St.pop(); 
                    --top; 
                }
                St[++top] = i; 
                // St.push(i); 
            }
        }
        while (top >= 0)
        {
            /* code */
            r[St[top]] = nums.size() - 1; 
            // St.pop(); 
            --top;
        }
        
        
        for (int i = (int)nums.size() - 1; i >= 0; --i) {
            if (!(~top) || nums[St[top]] <= nums[i]) {
                // St.push(i); 
                St[++top] = i; 
            }
            else {
                while(top >= 0 && nums[St[top]] > nums[i]) {
                    l[St[top]] = i + 1; 
                    // St.pop(); 
                    --top; 
                }
                // St.push(i); 
                St[++top] = i; 
            }
        }
        while (top >= 0) {
            l[St[top]] = 0; 
            // St.pop(); 
            --top; 
        }

        ll ans = 0; 
        for (int i = 0; i < nums.size(); i++) {
            // cout << "i == " << i << " l[i] == " << l[i] << " r[i] == " << r[i] << endl; 
            if (r[i] >= k && l[i] <= k) {
                ans = std::max(ans, 1LL * nums[i] * (r[i] - l[i] + 1)); 
            }
        }
        return ans; 
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */


    return 0;
}