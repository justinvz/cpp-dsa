#include <gtest/gtest.h>

#include <climits>
#include <limits>

using namespace std;

/// @problem invert binary tree
///
/// @starttime = 14:40
/// @end = 15:08

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

bool dfs(TreeNode *node, long long low, long long high) {
  if (!node)
    return true;

  if (node->val <= low || node->val >= high)
    return false;

  return dfs(node->left, low, node->val) && dfs(node->right, node->val, high);
}

bool isValidBST(TreeNode *root) {
  if (!root)
    return true;

  return dfs(root, LLONG_MIN, LLONG_MAX);
}
TEST(Problem, ExistingCases) {

  TreeNode n9(9);
  TreeNode n7(7);
  TreeNode n6(6);
  TreeNode n5(5);
  TreeNode n4(4);
  TreeNode n3(3);
  TreeNode n2(2);
  TreeNode n1(1);

  TreeNode *root = &n3;

  n3.left = &n1;
  n3.right = &n5;

  n5.right = &n7;
  n5.left = &n4;

  EXPECT_EQ(isValidBST(root), true);
}
