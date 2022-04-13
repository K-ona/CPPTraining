class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos = n + m; 
        int i = m; 
        int j = n;
        while (i && j) {
            if (nums1[i - 1] < nums2[j - 1]) nums1[--pos] = nums2[--j]; 
            else nums1[--pos] = nums1[--i]; 
        }
        while (j) {
            nums1[--pos] = nums2[--j]; 
        }
    }
};