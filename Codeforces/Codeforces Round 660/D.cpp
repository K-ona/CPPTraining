#include <bits/stdc++.h>

#define Vanya Unstoppable

using namespace std;

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n;
    cin >> n;
    
    long long a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    set < int > s;
    for (int i = 0; i < n; ++i) {
        s.insert(i);
    }
    
    int b[n];
    vector < int > sz(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i]; --b[i];
        if (b[i] == -2) continue;
        ++sz[b[i]];
        if (sz[b[i]] == 1) {
            s.erase(b[i]);
        }
    }
    
    long long sum = 0;
    vector < int > ans[2];
    
    while (!s.empty()) {
        int v = *s.begin();
        s.erase(s.begin());
        int w = b[v];
        sum += a[v];
        if (a[v] >= 0) {
            if (w >= 0) {
                a[w] += a[v];
            }
            ans[0].push_back(v);
        } else {
            ans[1].push_back(v);
        }
        
        if (w >= 0) {
            --sz[w];
            if (sz[w] == 0) {
                s.insert(w);
            }
        }
    }
    
    cout << sum << endl;
    for (int to : ans[0]) cout << to + 1 << ' ';
    
    reverse(ans[1].begin(), ans[1].end());
    
    for (int to : ans[1]) cout << to + 1 << ' ';
    cout << endl;
}