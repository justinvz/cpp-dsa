#include "testSuite.h"

using namespace std;

/// @problem subtree of another tree
///
/// @Naive approach is to look for the root node of a subtree, and than traverse
/// both trees to check if they are the same.
///
/// Another approach is to not look at the root, but at the leave.
///
///

/// Starttime = 01-06-2026 21:46 finish with help of chat 22:27

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

bool CheckSubTree(TreeNode *root, TreeNode *subRoot) {
  if (!root && !subRoot)
    return true;

  if (!root || !subRoot)
    return false;

  if (root->val != subRoot->val)
    return false;

  return CheckSubTree(root->left, subRoot->left) ||
         CheckSubTree(root->right, subRoot->right);
}

bool Traverse(TreeNode *node, TreeNode *subRoot, int val) {
  if (!node)
    return false;

  if (CheckSubTree(node, subRoot)) {
    return true;
  }

  return Traverse(node->left, subRoot, val) ||
         Traverse(node->right, subRoot, val);
}

// Walk through tree looking for the sub root, if found, walk down each tree
// to check if nodes are inside, if there is any difference, return false;

bool isSubtree(TreeNode *root, TreeNode *subRoot) {
  if (!subRoot)
    return true;

  return Traverse(root, subRoot, subRoot->val);
}

int main() {
  TestTimer timer;

  TreeNode n5(5);
  TreeNode n4(4);
  TreeNode n3(3);
  TreeNode n2(2);
  TreeNode n1(1);

  n3.left = &n4;
  n3.right = &n5;

  n4.left = &n1;
  n4.right = &n2;

  TreeNode *root = &n3;

  ExpectTrue(isSubtree(root, &n4));
  // ExpectTrue(isSubtree(root, root));

  TreeNode n10(0);
  TreeNode n9(2);
  TreeNode n7(1);
  TreeNode n6(4);
  n9.left = &n10;

  n6.left = &n7;
  n6.right = &n9;

  // ExpectFalse(isSubtree(root, &n6));
}
