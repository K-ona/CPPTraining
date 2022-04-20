class Solution {
public:
    int lengthLongestPath(string input) {
        int n = input.size();
        int pos = 0;
        int ans = 0;
        stack<int> st;

        while (pos < n) {
            /* 检测当前文件的深度 */
            int depth = 1;
            while (pos < n && input[pos] == '\t') {
                pos++;
                depth++;
            }
            /* 统计当前文件名的长度 */   
            int len = 0; 
            bool isFile = false;     
            while (pos < n && input[pos] != '\n') {
                if (input[pos] == '.') {
                    isFile = true;
                }
                len++;
                pos++;
            }
            /* 跳过换行符 */
            pos++;

            while (st.size() >= depth) {
                st.pop();
            }
            if (!st.empty()) {
                len += st.top() + 1;
            }
            if (isFile) {
                ans = max(ans, len);
            } else {
                st.emplace(len);
            }
        }
        return ans;
    }
};

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/longest-absolute-file-path/solution/wen-jian-de-zui-chang-jue-dui-lu-jing-by-fi0r/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。