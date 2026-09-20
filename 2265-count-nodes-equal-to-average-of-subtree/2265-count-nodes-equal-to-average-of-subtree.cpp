/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int answer = 0;

    pair<int, int> solve(TreeNode* node) {
        if (node == NULL)
            return {0, 0};

        pair<int, int> left = solve(node->left);
        pair<int, int> right = solve(node->right);

        int totalSum = node->val + left.first + right.first;
        int totalCount = 1 + left.second + right.second;

        if (node->val == totalSum / totalCount)
            answer++;

        return {totalSum, totalCount};
    }

    int averageOfSubtree(TreeNode* root) {
        solve(root);
        return answer;
    }
};