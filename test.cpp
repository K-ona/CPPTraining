#include<bits/stdc++.h>

using namespace std;

vector<int> KMP(const string& S, const string& T)
{
    vector<int> Next;
    Next.push_back(-1);

    for (int i = 0, j = -1; i < T.size();) {
        if (j == -1 || T[i] == T[j]) {
            i++, j++;
            if (i != T.size() && T[j] == T[i]) Next.push_back(Next[j]);
            else Next.push_back(j);
        }
        else j = Next[j];
    }

    vector<int> res;
    for (int i = 0, j = 0; i < S.size() && j < (int)T.size();) {
        if (j == -1 || S[i] == T[j]) {
            i++, j++;
            if (j == T.size()) {
                res.push_back(i - j);
                j = Next[j];
            }
        }
        else j = Next[j];
    }

    return res;
}
int main()
{
    string s, t; 
	cin >> s >> t;
	vector<int> res = KMP(s, t);
	for(auto pos:res)
	{
		cout << pos + 1 << endl;
	}
    return 0;
}

