class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    vector<pair<int, int>> Con = {{INT_MAX, 0}, {INT_MIN, 0}};
    for (int i = 0; i < nums.size(); ++i) {
      bool exist = false;
      for (int j = 0; j < 2; ++j) {
        if (nums[i] == Con[j].first) {
          ++Con[j].second;
          exist = true;
          break;
        }
      }
      if (!exist)
        for (int j = 0; j < 2; ++j) {
          if (!Con[j].second) {
            Con[j].first = nums[i];
            Con[j].second = 1;
            exist = true;
            break;
          }
        }
      if (!exist) {
        for (int j = 0; j < 2; ++j) {
          --Con[j].second;
        }
      }
      // cout << Con[0].first << " " << Con[0].second << " ";
      // cout << Con[1].first << " " << Con[1].second << endl;
    }
    vector<int> res;
    for (auto [num, _] : Con) {
      int cnt = 0;
      for (int i = 0; i < nums.size(); ++i) {
        if (num == nums[i])
          cnt++;
      }
      if (cnt > nums.size() / 3)
        res.push_back(num);
    }
    return res;
  }
};