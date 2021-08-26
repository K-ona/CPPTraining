//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>

// #define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
    const string ss = "aeiou#"; 
public:
    int longestBeautifulSubstring(string &word) {
        int res = 0, ind = 0; 
        int l = 0, r = 0; 
        // 第一个子串的l
        while(r + 1 < word.size() && word[r] != 'a') ++r; 
        l = r; 
        for (; r != word.size(); ++r) {
            if (word[r] == ss[ind + 1]) {
                ++ind; 
            }
            else if (word[r] != ss[ind]){
                // 更新答案
                if (ind == 4) res = std::max(res, r - l); 
                ind = 0; 
                // 找下一个l
                while(r + 1 < word.size() && word[r] != 'a') ++r;
                l = r; 
            }
        }
        // 注意最后一个区间
        if (ind == 4) res = std::max(res, r - l); 
        return res; 
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