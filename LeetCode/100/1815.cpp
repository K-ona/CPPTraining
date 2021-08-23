//created by Kona @VSCode
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
    typedef long long ll;
    std::unordered_map<ll,int>M;
    int batchSize;
    //cur表示目前左边的余数，state表示剩余顾客的分布
    int dfs(int cur,ll state){
        if(M.count(state))return M[state];
        if(!state)return M[state]=0;
        int res=0;
        for(int i=1;i<batchSize;i++){
            //如果还有余数为i的顾客，就尝试令他作为下一波顾客
            if((state>>(i*5))%32){
                int temp=dfs((cur+i)%batchSize,state-(1ll<<(i*5)));
                res=std::max(res,cur?temp:temp+1);
            }
        }
        return M[state]=res;
    }
public:
    int maxHappyGroups(int _batchSize, vector<int>& groups) {
        batchSize=_batchSize;
        ll state=0;
        int mod0=0;
        for(int a:groups){
            a%=batchSize;
            if(!a)mod0++;//余数为0直接贪心作为最左边的顾客
            else state+=1ll<<(a*5);
        }
        return mod0+dfs(0,state);
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