int cat[20]; 

int init() {
    cat[0] = cat[1] = 1; 
    for (int i = 2; i < 20; ++i) {
        for (int j = 0; j < i; ++j)
            cat[i] += cat[j] * cat[i - 1 - j];
    }
    return 0;
}

class Solution {
public:
    int numTrees(int n) {
        static int x = init(); 
        return cat[n]; 
    }
};