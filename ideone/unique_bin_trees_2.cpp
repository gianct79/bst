#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(v), left(l), right(l) {};
};

TreeNode* clone(TreeNode* root, int offset) {
    if (!root) {
        return root;
    }
    return new TreeNode(root->val + offset, clone(root->left, offset), clone(root->right, offset));
}

vector<TreeNode*> generateTrees(int n) {
    if (n == 0) {
        return {};
    }
    unordered_map<int, vector<TreeNode*>> m;
    m[0].push_back(nullptr);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; j++) {
            for (auto nodeL : m[j]) {
                for (auto nodeR : m[i - j - 1]) {
                    auto node = new TreeNode(j + 1);
                    node->left = nodeL;
                    node->right = clone(nodeR, j + 1);
                    m[i].push_back(node);
                }
            }
        }
    }
    return m[n];
}

int main() {
    auto res = generateTrees(5);
    cout << res.size() << '\n';
    
    return 0;
}
