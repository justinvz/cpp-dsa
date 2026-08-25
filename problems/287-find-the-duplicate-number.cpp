#include <gtest/gtest.h>

#include <vector>

/// @problem 287. Find the Duplicate Number
/// @difficulty Medium
///
/// Given an array containing n + 1 integers where every integer is in the
/// inclusive range [1, n], return the repeated number.
///
/// There is only one repeated number, but it may appear more than twice.
/// Solve the problem without modifying the array and using only constant
/// auxiliary space.
///
/// Constraints:
/// - 1 <= n <= 10^5
/// - nums.size() == n + 1
/// - 1 <= nums[i] <= n
/// - Exactly one integer appears more than once.
///
/// @start 2026-08-23 22:54

int findDuplicate(std::vector<int> &nums) {
  int slow = nums[0];
  int fast = nums[0];

  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  } while (slow != fast);

  int walker = nums[0];
  while (walker != slow) {
    walker = nums[walker];
    slow = nums[slow];
  }

  return walker;
}

TEST(FindDuplicate, FindsDuplicateNearEnd) {
  std::vector<int> numbers{2, 5, 9, 6, 9, 3, 8, 9, 7, 1};

  EXPECT_EQ(findDuplicate(numbers), 9);
}

TEST(FindDuplicate, FindsDuplicateNearBeginning) {
  std::vector<int> numbers{3, 1, 3, 4, 2};

  EXPECT_EQ(findDuplicate(numbers), 3);
}

TEST(FindDuplicate, HandlesMinimumInput) {
  std::vector<int> numbers{1, 1};

  EXPECT_EQ(findDuplicate(numbers), 1);
}

TEST(FindDuplicate, HandlesMoreThanTwoOccurrences) {
  std::vector<int> numbers{3, 3, 3, 3, 3};

  EXPECT_EQ(findDuplicate(numbers), 3);
}

TEST(FindDuplicate, FindsLargeDuplicateValue) {
  std::vector<int> numbers{1, 4, 6, 3, 2, 5, 6};

  EXPECT_EQ(findDuplicate(numbers), 6);
}
