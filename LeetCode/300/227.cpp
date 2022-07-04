#include <string>
#include <stack>
#include <map>
#include <unordered_map>

using std::string; 

const int N = 7;
enum class Operator {ADD, SUB, L_P, R_P, END}; 

class Solution {
    std::unordered_map<char, int> map{ {'+', 0}, {'-', 1}, {'*', 2}, {'/', 3}, {'(', 4}, {')', 5}, {'#', 6}}; 
    const char priority[N][N] = {
    /*      +      -      *      /      (     )      #*/
  /* + */  '>',   '>',   '<',   '<',   '<',  '>',   '>',
  /* - */  '>',   '>',   '<',   '<',   '<',  '>',   '>',
  /* * */  '>',   '>',   '>',   '>',   '<',  '>',   '>',
  /* / */  '>',   '>',   '>',   '>',   '<',  '>',   '>',
  /* ( */  '<',   '<',   '<',   '<',   '<',  '=',   ' ',
  /* ) */  ' ',   ' ',   ' ',   ' ',   ' ',  ' ',   ' ',
  /* # */  '<',   '<',   '<',   '<',   '<',  ' ',   '=',
    }; 
public:
    int calculate(string s) {
      s += '#'; 
      std::stack<int> opnd; 
      std::stack<int> optr; 
      optr.push(s.size() - 1); 
      for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ' ') continue;
        if (std::isdigit(s[i])) {
          int num = s[i] - '0'; 
          while (++i < s.size() && std::isdigit(s[i])) num = num * 10 - '0' + s[i]; 
          --i; 
          opnd.push(num); 
        } else {
          switch (priority[map[s[optr.top()]]][map[s[i]]])
          {
            case '<':
              optr.push(i); 
              break;
            case '=':
              optr.pop(); 
              break;
            case '>': {
              int pos = optr.top(); 
              char op = s[pos]; optr.pop(); 
              int num1 = opnd.top(); opnd.pop(); 
              int num2 = opnd.top(); opnd.pop(); 
            //   cout << num2 << " " << op << " " << num1 << endl; 
              if (op == '+') {
                opnd.push(num1 + num2); 
              } else if (op == '-') {
                opnd.push(num2 - num1); 
              } else if (op == '*') {
                opnd.push(num2 * num1); 
              } else {
                opnd.push(num2 / num1); 
              }
              --i; 
            }
              break;  
            default:
              // 不合法的表达式
              break;
          }
        }
      }
      return opnd.top(); 
    }
};
