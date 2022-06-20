class Solution {
public:
    bool isHappy(int n) {
        unordered_map<int, int> M; 
        while (n != 1) {
            if (M.find(n) != M.end()) return false;
            ++M[n]; 
            n = cal(n); 
        }
        return true; 
    }

    int cal(int n) {
        int res = 0; 
        while (n) {
            res += (n % 10) * (n % 10); 
            n /= 10; 
        }
        return res; 
    }
};