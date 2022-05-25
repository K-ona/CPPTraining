#include <vector>
#include <string>
#include <iostream>

using std::vector; 
using std::string;

int stk[10000];
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int top = 0;
        for (const auto& x: tokens) {
            if (x == "+") stk[top - 1] = stk[top - 2] + stk[--top];
            else if (x == "-") stk[top - 1] = stk[top - 2] - stk[--top];
            else if (x == "*") stk[top - 1] = stk[top - 2] * stk[--top];
            else if (x == "/") stk[top - 1] = stk[top - 2] / stk[--top];
            else stk[top++] = std::stoi(x); 
        }
        return stk[0]; 
    }
};
