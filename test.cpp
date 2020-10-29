#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define Redge(u) for (int k = h[u],to; k; k = ed[k].nxt)
#define REP(i,n) for (int i = 1; i <= (n); i++)
#define mp(a,b) make_pair<int,int>(a,b)
#define cls(s) memset(s,0,sizeof(s))
#define cp pair<int,int>
#define LL long long int
using namespace std;
const int maxn = 100005,maxm = 100005,INF = 1000000000;

inline int read(){
	int out = 0,flag = 1; char c = getchar();
	while (c < 48 || c > 57){if (c == '-') flag = -1; c = getchar();}
	while (c >= 48 && c <= 57){out = (out << 3) + (out << 1) + c - 48; c = getchar();}
	return out * flag;
}
inline int qpow(int a,LL b,int pr){
	int re = 1;
	for (; b; b >>= 1,a = 1ll * a * a % pr)
		if (b & 1) re = 1ll * re * a % pr;
	return re;
}
int P,fac[maxn],cnt;
void Sp(int x){
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0){
			fac[++cnt] = i;
			while (x % i == 0) x /= i;
		}
	if (x - 1) fac[++cnt] = x;
}
void work(){
	for (int i = 2; i < P; i++){
		int flag = true;
		for (int j = 1; j <= cnt; j++)
			if (qpow(i,(P - 1) / fac[j],P) == 1){
				flag = false;
				break;
			}
		if (flag){
			printf("%d\n",i);
			
		}
	}
}
int main(){
	P = read();
	Sp(P - 1);
	work();
	return 0;
}