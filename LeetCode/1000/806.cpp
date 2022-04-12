class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int n = s.size(); 
        int cur = 0, lines = 1; 
        for (int i = 0; i < n; ++i) {
            if (cur + widths[s[i] - 'a'] <= 100) {
                cur += widths[s[i] - 'a'];
            } else {
                ++lines;
                cur = widths[s[i] - 'a'];; 
            }
        }
        return {lines, cur};
    }
};