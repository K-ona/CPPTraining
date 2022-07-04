class Solution {
 public:
  vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
    vector<vector<int>> res;
    res.reserve(arr.size() / 2);
    int min = 1e7;
    std::sort(arr.begin(), arr.end());
    for (int i = 1; i < arr.size(); ++i) {
      if (arr[i] - arr[i - 1] < min) {
        res.clear();
        res.emplace_back(vector<int>{arr[i - 1], arr[i]});
        min = arr[i] - arr[i - 1];
      } else if (arr[i] - arr[i - 1] == min) {
        res.emplace_back(vector<int>{arr[i - 1], arr[i]});
      }
    }
    return res;
  }
};