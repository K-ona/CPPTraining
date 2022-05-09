class Solution {
public:
    vector<int> diStringMatch(string s) {
        vector<int> res;
        res.reserve(s.size() + 1);
        int max = s.size(); 
        int min = 0; 
        for (const auto c: s) {
            if (c == 'I') {
                res.push_back(min++); 
            } else {
                res.push_back(max--); 
            }
        }
        res.push_back(max); 
        return res; 
    }
};