//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#define LOCAL_TEST
typedef long long ll;
using std::string;
using std::vector;  
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        std::unordered_map<string, string> Map; 
        for (auto x: knowledge) {
            Map[x[0]] = x[1];
        }
        string res = ""; 
        int pre = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == '(') {if (i) res += string(s.begin() + pre, s.begin() + i); pre = i + 1; }
            if (s[i] == ')') {
                auto tmp =  Map[string(s.begin() + pre, s.begin() + i)];
                if (tmp == "")
                    res += "?";
                else res += tmp;
                pre = i + 1; 
            }
        }
        if (pre != (int)s.size()) res += string(s.begin() + pre, s.end());
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