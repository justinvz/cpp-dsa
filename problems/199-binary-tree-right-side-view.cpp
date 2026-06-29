#include "testSuite.h"
#include <queue>

using namespace std;

// Start 22:14 finish 22:28

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

vector<int> rightSideView(TreeNode *root) {
  if (!root) {
    return {};
  }
  queue<TreeNode *> nodeQueue;

  nodeQueue.push(root);

  vector<int> result;

  while (!nodeQueue.empty()) {
    int len = nodeQueue.size();

    bool first = true;
    for (int i = 0; i < len; i++) {
      TreeNode *node = nodeQueue.front();
      nodeQueue.pop();

      // Only push first
      if (first) {
        result.push_back(node->val);
        first = false;
      }

      if (node->right != nullptr) {
        nodeQueue.push(node->right);
      }

      if (node->left != nullptr) {
        nodeQueue.push(node->left);
      }
    }
  }

  return result;
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

  node1.left = &node2;
  node1.right = &node3;

  node2.left = &node4;
  node2.right = &node5;

  node3.left = &node6;
  node3.right = &node7;

  ExpectEq(rightSideView(&node1), {1, 3, 7});
}
