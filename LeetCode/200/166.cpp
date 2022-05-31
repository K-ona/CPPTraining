#include <string>
#include <map>

using std::map; 
using std::string;
using std::pair; 

class Solution {
public:
    string fractionToDecimal(long long numerator, long long denominator) {
        if (!numerator) return "0";
        map<pair<int, int>, int> M; 
        string res; 
        if ((numerator < 0) + (denominator < 0) == 1) res = "-", numerator = abs(numerator), denominator = abs(denominator);
        // cout << numerator << " " << denominator << endl;  
        
        long long cur = numerator / denominator; 
        long long mod = numerator % denominator; 
        // cout << "cur == " << cur << endl; 
        res += std::to_string(cur); 
        if (!mod) return res;
        res += ".";
        numerator -= cur * denominator;
        numerator *= 10; 

        // cout << numerator << " " << denominator << endl;  
        for (int i = res.size(); true; ++i) {
            if (M[{numerator, denominator}]) {
                res.insert(M[{numerator, denominator}], "("); 
                res += ")"; 
                break;
            }
            M[{numerator, denominator}] = i; 
            long long cur = numerator / denominator; 
            long long mod = numerator % denominator; 
            res += std::to_string(cur); 
            if (!mod) break;
            numerator -= cur * denominator;
            numerator *= 10; 
        }
        return res; 
    }
};