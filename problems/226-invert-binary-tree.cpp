#include "testSuite.h"

using namespace std;

/// @problem invert binary tree
/// Starttime = 26-05-2026 21:32
///
/// @ Solution Go through each node and swap left and right?

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *invertTree(TreeNode *root) {
  if (!root)
    return nullptr;

  TreeNode *dummy = root->left;
  root->left = root->right;
  root->right = dummy;

  invertTree(root->left);
  invertTree(root->right);

  return root;
}

int main() {
  TestTimer timer;

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
  n4.left = &n7;

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
  // ExpectFalse(hasCycleBruteForce(&n1));
  // ExpectTrue(hasCycleBruteForce(&n4));

  ExpectFalse(hasCycle(&n1));
  ExpectTrue(hasCycle(&n4));
  ExpectFalse(hasCycle(&n6));
}
