class Solution {
public:
    bool isPalindrome(string s) {
        int len = s.size();
        int l = 0, r = len - 1; 
        while (l < r) {
            while (l + 1 < len and !(isalpha(s[l]) or isdigit(s[l]))) ++l; 
            while (r - 1 >= 0 and !(isalpha(s[r]) or isdigit(s[r]))) --r; 
            if (l > r) break; 
            if (std::tolower(s[l++]) != std::tolower(s[r--])) return false; 
        }
        return true; 
    }
};