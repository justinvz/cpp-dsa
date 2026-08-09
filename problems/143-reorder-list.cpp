#include <gtest/gtest.h>

#include <cstddef>
#include <stack>
#include <unordered_set>

using namespace std;

/// @problem reverse the linked list.
/// Starttime = 2026-06-03 22:53
/// @Solution
///
/// I think using two pointers is simplest.
///
/// p1 at start, and p2 walks to the end, point p1 to p2, and walk p1 foward,
/// after point p2 to p1 and walk p2 backwards.
///

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool reorderListStack(ListNode *head) {
  stack<ListNode *> visted;

  auto p1 = head;
  auto p2 = head;

  // Walk p2 to the end.
  while (p2 != nullptr) {
    visted.push(p2);
    p2 = p2->next;
  }
  p2->next = nullptr;

  while (p1 != p2) {
    auto temp = p1;
    p1 = p1->next;
    temp->next = p2;

    if (p1 == p2) {
      break;
    }

    temp = p2;

    if (visted.empty()) {
      break;
    }

    visted.pop();
    p2 = visted.top();
    temp->next = p1;
  }

  return head;
}

bool reorderList(ListNode *head) {
  /// Search for middle

  ListNode *p1 = head;
  ListNode *p2 = head;

  // Fast pointer takes two steps. so when p2 is near the end. p1 is halfway.
  while (p2->next->next != nullptr) {
    p2->next = p2->next->next;
    p1->next = p1;
  }

  // Split list
  auto tail = p1->next;
  p1->next = nullptr;

  // Reverse list
  while (p1 != nullptr) {
    auto temp = p1;
    p1 = p1->next;
    p1->next = temp;
  }
  tail = nullptr;

  /// Merge lists
}

// Use fast and slow pointer, one moves 1 node at a time, other moves two nodes
// at a time, When pointers meet, cycle is detected. If the slow pointer reaches
// the end without meeting the fast pointer, there is no cycle.
bool hasCycle(ListNode *head) {
  ListNode *fast = head;
  ListNode *slow = head;

  if (head->next == nullptr) {
    return false;
  }

  while (fast) {
    if (fast->next) {
      fast = fast->next->next;
    } else {
      fast = nullptr;
    }
    slow = slow->next;

    if (slow == fast) {
      return true;
    }
  }
  return false;
}
TEST(Problem, ExistingCases) {

  ListNode n6(6);

  ListNode n5(5);
  ListNode n4 = ListNode(4, &n5);
  n5.next = &n4;

  ListNode n3(3);
  ListNode n2(2, &n3);
  ListNode n1(1, &n2);

  // auto current = &n1;
  // while (current) {
  //   std::cout << current->val << std::endl;
  //   current = current->next;
  // }
  //
  // EXPECT_FALSE(hasCycleBruteForce(&n1));
  // EXPECT_TRUE(hasCycleBruteForce(&n4));

  EXPECT_FALSE(hasCycle(&n1));
  EXPECT_TRUE(hasCycle(&n4));
  EXPECT_FALSE(hasCycle(&n6));

  // current = reverseList(&n1);
  // while (current) {
  //   std::cout << current->val << std::endl;
  //   current = current->next;
  // }
}
