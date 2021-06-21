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
        std::stack<int> St;
        // int St[100005]; 
        // int top = -1;  
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (St.empty() || nums[St.top()] < nums[i]) {
                St.push(i); 
            }
            else {
                while(!St.empty()) {
                    r[St.top()] = i; 
                    St.pop(); 
                }
                St.push(i); 
            }
        }

        while(!St.empty()) St.pop();
        // int St[100005]; 
        // int top = -1;  
        for (int i = (int)nums.size(); i; --i) {
            if (St.empty() || nums[St.top()] < nums[i]) {
                St.push(i); 
            }
            else {
                while(!St.empty()) {
                    l[St.top()] = i; 
                    St.pop(); 
                }
                St.push(i); 
            }
        }

        for (int i = 0; i <= k; i++) {
            
        }

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