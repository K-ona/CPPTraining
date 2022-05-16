class Solution {
public:
    bool oneEditAway(string first, string second) {
        if (first.size() > second.size()) std::swap(first, second); 
        int m = second.size();
        int n = first.size();
        if (m - n > 1) return false; 
        int cnt = 0; 
        for (int i = 0, j = 0; i < n and j < m; ) {
            if (first[i] == second[j]) {
                ++i, ++j; 
            } else {
                ++cnt; 
                if (n != m) {
                    ++j;
                } else {
                    ++i; ++j;
                }
            }
        }
        // cout << cnt << endl; 
        return cnt <= 1; 
    }
};