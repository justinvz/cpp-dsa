#include <gtest/gtest.h>

#include <queue>

using namespace std;

/// @start time 18:45
/// @stop time 20:02
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

// dfs untill last node, and than move k up. I think best method is to always
// queue last tree kth node?
void dfs(TreeNode *node, int &k, int &result) {
  if (!node)
    return;

  dfs(node->left, k, result);

  k--;
  if (k == 0) {
    result = node->val;
    return;
  }

  if (k < 0) {
    return;
  }

  dfs(node->right, k, result);
}

int kthSmallest(TreeNode *root, int k) {
  if (!root)
    return true;

  int result;

  dfs(root, k, result);
  return result;
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

  TreeNode *root = &n5;

  n5.left = &n3;
  n3.left = &n2;
  n2.left = &n1;

  n3.right = &n4;
  n5.right = &n6;

  EXPECT_EQ(kthSmallest(root, 1), 1);
  EXPECT_EQ(kthSmallest(root, 2), 2);
  EXPECT_EQ(kthSmallest(root, 3), 3);
  EXPECT_EQ(kthSmallest(root, 4), 4);
  EXPECT_EQ(kthSmallest(root, 5), 5);
  EXPECT_EQ(kthSmallest(root, 6), 6);
}
