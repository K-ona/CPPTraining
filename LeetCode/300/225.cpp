class MyStack {
    std::queue<int> Q[2]; 
    int cur = 0; 
public:
    MyStack() {
    }
    
    void push(int x) {
        Q[cur].push(x); 
    }
    
    int pop() {
        while (!Q[cur].empty()) {
            if (Q[cur].size() == 1) {
                int res = Q[cur].front(); Q[cur].pop(); 
                cur ^= 1; 
                return res; 
            }
            Q[cur ^ 1].push(Q[cur].front()); Q[cur].pop(); 
        }
        return 0; 
    }
    
    int top() {
        int res; 
        while (!Q[cur].empty()) {
            res = Q[cur].front(); 
            Q[cur ^ 1].push(Q[cur].front()); Q[cur].pop(); 
        }
        cur ^= 1; 
        return res; 
    }
    
    bool empty() {
        if (Q[cur].empty()) return true; 
        return false; 
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */