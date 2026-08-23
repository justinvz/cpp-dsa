#include <gtest/gtest.h>

#include <cstddef>
#include <deque>
#include <vector>

/// @problem 143. Reorder List
/// @difficulty Medium
///
/// Given the head of a singly linked list whose nodes are ordered as
///
///   L0 -> L1 -> ... -> Ln-1 -> Ln
///
/// Reorder the list in place to
///
///   L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...
///
/// Node values may not be changed; only the links between nodes may change.
///
/// Constraints:
/// - 1 <= number of nodes <= 5 * 10^4
/// - 1 <= Node.val <= 1000
///
/// Starttime = 2026-06-03 22:53
/// Starttime second = 2026-08-09 22:36
/// Starttime third = 2026-08-23 13:38
/// Finish 13:56
/// @Solution
///

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void reverseList(ListNode *head) {
  ListNode *current = head;
  ListNode *previous = nullptr;

  while (current != nullptr) {
    ListNode *next = current->next;
    current->next = previous;

    previous = current;
    current = next;
  }

  head = previous;
}

void reorderList(ListNode *head) {
  if (head == nullptr) {
    return;
  }

  std::deque<ListNode *> dequeu;

  ListNode *current = head;
  while (current != nullptr) {
    dequeu.push_back(current);
    current = current->next;
    dequeu.back()->next = nullptr;
  }

  if (dequeu.empty() || dequeu.size() == 1) {
    return;
  }

  bool frontOrBack{true};
  while (!dequeu.empty()) {
    if (frontOrBack) {
      current = dequeu.front();
      current->next = dequeu.back();
      dequeu.pop_front();
    } else {
      current = dequeu.back();
      current->next = dequeu.front();
      dequeu.pop_back();
    }
    frontOrBack = !frontOrBack;
  }

  current->next = nullptr;
}

std::vector<ListNode *> collectNodes(ListNode *head,
                                     std::size_t expectedNodes) {
  std::vector<ListNode *> nodes;
  while (head != nullptr && nodes.size() <= expectedNodes) {
    nodes.push_back(head);
    head = head->next;
  }
  return nodes;
}

TEST(ReorderList, EmptyList) {
  reorderList(nullptr);
  SUCCEED();
}

TEST(ReorderList, SingleNode) {
  ListNode node1{1};

  reorderList(&node1);

  EXPECT_EQ(collectNodes(&node1, 1), (std::vector<ListNode *>{&node1}));
}

TEST(ReorderList, TwoNodes) {
  ListNode node2{2};
  ListNode node1{1, &node2};

  reorderList(&node1);

  EXPECT_EQ(collectNodes(&node1, 2), (std::vector<ListNode *>{&node1, &node2}));
}

TEST(ReorderList, EvenNumberOfNodes) {
  ListNode node4{4};
  ListNode node3{3, &node4};
  ListNode node2{2, &node3};
  ListNode node1{1, &node2};

  reorderList(&node1);

  EXPECT_EQ(collectNodes(&node1, 4),
            (std::vector<ListNode *>{&node1, &node4, &node2, &node3}));
}

TEST(ReorderList, OddNumberOfNodes) {
  ListNode node5{5};
  ListNode node4{4, &node5};
  ListNode node3{3, &node4};
  ListNode node2{2, &node3};
  ListNode node1{1, &node2};

  reorderList(&node1);

  EXPECT_EQ(collectNodes(&node1, 5),
            (std::vector<ListNode *>{&node1, &node5, &node2, &node4, &node3}));
}
