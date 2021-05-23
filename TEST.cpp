#include <iostream>
#include <string>
#include <bits/stdc++.h>

using std::cin;
using std::string;
using std::endl;
using std::cout;

int main()
{
    int n, m; 
    cin >> n; 
    std::vector<std::vector<int>> sche(n, std::vector<int>(n)); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> sche[i][j];
            --sche[i][j];  
        }
    }

    std::map<std::pair<int, int>, int> Map; 
    Map[{2, 1}] = 2;
    int y = 1, t = 2, len = 505 * 505; 
    for (int i = 3; i < len && i < m; i++) {
        int tmp = sche[y][t]; y = t; t = tmp; 
        if (Map[{t, y}]) {
            int sep = i - Map[{t, y}]; 
        
        } 
        else {
            Map[{t, y}] = i; 
        }
    } 
    cout << sche[t][y] << endl; 

    return 0;
}