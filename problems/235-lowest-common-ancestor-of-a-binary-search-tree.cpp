
#include "testSuite.h"

using namespace std;

// Start 19:14 finish 19:41

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {

  TreeNode *node = root;

  while (node != nullptr) {
    // Search in subtree
    if (p->val < node->val && q->val < node->val) {
      node = node->left;
    } else if (p->val > node->val && q->val > node->val) {
      node = node->right;
    } else { // Split happend
      return node;
    }
  }

  return nullptr;
}

int main() {
  TestTimer timer;

  TreeNode node1(1);
  TreeNode node2(2);
  TreeNode node3(3);
  TreeNode node4(4);
  TreeNode node5(5);
  TreeNode node6(6);
  TreeNode node7(7);
  TreeNode node8(8);
  TreeNode node9(9);

  node6.left = &node2;
  node6.right = &node8;

  node8.left = &node7;
  node8.right = &node9;

  auto result = lowestCommonAncestor(&node6, &node2, &node8);
  ExpectEq(result->val, node6.val);

  result = lowestCommonAncestor(&node6, &node7, &node9);
  ExpectEq(result->val, node8.val);
}
