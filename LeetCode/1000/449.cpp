/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
int dis[10005]; 
vector<int> seq;
class Codec {
    void dfs(string& s, TreeNode* root) {
        if (!root) return; 
        s += std::to_string(root->val) + " "; 
        dfs(s, root->left);
        dfs(s, root->right);
    }

    TreeNode* deserialization(int l, int r) { 
        // cout << l << " " << r << endl; 
        if (r < l) return nullptr; 
        TreeNode* root = new TreeNode(seq[l]); 
        // cout << "dis[l] == " << dis[l] << endl; 
           
        root->left = deserialization(l + 1, dis[l] - 1); 
        root->right = deserialization(dis[l], r); 
        return root; 
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res; 
        dfs(res, root);
        return res; 
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        seq.resize(0); 
        seq.reserve(10000); 
        istringstream stream(data);
        int x; 
        while (stream >> x) {
            seq.push_back(x); 
        }
        std::stack<int> stk; 
        for (int i = 0; i < seq.size(); ++i) {
            dis[i] = i + 1; 
            if (stk.empty()) stk.push(i); 
            else if (seq[stk.top()] > seq[i]) stk.push(i); 
            else {
                while (!stk.empty() and seq[stk.top()] < seq[i]) {
                    dis[stk.top()] = i; 
                    stk.pop();
                }
                stk.push(i); 
            }
        }
        while (!stk.empty()) {
            dis[stk.top()] = seq.size(); 
            stk.pop();
        }
        return deserialization(0, seq.size() - 1); 
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;