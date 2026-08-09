#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

/// @problem invert binary tree

/// Starttime = 26-05-2026 21:30 end 22:42
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

int maxDepth(TreeNode *root) {
  if (!root)
    return 0;

  return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

int diameterOfBinaryTree(TreeNode *root) {
  if (!root)
    return 0;

  // Doesn't pass through the root..
  if (!root->left)
    return maxDepth(root);
  else if (!root->right)
    return maxDepth(root);
  else {
    return maxDepth(root->left) + maxDepth(root->right);
  }
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

  n4.left = &n2;
  n4.right = &n7;

  n2.left = &n1;
  n2.right = &n3;

  n7.left = &n6;
  n7.right = &n9;

  // auto current = &n1;
  // while (current) {
  //   std::cout << current->val << std::endl;
  //   current = current->next;
  // }
  //
  // EXPECT_FALSE(hasCycleBruteForce(&n1));
  // EXPECT_TRUE(hasCycleBruteForce(&n4));

  EXPECT_EQ(diameterOfBinaryTree(&n4), 4);
}
