//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

// 模拟
class Solution {
public:
    int findTheWinner(int n, int k) {
        std::list<int> cir;  
        for (int i = 1; i <= n; ++i) {
            cir.push_back(i); 
        }
        auto it = cir.begin(); 
        while (cir.size() > 1) {
            int kk = k; 
            while (--kk) {
                it++; 
                if (it == cir.end()) it = cir.begin(); 
            }
            cir.erase(it++); 
            if (it == cir.end()) it = cir.begin(); 
        }
        return cir.front(); 
    }
};

// dp
class Solution {
public:
    int f(int n, int k) {
        if (n == 1) return 0;
        return (f(n - 1, k) + k) % n;
    }
    int findTheWinner(int n, int k) {
        return f(n, k) + 1;
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
