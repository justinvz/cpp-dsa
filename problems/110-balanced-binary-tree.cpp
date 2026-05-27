#include "testSuite.h"
#include <cstdlib>
#include <functional>

using namespace std;

/// Starttime = 27-05-2026 22:27
///
/// A height-balanced binary tree is a binary tree in which the depth of the two
/// subtrees of every node never differs by more than one.
///
/// I think what you can do is you can track the difference in depth for each
/// node, when doing that, you could see if the difference in more than one.
///
/// So, for example:
///
/// We have this tree
///
/// [3,9,20,null,null,15,17]
///
/// Use breadth first search.
///
/// order
///
/// 3
///
/// 9
///
/// 20
///
///

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

void Traverse(TreeNode *current, bool &balanced) {
  if (!current) {
    return;
  }

  Traverse(current->left, balanced);
  if (!balanced)
    return;

  Traverse(current->right, balanced);

  if (!balanced)
    return;

  balanced = abs(maxDepth(current->left) - maxDepth(current->right)) < 2;
  std::cout << "Node: " << current->val << " is balanced " << balanced
            << " Depth left " << maxDepth(current->left) << " Depth right "
            << maxDepth(current->right) << std::endl;
}

bool isBalanced(TreeNode *root) {

  bool isBalanced{true};
  Traverse(root, isBalanced);
  return isBalanced;
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

  // n4.left = &n2;
  n4.right = &n7;

  n2.left = &n1;
  n2.right = &n3;

  n7.left = &n6;
  n7.right = &n9;

  auto status = isBalanced(root);
  std::cout << "Is balanced result " << status << std::endl;

  // auto current = &n1;
  // while (current) {
  //   std::cout << current->val << std::endl;
  //   current = current->next;
  // }
  //
  // ExpectFalse(hasCycleBruteForce(&n1));
  // ExpectTrue(hasCycleBruteForce(&n4));
}
