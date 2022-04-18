class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res; 
        dfs(res, 0, n); 
        return res; 
    }

    void dfs(std::vector<int>& res, int num, int max) {
        for (int i = 0; i < 10; ++i) {
            if (num * 10 + i > 0 and num * 10 + i <= max) {
                res.push_back(num * 10 + i);
                dfs(res, num * 10 + i, max);
            }
        }
    }
};