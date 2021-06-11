#include <iostream>
#include <vector>
using namespace std;

int solve(string &s) { // decrease 0
    vector<char> stk;
    // 000
    for (int i = 0; i < s.size(); i++) {
        if (stk.size() < 2) stk.push_back(s[i]);
        else {
            int sum = s[i] + stk.back() + stk[stk.size() - 2] - 3 * '0';
            if (sum == 0) stk.pop_back(), stk.pop_back();
            else stk.push_back(s[i]);
        }
    }
    vector<char> v;
    // 001
    for (int i = 0; i < stk.size(); i++) {
        if (v.size() < 2) v.push_back(stk[i]);
        else {
            int sum = stk[i] + v.back() + v[v.size() - 2] - 3 * '0';
            if (sum <= 1) v.pop_back(), v.pop_back();
            else v.push_back(stk[i]);
        }
    }

    int res = 0;
    for (auto x : v) {
        if (x == '1') res++;
        else res--;
    }
    return res;
}

int main() {

    int n;
    string s;
    while (cin >> n >> s) {
        string rs = s;
        for (auto &ch : rs) ch = (ch == '0') ? '1' : '0';

//      cout << solve(s) << ' ' << solve(rs) << endl;
        cout << max(solve(s), solve(rs)) << endl;
    }

    return 0;
}
