class MyCalendarThree {
  std::map<int, int> M;

 public:
  MyCalendarThree() {}

  int book(int start, int end) {
    M[start] += 1;
    M[end] -= 1;
    int cnt = 0;
    int max = 0;
    for (auto [_, x] : M) {
      cnt += x;
      max = std::max(max, cnt);
    }
    return max;
  }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */