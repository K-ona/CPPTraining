tail -n +10 file.txt | head -1

# 注意：tail -n +10 与 tail -n 10 不一样，-n +10 表示从第 10 行开始显示，若文件不足 10 行则什么也不会输出；-n 10 表示显示最后的 10 行。

# 作者：gump-milkha
# 链接：https://leetcode.cn/problems/tenth-line/solution/tail-head-by-milkha-x8w9/
# 来源：力扣（LeetCode）
# 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。