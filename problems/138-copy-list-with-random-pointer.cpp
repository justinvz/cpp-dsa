#include <gtest/gtest.h>

#include <cstddef>
#include <unordered_map>
#include <vector>

/// @problem 138. Copy List with Random Pointer
/// @difficulty Medium
///
/// A linked list contains nodes with a next pointer and an additional random
/// pointer. A node's random pointer may point to any node in the list or to
/// null.
///
/// Construct a deep copy of the list. Every copied node must have the same
/// value as its corresponding original node, and the copied next and random
/// pointers must refer only to nodes in the copied list.
///
/// Constraints:
/// - 0 <= number of nodes <= 1000
/// - -10^4 <= Node.val <= 10^4
/// - random is null or points to a node in the list
///
/// @start 2026-08-23 19:10
/// @finish 2026-08-23 19:26

struct Node {
  int val;
  Node *next;
  Node *random;

  explicit Node(int value) : val(value), next(nullptr), random(nullptr) {}
};

Node *copyRandomList(Node *head) {
  if (head == nullptr) {
    return head;
  }
  std::unordered_map<Node *, Node *> listMapping;

  Node *current = head;
  while (current != nullptr) {
    Node *copy = new Node(current->val);
    listMapping.insert({current, copy});
    current = current->next;
  }

  current = head;
  while (current != nullptr) {
    Node *currentCopy = listMapping.at(current);
    currentCopy->next =
        (current->next != nullptr) ? listMapping.at(current->next) : nullptr;

    currentCopy->random = (current->random != nullptr)
                              ? listMapping.at(current->random)
                              : nullptr;

    current = current->next;
  }

  return listMapping.at(head);
}

std::vector<Node *> collectNodes(Node *head, std::size_t expectedNodes) {
  std::vector<Node *> nodes;
  while (head != nullptr && nodes.size() <= expectedNodes) {
    nodes.push_back(head);
    head = head->next;
  }
  return nodes;
}

void expectDeepCopy(Node *copiedHead, const std::vector<Node *> &original,
                    const std::vector<int> &randomIndices) {
  const std::vector<Node *> copied = collectNodes(copiedHead, original.size());
  ASSERT_EQ(copied.size(), original.size());
  ASSERT_EQ(randomIndices.size(), original.size());

  for (std::size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(copied[i]->val, original[i]->val);

    for (Node *originalNode : original) {
      EXPECT_NE(copied[i], originalNode);
    }

    Node *expectedOriginalNext =
        i + 1 < original.size() ? original[i + 1] : nullptr;
    EXPECT_EQ(original[i]->next, expectedOriginalNext);

    if (randomIndices[i] == -1) {
      EXPECT_EQ(original[i]->random, nullptr);
      EXPECT_EQ(copied[i]->random, nullptr);
    } else {
      const auto randomIndex = static_cast<std::size_t>(randomIndices[i]);
      ASSERT_LT(randomIndex, original.size());
      EXPECT_EQ(original[i]->random, original[randomIndex]);
      EXPECT_EQ(copied[i]->random, copied[randomIndex]);
    }
  }
}

TEST(CopyRandomList, EmptyList) { EXPECT_EQ(copyRandomList(nullptr), nullptr); }

TEST(CopyRandomList, SingleNodeWithNullRandom) {
  Node node1{7};

  expectDeepCopy(copyRandomList(&node1), {&node1}, {-1});
}

TEST(CopyRandomList, SingleNodeWithSelfRandom) {
  Node node1{7};
  node1.random = &node1;

  expectDeepCopy(copyRandomList(&node1), {&node1}, {0});
}

TEST(CopyRandomList, MixedRandomPointers) {
  Node node1{7};
  Node node2{13};
  Node node3{11};
  Node node4{10};
  Node node5{1};

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;

  node1.random = nullptr;
  node2.random = &node1;
  node3.random = &node5;
  node4.random = &node3;
  node5.random = &node1;

  expectDeepCopy(copyRandomList(&node1),
                 {&node1, &node2, &node3, &node4, &node5}, {-1, 0, 4, 2, 0});
}
