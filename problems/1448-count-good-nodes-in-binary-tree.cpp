#include "testSuite.h"

using namespace std;

/// @problem invert binary tree

/// Starttime = 29-06-2026 22:51
///
/// Second attempt
/// Starttime = 05-07-2026 13:41
///
/// Finished brute force at 14:13
/// Finished optimal solution at 14:32
///
/// Total time = 0:51

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

int Traverse(TreeNode *node, int highestValue) {
  if (!node)
    return 0;
  int good = 0;

  if (node->val >= highestValue) {
    good = 1;
    highestValue = node->val;
  }

  good += Traverse(node->left, highestValue);
  good += Traverse(node->right, highestValue);

  return good;
}

int goodNodes(TreeNode *root) { return Traverse(root, root->val); }

int main() {
  TestTimer timer;

  TreeNode n9(9);
  TreeNode n7(7);
  TreeNode n6(5);
  TreeNode n5(1);
  TreeNode n4(4);
  TreeNode n3(3);
  TreeNode n2(1);
  TreeNode n1(3);

  TreeNode *root = &n1;

  n1.left = &n2;
  n2.left = &n3;

  n1.right = &n4;
  n4.left = &n5;
  n4.right = &n6;

  ExpectEq(goodNodes(root), 4);
}
