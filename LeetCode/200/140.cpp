string subs[22][22];
bool valid[22][22];
int len; 
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> ans;
        vector<int> stk; 
        stk.reserve(20); 
        unordered_map<string, bool> M;         
        for (auto& x: wordDict) {
            M[x] = true;
        }
        memset(valid, 0, sizeof(valid)); 
        len = s.size(); 
        for (int i = 0; i < len; ++i) {
            for (int j = i; j < len; ++j) {
                subs[i][j] = s.substr(i, j - i + 1); 
                if (M[subs[i][j]])
                    valid[i][j] = true; 
            }
        }

        stk.push_back(0); 
        dfs(ans, stk, 0); 
        return ans; 
    }

    void dfs(vector<string>& ans, vector<int>& stk, int pos) {
        if (pos == len) {
            int sz = stk.size();
            string res; 
            for (int i = 1; i < sz; ++i) {
                res += subs[stk[i - 1]][stk[i] - 1] + " "; 
            }
            res.pop_back(); 
            ans.push_back(std::move(res)); 
            return ;
        }
        for (int i = pos; i < len; ++i) {
            if (valid[stk.back()][i]) {
                stk.push_back(i + 1);
                dfs(ans, stk, i + 1);
                stk.pop_back();
            }
        }
    }

};