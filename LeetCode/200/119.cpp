class Solution {
public:
    vector<int> getRow(int numRows) {
      ++numRows; 
      vector<vector<int>> ans(numRows);
      ans[0] = {1}; 
      for (int i = 1; i < numRows; ++i) {
        int sz = ans[i - 1].size();
        vector<int> tmp;
        tmp.reserve(sz + 1); 
        tmp.push_back(1);  
        for (int j = 0; j + 1 < sz; ++j) {
          tmp.push_back(ans[i - 1][j] + ans[i - 1][j + 1]);
        }
        tmp.push_back(1);  
        ans[i] = std::move(tmp); 
      }
      return ans.back(); 
    }
};