#include "testSuite.h"
#include <optional>
#include <unordered_set>

using namespace std;

/// @problem reverse the linked list.
/// Starttime = 20-05-2026 23:27
///
///
/// @Approach
///
/// Walk through linked list, reverse the pointers.

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool hasCycleBruteForce(ListNode *head) {
  unordered_set<ListNode *> visited;

  ListNode *current = head;

  while (current) {
    if (visited.contains(current)) {
      return true;
    }
    visited.insert(current);
    current = current->next;
  }
  return false;
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
int main() {
  TestTimer timer;

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
  // ExpectFalse(hasCycleBruteForce(&n1));
  // ExpectTrue(hasCycleBruteForce(&n4));

  ExpectFalse(hasCycle(&n1));
  ExpectTrue(hasCycle(&n4));
  ExpectFalse(hasCycle(&n6));

  // current = reverseList(&n1);
  // while (current) {
  //   std::cout << current->val << std::endl;
  //   current = current->next;
  // }
}
