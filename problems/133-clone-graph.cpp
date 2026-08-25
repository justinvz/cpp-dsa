#include <gtest/gtest.h>

#include <memory>
#include <print>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// @start 2026-08-05 21:34 finish 21:44
//

/// @problem 133. Clone Graph
/// @difficulty Medium
///
/// Given a reference to a node in a connected undirected graph, return a deep
/// copy of the graph.
///
/// Each node in the graph contains an integer value and a list of its
/// neighbors:
///
/// class Node {
/// public:
///   int val;
///   vector<Node *> neighbors;
/// };
///
/// The graph is represented in the test cases using an adjacency list. The
/// value of each node is the same as its one-based index in that list. The
/// given node is always the node with value 1.
///
/// Example 1:
/// Input:  adjList = [[2,4],[1,3],[2,4],[1,3]]
/// Output: [[2,4],[1,3],[2,4],[1,3]]
///
/// Example 2:
/// Input:  adjList = [[]]
/// Output: [[]]
///
/// Example 3:
/// Input:  adjList = []
/// Output: []
///
/// Constraints:
/// - The number of nodes is between 0 and 100.
/// - 1 <= Node.val <= 100
/// - Every node has a unique value.
/// - The graph has no repeated edges and no self-loops.
/// - The graph is connected and every node can be reached from the given node.

class Node {
public:
  int val;
  vector<Node *> neighbors;

  Node() : val(0) {}
  explicit Node(int value) : val(value) { neighbors.clear(); }

  Node(int value, vector<Node *> adjacent)
      : val(value), neighbors(std::move(adjacent)) {}
};

Node *cloneGraph(Node *node) {
  std::unordered_map<Node *, Node *> cloneMap;
  if (node == nullptr) {
    return nullptr;
  }

  if (node->neighbors.empty()) {
    return new Node(node->val);
  }

  std::function<Node *(Node * current)> dfs;
  dfs = [&](Node *current) {
    if (cloneMap.contains(current)) {
      return cloneMap.at(current);
    }

    auto clone =  new Node(current->val);
    cloneMap.emplace(current, clone);

    for (Node *neighbor : current->neighbors) {
      clone->neighbors.push_back(dfs(neighbor));
    }
    return node;
  };

  return dfs(node);
}

void TestCase1();
void TestCase2();

TEST(Problem, ExistingCases) {

  // Node *node1 = new Node(1);
  // Node *cloned = cloneGraph(node1);
  //
  // ASSERT_TRUE(cloned);
  // EXPECT_EQ(cloned->val, node1->val);
  //
  TestCase1();
  TestCase2();
}

void TestCase1() {
  std::unique_ptr<Node> node1 = std::make_unique<Node>(1);
  std::unique_ptr<Node> node2 = std::make_unique<Node>(2);
  node1->neighbors.emplace_back(node2.get());

  Node *cloned = cloneGraph(node1.get());

  ASSERT_TRUE(cloned);
  EXPECT_EQ(cloned->val, node1->val);
  EXPECT_EQ(cloned->neighbors.size(), node1->neighbors.size());
  ASSERT_FALSE(cloned->neighbors.empty());
  ASSERT_FALSE(node1->neighbors.empty());
  ASSERT_TRUE(cloned->neighbors.front());
  EXPECT_EQ(cloned->neighbors.front()->val, node1->neighbors.front()->val);
  EXPECT_EQ(cloned->neighbors.front()->val, node2->val);
}

void TestCase2() {
  std::unique_ptr<Node> node1 = std::make_unique<Node>(1);
  std::unique_ptr<Node> node2 = std::make_unique<Node>(2);
  std::unique_ptr<Node> node3 = std::make_unique<Node>(3);
  std::unique_ptr<Node> node4 = std::make_unique<Node>(4);

  node1->neighbors.emplace_back(node2.get());
  node1->neighbors.emplace_back(node4.get());

  node2->neighbors.emplace_back(node1.get());
  node2->neighbors.emplace_back(node3.get());

  node3->neighbors.emplace_back(node2.get());
  node3->neighbors.emplace_back(node4.get());

  node4->neighbors.emplace_back(node1.get());
  node4->neighbors.emplace_back(node3.get());

  Node *cloned = cloneGraph(node1.get());

  ASSERT_TRUE(cloned);
  EXPECT_EQ(cloned->val, node1->val);
  EXPECT_EQ(cloned->neighbors.size(), node1->neighbors.size());
  ASSERT_FALSE(cloned->neighbors.empty());
  ASSERT_FALSE(node1->neighbors.empty());
  ASSERT_TRUE(cloned->neighbors.front());
  EXPECT_EQ(cloned->neighbors.front()->val, node1->neighbors.front()->val);
  EXPECT_EQ(cloned->neighbors.front()->val, node2->val);
}
