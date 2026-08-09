#include <gtest/gtest.h>

#include <iostream>

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

ListNode *reverseList(ListNode *head) {
  ListNode *prev = nullptr;
  ListNode *current = head;
  ListNode *next = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  return prev;
}

TEST(Problem, ExistingCases) {

  ListNode n5(5);
  ListNode n4(4, &n5);
  ListNode n3(3, &n4);
  ListNode n2(2, &n3);
  ListNode n1(1, &n2);

  auto current = &n1;
  while (current) {
    std::cout << current->val << std::endl;
    current = current->next;
  }

  current = reverseList(&n1);
  while (current) {
    std::cout << current->val << std::endl;
    current = current->next;
  }

  SUCCEED();
}
