#include <gtest/gtest.h>

#include <cstddef>
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
/// Finish 13:56 deque implementation
/// finsih 15:04 fast and slow pointer
/// @Solution
///

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void mergeList(ListNode *head1, ListNode *head2) {
  ListNode *current1 = head1;
  ListNode *current2 = head2;

  while (current2 != nullptr) {
    ListNode *next1 = current1->next;
    ListNode *next2 = current2->next;

    current1->next = current2;
    current2->next = next1;

    current1 = next1;
    current2 = next2;
  }
}

ListNode *reverseList(ListNode *head) {
  ListNode *current = head;
  ListNode *previous = nullptr;

  while (current != nullptr) {
    ListNode *next = current->next;
    current->next = previous;

    previous = current;
    current = next;
  }

  return previous;
}

void reorderList(ListNode *head) {
  if (head == nullptr || head->next == nullptr) {
    return;
  }

  // Use fast and slow pointer to find the midpoint
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast->next != nullptr && fast->next->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *midpoint = slow->next;
  slow->next = nullptr;
  mergeList(head, reverseList(midpoint));
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
