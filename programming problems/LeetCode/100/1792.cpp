//created by Kona @VSCode
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;

struct node
{
    /* data */
    int t, p;  
    bool operator<(const node other) const {
        return 1.0 * (t - p) / t / (t + 1) < 1.0 * (other.t - other.p) / other.t / (other.t + 1);  
    }
};

class Solution {
public:
    double maxAverageRatio(std::vector<std::vector<int>>& classes, int extraStudents) {
        std::priority_queue<node> PQ; 
        
        for (auto x: classes) PQ.push({x[1], x[0]}); 
        while (!PQ.empty()) {
            cout << PQ.top().t << " " << PQ.top().p << endl;  
            PQ.pop(); 
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    return 0;
}