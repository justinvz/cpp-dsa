#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

/// @problem 78. Subsets
/// @difficulty Medium
///
/// Given an integer array nums of unique elements, return all possible subsets
/// (the power set).
///
/// The solution set must not contain duplicate subsets. The answer may be
/// returned in any order.
///
/// Constraints:
/// - 1 <= nums.size() <= 10
/// - -10 <= nums[i] <= 10
/// - All values in nums are unique.
///
/// @starttime = 21:43
/// @finishtime =

std::vector<std::vector<int>> subsets(std::vector<int> nums) {
  std::vector<std::vector<int>> result;

  // Start with []
  //
  // check first number, take it, and leave it.
  //
  // check second, take it and leave int
  //
  // check n, take it and leave it.
  //
  // when depth nums.size() is reached, append to results.

  std::function<void(int index, std::vector<int> subset)> backtrace;
  backtrace = [&](int index, std::vector<int> subset) {
    if (index >= nums.size()) {
      result.push_back(subset);
      return;
    }

    subset.push_back(nums[index]);
    backtrace(index + 1, subset);
    subset.pop_back();
    backtrace(index + 1, subset);
  };

  backtrace(0, {});

  return result;
}

void expectSubsets(std::vector<std::vector<int>> actual,
                   std::vector<std::vector<int>> expected) {
  for (auto &subset : actual) {
    std::ranges::sort(subset);
  }
  for (auto &subset : expected) {
    std::ranges::sort(subset);
  }

  std::ranges::sort(actual);
  std::ranges::sort(expected);
  EXPECT_EQ(actual, expected);
}

TEST(Subsets, HandlesSingleton) { expectSubsets(subsets({1}), {{}, {1}}); }

TEST(Subsets, GeneratesPowerSetOfTwoElements) {
  expectSubsets(subsets({1, 2}), {{}, {1}, {2}, {1, 2}});
}

TEST(Subsets, GeneratesPowerSetOfThreeElements) {
  expectSubsets(subsets({1, 2, 3}),
                {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}});
}

TEST(Subsets, HandlesNegativeValues) {
  expectSubsets(subsets({-1, 2}), {{}, {-1}, {2}, {-1, 2}});
}
