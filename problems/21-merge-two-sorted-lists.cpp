#include "testSuite.h"
#include <cstddef>
#include <optional>

using namespace std;

/// Starttime = 21-05-2026 20:19
///
/// @Approach
///
/// I think th easiest solution is to first check which head is lowest.
///
/// The lowest head is the starting point, now you go to the next node of of
/// this head, and reavaluate. If it still lower, go to the next node. If it's
/// higher than the previous head. Attacch this node.

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
  ListNode dummy(0);
  ListNode *tail = &dummy;

  while (list1 && list2) {
    if (list1->val <= list2->val) {
      tail->next = list1;
      list1 = list1->next;
    } else {
      tail->next = list2;
      list2 = list2->next;
    }
    tail = tail->next;
  }

  tail->next = list1 ? list1 : list2;

  return dummy.next;
}
int main() {
  TestTimer timer;

  ListNode n5(5);
  ListNode n3(3, &n5);
  ListNode n2(2, &n3);

  ListNode n6(6);
  ListNode n4(4, &n6);
  ListNode n1(1, &n4);

  auto current = &n1;

  current = mergeTwoLists(&n2, &n1);
  while (current) {
    std::cout << current->val << std::endl;
    current = current->next;
  }
}
