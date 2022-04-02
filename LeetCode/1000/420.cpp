// created by Kona @VSCode
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>

#include <string.h>

#define LOCAL_TEST
typedef long long ll;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

// 官方题解
int strongPasswordChecker(char * s){

    bool has_digit = false, has_lower = false, has_upper = false;
    int  len = 0;
    char c;

    int cnt_mod[3] = {0, 0, 0}; /* 统计 3n,3n+1,3n+2 型连续子串的数量 */
    int n_modify = 0; /* 修改次数 */

    while (c = s[len]) {
        /* 统计字符类型 */
        switch (c) {
            case '0' ... '9': has_digit = true; break;
            case 'a' ... 'z': has_lower = true; break;
            case 'A' ... 'Z': has_upper = true; break;
        }

        /* 连续子串长度 */
        int i = len;
        while (s[++i] == c);
        int l = i - len;

        if (l >= 3) {
            n_modify += l / 3; /* 后续修改数等于重复长度/3 */
            cnt_mod[l % 3]++;
        }

        len = i;

    }

    /* 缺少的字符类型数目, 下界 */
    int n_missing_ctype = !has_digit+ !has_upper+ !has_lower;

    /* 过短，插入缺少的字符数量 */
    if (len < 6) return std::max(6-len, n_missing_ctype);

    /* 长度合法，修改去除连续子串 */
    if (len <= 20) return std::max(n_modify, n_missing_ctype);

    /* 过长，还可以删除 len - 20 个字符 */
    int n_remove = len - 20;
    
    /* 3n 型子串无法完全变为 3n+2 型，
        每个需要 1 次删除，
        只能把 n_remove 个变为 3n+2 型
        减少 n_remove 次后续修改
        */
    if (n_remove < cnt_mod[0]) 
        return std::max(n_modify - n_remove, n_missing_ctype) + len - 20;

    /* 3n 型全部变为 3n+2 型 */
    n_remove -= cnt_mod[0];
    n_modify -= cnt_mod[0];

    /* 3n+1 型无法完全变为 3n+2 型， 
        每个需要 2 次删除， 
        减少 n_remove/2 次后续修改
        */
    if (n_remove < cnt_mod[1] * 2)
        return std::max(n_modify - n_remove/2, n_missing_ctype) + len - 20;
    
    n_remove -= cnt_mod[1] * 2;
    n_modify -= cnt_mod[1];

    return std::max(n_modify - n_remove/3, n_missing_ctype) + len - 20;
}


int main() {
  std::ios_base::sync_with_stdio(false);
#ifdef LOCAL_TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  /* code */

  return 0;
}