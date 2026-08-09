#include <gtest/gtest.h>

#include <algorithm>

using namespace std;

/// @problem invert binary tree

/// Starttime = 26-05-2026 21:50 end 22:20
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
  if (root == nullptr)
    return -1;

  int lheight = maxDepth(root->left);
  int rheight = maxDepth(root->right);

  return max(lheight, rheight) + 1;
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

  TreeNode *root = &n4;

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

  EXPECT_EQ(maxDepth(&n4), 2);
}
