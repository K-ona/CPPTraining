#include <iostream>

class Solution {
public:
    double myPow(double a, int b) {
        double res = 1; 
        int sign = b > 0 ? 1 : -1; 
        b = std::abs(b); 
        for (; b; b /= 2) {
        if (b & 1)
            res = res * a ;
        a = a * a;
        }
        return sign == 1 ? res : 1.0 / res;
    }
};