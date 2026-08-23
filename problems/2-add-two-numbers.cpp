#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

/// @problem 2. Add Two Numbers
/// @difficulty Medium
///
/// Two non-empty linked lists represent two non-negative integers. Their
/// digits are stored in reverse order, with one digit in each node.
///
/// Add the two numbers and return the sum as a linked list in the same reverse
/// order.
///
/// Constraints:
/// - Each list contains between 1 and 100 nodes.
/// - 0 <= Node.val <= 9
/// - Neither number has leading zeroes unless the number is zero.
///
/// @start 2026-08-23 19:49
/// @start 2026-08-23 20:37

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int value) : val(value), next(nullptr) {}
  ListNode(int value, ListNode *next) : val(value), next(next) {}
};

ListNode *addTwoNumbers(ListNode *list1, ListNode *list2) {
  ListNode dummy;
  ListNode *tail = &dummy;
  int carry = 0;

  while (list1 != nullptr || list2 != nullptr || carry != 0) {
    int sum = carry;

    if (list1 != nullptr) {
      sum += list1->val;
      list1 = list1->next;
    }

    if (list2 != nullptr) {
      sum += list2->val;
      list2 = list2->next;
    }

    tail->next = new ListNode(sum % 10);
    tail = tail->next;
    carry = sum / 10;
  }

  return dummy.next;
}

std::vector<int> collectValues(ListNode *head, std::size_t expectedNodes) {
  std::vector<int> values;
  while (head != nullptr && values.size() <= expectedNodes) {
    values.push_back(head->val);
    head = head->next;
  }
  return values;
}

TEST(AddTwoNumbers, AddsEqualLengthLists) {
  ListNode left3{3};
  ListNode left2{4, &left3};
  ListNode left1{2, &left2};

  ListNode right3{4};
  ListNode right2{6, &right3};
  ListNode right1{5, &right2};

  EXPECT_EQ(collectValues(addTwoNumbers(&left1, &right1), 3),
            (std::vector<int>{7, 0, 8}));
}

TEST(AddTwoNumbers, AddsZeroes) {
  ListNode left{0};
  ListNode right{0};

  EXPECT_EQ(collectValues(addTwoNumbers(&left, &right), 1),
            (std::vector<int>{0}));
}

TEST(AddTwoNumbers, PropagatesCarryAcrossUnequalLengths) {
  ListNode left7{9};
  ListNode left6{9, &left7};
  ListNode left5{9, &left6};
  ListNode left4{9, &left5};
  ListNode left3{9, &left4};
  ListNode left2{9, &left3};
  ListNode left1{9, &left2};

  ListNode right4{9};
  ListNode right3{9, &right4};
  ListNode right2{9, &right3};
  ListNode right1{9, &right2};

  EXPECT_EQ(collectValues(addTwoNumbers(&left1, &right1), 8),
            (std::vector<int>{8, 9, 9, 9, 0, 0, 0, 1}));
}

TEST(AddTwoNumbers, AppendsFinalCarry) {
  ListNode left{5};
  ListNode right{5};

  EXPECT_EQ(collectValues(addTwoNumbers(&left, &right), 2),
            (std::vector<int>{0, 1}));
}

TEST(AddTwoNumbers, KeepsDigitWhenSumExceedsTen) {
  ListNode left{6};
  ListNode right{5};

  EXPECT_EQ(collectValues(addTwoNumbers(&left, &right), 2),
            (std::vector<int>{1, 1}));
}

TEST(AddTwoNumbers, PropagatesCarryThroughLongerFirstList) {
  ListNode left2{9};
  ListNode left1{9, &left2};
  ListNode right{1};

  EXPECT_EQ(collectValues(addTwoNumbers(&left1, &right), 3),
            (std::vector<int>{0, 0, 1}));
}

TEST(AddTwoNumbers, PropagatesCarryThroughLongerSecondList) {
  ListNode left{1};
  ListNode right2{9};
  ListNode right1{9, &right2};

  EXPECT_EQ(collectValues(addTwoNumbers(&left, &right1), 3),
            (std::vector<int>{0, 0, 1}));
}
