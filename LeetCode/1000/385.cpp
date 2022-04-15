/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
#include <stack>
#include <string>

class Solution {
 public:
  NestedInteger deserialize(string s) {
    if (s[0] != '[') return NestedInteger(std::stoi(s));
    std::stack<NestedInteger> sn; 
    int n = s.size(); 
    for (int i = 0; i < n; ++i) {
      if (s[i] == ',') continue; 
      if (s[i] == '[') {
        sn.push(NestedInteger()); 
      } else if (s[i] == ']') {
        // cout << sn.size() << endl; 
        if (i == n - 1) continue; 
        auto cur = sn.top(); sn.pop(); 
        sn.top().add(cur); 
      } else {
        int sign = 1; 
        if (s[i] == '-') sign = -1, ++i;
        int cnt = 0; 
        while (isdigit(s[i])) {
          cnt = cnt * 10 + s[i++] - '0'; 
        }
        cnt *= sign; 
        --i; 
        sn.top().add(NestedInteger(cnt));
      }
    }
    return sn.top(); 
  }
};