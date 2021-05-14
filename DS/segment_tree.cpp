//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

#define LOCAL_TEST
#define rep(i, a, n) for (int i = a; i<n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<pair<int, int>> VPII;
typedef map<int, int> MII;
const ll mod = 1000000007;
ll powmod(ll a, ll b) { ll res = 1; a %= mod; for (; b; b >>= 1) { if (b & 1) res = res * a % mod; a = a * a % mod;}return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}

const int maxn = 1e5 + 50; 
int wt[maxn];

struct SegTree
{
    int l, r, siz;
    ll w, laz;
}T[maxn * 4];

void push_up(int rt)
{
    T[rt].w = T[rt + rt].w + T[rt + rt + 1].w;
}

void push_dow(int rt)
{
    if(T[rt].laz)
    {
        T[rt + rt].w = T[rt + rt].w + 1LL * T[rt + rt].siz * T[rt].laz;
        T[rt + rt + 1].w = T[rt + rt + 1].w + 1LL * T[rt + rt + 1].siz * T[rt].laz;
        T[rt + rt].laz = T[rt + rt].laz + T[rt].laz;
        T[rt + rt + 1].laz = T[rt + rt + 1].laz + T[rt].laz;
        T[rt].laz = 0;
    }
}

void build(int rt, int l, int r)
{
    T[rt].l = l, T[rt].r = r, T[rt].siz = r - l + 1;
    T[rt].laz = 0;
    if(l == r)
    {
        T[rt].w = wt[l];
    }
    else
    {
        int mid = (l + r) >> 1;
        build(rt + rt, l, mid);
        build(rt + rt + 1, mid + 1, r);
        push_up(rt);
    }
}

void Add(int rt, int l, int r, int x)
{
    int L = T[rt].l, R = T[rt].r;
    if(l <= L && R <= r)
    {
        T[rt].w += 1LL * T[rt].siz * x;
        T[rt].laz += x;
        return ;
    }
    push_dow(rt);
    int mid = (L + R) >> 1;
    if(l <= mid) Add(rt + rt, l, r, x);
    if(r > mid) Add(rt + rt + 1, l, r, x);
    push_up(rt);
}

ll Sum(int rt, int l, int r)
{
    int L = T[rt].l, R = T[rt].r;
    if(l <= L && R <= r)
        return T[rt].w;
    push_dow(rt);
    int mid = (L + R) >> 1;
    ll res = 0;
    if(l <= mid) res += Sum(rt + rt, l, r);
    if(r > mid) res += Sum(rt + rt + 1, l, r);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */

    
    return 0;
}