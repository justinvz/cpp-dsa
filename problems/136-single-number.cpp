#include <gtest/gtest.h>

#include <vector>

/// @problem 136. Single Number
/// @difficulty Easy
///
/// Given a non-empty array of integers in which every element appears twice
/// except for one, return the element that appears only once.
///
/// Implement a solution with linear runtime complexity and constant auxiliary
/// space.
///
/// Constraints:
/// - 1 <= nums.size() <= 3 * 10^4
/// - -3 * 10^4 <= nums[i] <= 3 * 10^4
/// - Every element except one appears exactly twice.
///
/// @solved 2026-08-23 00:05

int singleNumber(std::vector<int> &numbers) {
  int result = 0;
  for (auto &num : numbers) {
    result ^= num;
  }
  return result;
}

TEST(SingleNumber, FindsValueAmongOnePair) {
  std::vector<int> numbers{2, 2, 1};

  EXPECT_EQ(singleNumber(numbers), 1);
}

TEST(SingleNumber, FindsValueAmongSeveralPairs) {
  std::vector<int> numbers{4, 1, 2, 1, 2};

  EXPECT_EQ(singleNumber(numbers), 4);
}

TEST(SingleNumber, HandlesSingletonInput) {
  std::vector<int> numbers{7};

  EXPECT_EQ(singleNumber(numbers), 7);
}

TEST(SingleNumber, HandlesNegativeValues) {
  std::vector<int> numbers{-1, -2, -1};

  EXPECT_EQ(singleNumber(numbers), -2);
}

TEST(SingleNumber, HandlesZero) {
  std::vector<int> numbers{5, 0, 5};

  EXPECT_EQ(singleNumber(numbers), 0);
}
