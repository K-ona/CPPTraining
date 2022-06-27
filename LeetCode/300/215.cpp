class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    std::priority_queue<int> Q;
    for (int x : nums) {
      Q.push(x);
    }
    while (--k) {
      Q.pop();
    }
    return Q.top();
  }
};