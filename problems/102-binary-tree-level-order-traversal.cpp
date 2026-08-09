#include <gtest/gtest.h>

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Start 19:54 - 20:13 (on hold) - 21-57 start again finsh 22:12
//
//
// Given the root of a binary tree, return the level order traversal of its
// nodes'values, from left ot right

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

vector<vector<int>> levelOrder(TreeNode *root) {
  if (!root) {
    return vector<vector<int>>{};
  }
  queue<TreeNode *> nodeQueue;
  nodeQueue.push(root);

  vector<vector<int>> result;

  while (!nodeQueue.empty()) {
    int len = nodeQueue.size();
    vector<int> currentLevel;

    for (int i = 0; i < len; i++) {
      TreeNode *node = nodeQueue.front();
      nodeQueue.pop();

      currentLevel.push_back(node->val);

      if (node->left != nullptr) {
        nodeQueue.push(node->left);
      }

      if (node->right != nullptr) {
        nodeQueue.push(node->right);
      }
    }
    result.push_back(currentLevel);
  }

  return result;
}

TEST(Problem, ExistingCases) {

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

  for (const auto &row : levelOrder(&node6)) {
    for (int x : row) {
      cout << x << " ";
    }
    cout << endl;
  }

  SUCCEED();
}
