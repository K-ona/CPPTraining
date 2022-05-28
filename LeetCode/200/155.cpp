#include <set>
#include <stack>

class MinStack {
  std::stack<int> stk;
  std::stack<int> smin;

 public:
  MinStack() {}

  void push(int val) {
    stk.push(val); 
    if (!smin.empty()) 
      smin.push(std::min(val, smin.top()));
    else 
      smin.push(val); 
  }

  void pop() {
    smin.pop();     
    stk.pop();
  }

  int top() { 
    return stk.top(); 
  }

  int getMin() { 
    return smin.top(); 
  }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */