#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

/// @problem 19. Remove Nth Node From End of List
/// @difficulty Medium
///
/// Given the head of a linked list, remove the nth node from the end of the
/// list and return its head.
///
/// Constraints:
/// - The number of nodes is sz.
/// - 1 <= sz <= 30
/// - 0 <= Node.val <= 100
/// - 1 <= n <= sz
///
/// @start 2026-08-23 18:10
/// @finished 2026-08-23 18:49

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeNthFromEnd(ListNode *head, int n) {
  ListNode dummy(0, head);
  ListNode *leader = &dummy;
  ListNode *follower = &dummy;

  for (int i = 0; i < n; i++) {
    leader = leader->next;
  }

  while (leader->next != nullptr) {
    leader = leader->next;
    follower = follower->next;
  }

  follower->next = follower->next->next;
  return dummy.next;
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

TEST(RemoveNthFromEnd, RemovesOnlyNode) {
  ListNode node1{1};

  EXPECT_EQ(removeNthFromEnd(&node1, 1), nullptr);
}

TEST(RemoveNthFromEnd, RemovesMiddleNode) {
  ListNode node5{5};
  ListNode node4{4, &node5};
  ListNode node3{3, &node4};
  ListNode node2{2, &node3};
  ListNode node1{1, &node2};

  ListNode *head = removeNthFromEnd(&node1, 2);

  EXPECT_EQ(collectNodes(head, 4),
            (std::vector<ListNode *>{&node1, &node2, &node3, &node5}));
}

TEST(RemoveNthFromEnd, RemovesHead) {
  ListNode node3{3};
  ListNode node2{2, &node3};
  ListNode node1{1, &node2};

  ListNode *head = removeNthFromEnd(&node1, 3);

  EXPECT_EQ(collectNodes(head, 2), (std::vector<ListNode *>{&node2, &node3}));
}

TEST(RemoveNthFromEnd, RemovesHead2) {
  ListNode node2{2};
  ListNode node1{1, &node2};

  ListNode *head = removeNthFromEnd(&node1, 2);

  EXPECT_EQ(collectNodes(head, 1), (std::vector<ListNode *>{&node2}));
}

TEST(RemoveNthFromEnd, RemovesTail) {
  ListNode node3{3};
  ListNode node2{2, &node3};
  ListNode node1{1, &node2};

  ListNode *head = removeNthFromEnd(&node1, 1);

  EXPECT_EQ(collectNodes(head, 2), (std::vector<ListNode *>{&node1, &node2}));
}

TEST(RemoveNthFromEnd, RemoveTail2) {
  ListNode node2{2};
  ListNode node1{1, &node2};

  ListNode *head = removeNthFromEnd(&node1, 1);

  EXPECT_EQ(collectNodes(head, 2), (std::vector<ListNode *>{&node1}));
}
