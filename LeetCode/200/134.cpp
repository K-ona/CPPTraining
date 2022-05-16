class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
      int len = static_cast<int>(gas.size());
      for (int i = 0; i < len; ++i) {
        gas[i] -= cost[i]; 
      }
      
      int sum = 0; 
      int Min = 0;
      int mini = -1;  
      for (int i = 0; i < len; ++i) {
        sum += gas[i]; 
        if (sum < Min) {
            Min = sum; 
            mini = i; 
        }
      }
      if (sum >= 0)
        return (mini + 1) % len; 
      return -1; 
    }
};