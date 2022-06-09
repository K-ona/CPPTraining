#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string_view, int> cnt; 
        string_view sv(s); 
        for (int i = 0; i + 9 < sv.size(); ++i) {
            ++cnt[sv.substr(i, 10)]; 
            // cout << sv.substr(i, 10) << " " << cnt[sv.substr(i, 10)] << endl;
        }
        vector<string> res; 
        res.reserve(10000); 
        for (auto& [k, v]: cnt) {
            if (v > 1)
                res.push_back(std::string(k)); 
        }
        return res; 
    }
};

// hash
class Solution {
    const int L = 10;
    unordered_map<char, int> bin = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        int n = s.length();
        if (n <= L) {
            return ans;
        }
        int x = 0;
        for (int i = 0; i < L - 1; ++i) {
            x = (x << 2) | bin[s[i]];
        }
        unordered_map<int, int> cnt;
        for (int i = 0; i <= n - L; ++i) {
            x = ((x << 2) | bin[s[i + L - 1]]) & ((1 << (L * 2)) - 1);
            if (++cnt[x] == 2) {
                ans.push_back(s.substr(i, L));
            }
        }
        return ans;
    }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode.cn/problems/repeated-dna-sequences/solution/zhong-fu-de-dnaxu-lie-by-leetcode-soluti-z8zn/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。