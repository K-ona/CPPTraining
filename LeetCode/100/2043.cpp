// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

using ll = long long; 

ll M[100005]; 
class Bank {

    int n = 0; 
public:
    Bank(vector<ll>& balance) {
        n = 0; 
        for (const auto x: balance) {
            M[++n] = x; 
        }
    }
    
    bool transfer(int account1, int account2, ll money) {
        if (account1 < 1 or account1 > n or account2 < 1 or account2 > n) return false; 
        if (M[account1] < money) return false; 
        M[account2] += money; 
        M[account1] -= money; 
        return true; 
    }
    
    bool deposit(int account, ll money) {
        if (account < 1 or account > n) return false; 
        M[account] += money; 
        return true; 
    }
    
    bool withdraw(int account, ll money) {
        if (account < 1 or account > n) return false; 
        if (M[account] < money) return false; 
        M[account] -= money; 
        return true; 
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */

int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}