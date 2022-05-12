int cols, rows;
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        cols = strs[0].size(); 
        rows = strs.size(); 
        int cnt = 0; 
        for (int i = 0; i < cols; ++i) {
            for (int j = 1; j < rows; ++j) {
                if (strs[j][i] < strs[j - 1][i]) {
                    ++cnt;
                    break;
                }
            }
        }
        return cnt; 
    }
};