#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool findPlalidrome(string& s, int min,vector<int> &halfLanArr)
{
    const int len = s.size();
    if (len < min)
    {
        return false;
    }
    int rights = 0;
    int rightc = 0;
    int center = 0;
    for (int i = 0; i < len; i++)
    {
        bool needCalc = true;
        if (rights > i)
        {
            int left = 2 * rightc - i;
            halfLanArr[i] = halfLanArr[left];
            if (i + halfLanArr[i] > rights)
            {
                halfLanArr[i] = rights - i;
            }
            if (i + halfLanArr[i] < rights)
            {
                needCalc = false;
            }
        }
        if (needCalc)
        {
            while (i - 1 - halfLanArr[i] >= 0 && i + 1 + halfLanArr[i] < len)
            {
                if (s[i + 1 + halfLanArr[i]] == s[i - 1 - halfLanArr[i]])
                {
                    halfLanArr[i]++;
                }
                else
                {
                    break;
                }
            }
            rights = i + halfLanArr[i];
            rightc = i;
        }
    }
    return true;
}
bool cmp(int i, int j) {
    return i > j;
}

int main()
{
    int len, min;
    string s;
    cin >> len >> min;
    cin >> s;
    vector<int> halfLanArr(len, 0);
    if (!findPlalidrome(s, min, halfLanArr)) {
        cout<< -1;
        return 0;
    }
    sort(halfLanArr.begin(), halfLanArr.end(),cmp);
    long long ans = 1;
    for (int i = 0; i <min; i++)
    {
        ans = ans * (2 * halfLanArr[i] + 1) % 1000000007;
    }
    cout << ans % (1000000007) << endl;
    return 0;
}