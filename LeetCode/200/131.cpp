bool valid[20][20]; 
int len; 
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        ans.reserve(1024);
        len = s.size(); 
        memset(valid, 0, sizeof(valid)); 
        for (int i = 0; i < len; ++i) {
            for (int j = i; j < len; ++j) {
                int ti = i, tj = j;
                while (tj >= ti) {
                    if (s[ti] != s[tj]) break;
                    ++ti, --tj;
                }
                if (tj < ti) valid[i][j] = true;
            }
        }
        vector<string> stk;
        stk.reserve(20);
        dfs(ans, stk, s, 0);
        return ans; 
    }

    void dfs(vector<vector<string>>& ans, vector<string>& stk, string& s, int begin) {
        if (begin == len) {
            ans.push_back(stk);
            return ;
        }
        for (int i = begin; i < len; ++i) {
            if (valid[begin][i]) {
                stk.push_back(s.substr(begin, i - begin + 1)); 
                dfs(ans, stk, s, i + 1); 
                stk.pop_back(); 
            }
        }
    }
};