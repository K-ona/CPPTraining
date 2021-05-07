//created by Kona @VSCode
#include<bits/stdc++.h>

using namespace std;

// #define LOCAL_TEST
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

class A
{
private:
    /* data */
    int x, y; 
public:
    A(/* args */);
    ~A();
};

A::A(/* args */)
{
    cout << "construct" << endl; 
}

A::~A()
{
    cout << "deconstruct" << endl; 
}


int main()
{
    ios_base::sync_with_stdio(false); 
    #ifdef LOCAL_TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    /* code */
    // A a;

    {
        // unique_ptr<A> p(new A()); 
        // unique_ptr<A> p2 = make_unique<A>(); //safer about exception

        // unique_ptr<A> tmp = p; error

        shared_ptr<A> q(new A()); // low efficiency
        weak_ptr<A> weakp; 
        {
            shared_ptr<A> q1 = make_shared<A>(); // 
            q = q1;  //ok
            weakp = q1; 
        }
        cout << "get out of scope" << endl; 
    }


    return 0;
}