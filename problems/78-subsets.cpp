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
/// @starttime = 14:40
/// @finishtime = 15:01

std::vector<std::vector<int>> subsets(std::vector<int> nums) {
  // First define
  //
  // State -> i, subset
  // Choice -> take or leave number
  // NextState -> i + 1
  // Path -> subset
  // EndCondition -> i == nums.size()

  std::vector<std::vector<int>> result;

  // [1, 2, 3]
  // i = 1
  // result = [[1,2,3], []]
  // subset = [1, 2]

  std::function<void(size_t i, std::vector<int> subset)> backtrace;
  backtrace = [&](size_t i, std::vector<int> subset) {
    if (nums.size() == i) {
      result.push_back(subset); // When I reached, than add to result.
      return;
    }

    // Explore take nums[i]
    subset.emplace_back(nums[i]);
    backtrace(i+1, subset);

    // Explore leave nums[i]
    subset.pop_back();
    backtrace(i+1, subset);
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

// TEST(Subsets, HandlesSingleton) { expectSubsets(subsets({1}), {{}, {1}}); }
//
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
