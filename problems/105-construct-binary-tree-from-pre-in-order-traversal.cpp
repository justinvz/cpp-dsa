#include "testSuite.h"
#include <unordered_map>

using namespace std;

/// Starttime = 12-07-2026 20:00
///
/// Algorithm goes as follows
///
/// Use preOrder te detirmine the root node,
///
/// use inOrder te detrimine the left and right pair.
/// The lowest index is always left, and the highest is alwasy right
///
///
///
/// Try again 19-07-2026 12:16

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *build(int preL, int preR, int inL, int inR,
                const vector<int> &preorder, const vector<int> &inorder,
                unordered_map<int, int> &pos) {
  if (preL > preR)
    return nullptr;

  int rootVal = preorder[preL];
  TreeNode *root = new TreeNode(rootVal);

  int k = pos[rootVal];
  int leftSize = k - inL;

  root->left =
      build(preL + 1, preL + leftSize, inL, k - 1, preorder, inorder, pos);

  root->right =
      build(preL + leftSize + 1, preR, k + 1, inR, preorder, inorder, pos);

  return root;
}

TreeNode *buildTree(vector<int> preorder, vector<int> inorder) {
  unordered_map<int, int> pos;

  for (int i = 0; i < inorder.size(); i++)
    pos[inorder[i]] = i;

  return build(0, preorder.size() - 1, 0, inorder.size() - 1, preorder, inorder,
               pos);
}

int main() {
  TestTimer timer;

  auto tree = buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
}
