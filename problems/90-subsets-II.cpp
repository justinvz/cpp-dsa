#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <unordered_map>
#include <vector>

/// @problem 90. Subsets II
/// @difficulty Medium
///
/// Given an integer array nums that may contain duplicates, return all possible
/// subsets. The solution set must not contain duplicate subsets.
///
/// Constraints:
/// - 1 <= nums.size() <= 10
/// - -10 <= nums[i] <= 10
///
/// @starttime 21:20 20-08-27

std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {

  // What we want to do is we want to use backtracing.
  std::vector<std::vector<int>> result;

  std::ranges::sort(nums);

  std::function<void(int i, std::vector<int> subset)> backtrace;
  backtrace = [&](int i, std::vector<int> subset) {
    if (i == nums.size()) {
      result.push_back(subset);
      return;
    }

    subset.push_back(nums[i]);
    backtrace(i + 1, subset);
    subset.pop_back();

    while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
      i += 1;
    }
    backtrace(i + 1, subset);
  };

  backtrace(0, {});

  return result;
}

void expectSubsets(std::vector<std::vector<int>> actual,
                   std::vector<std::vector<int>> expected) {
  std::ranges::sort(actual);
  std::ranges::sort(expected);
  EXPECT_EQ(actual, expected);
}

TEST(SubsetsII, HandlesSingleton) {
  std::vector<int> nums{1};

  expectSubsets(subsetsWithDup(nums), {{}, {1}});
}

TEST(SubsetsII, RemovesDuplicateSubsets) {
  std::vector<int> nums{1, 2, 2};

  expectSubsets(subsetsWithDup(nums),
                {{}, {1}, {2}, {1, 2}, {2, 2}, {1, 2, 2}});
}

TEST(SubsetsII, AllowsRepeatedValuesWithinASubset) {
  std::vector<int> nums{2, 2, 2};

  expectSubsets(subsetsWithDup(nums), {{}, {2}, {2, 2}, {2, 2, 2}});
}

TEST(SubsetsII, HandlesUnsortedNegativeDuplicates) {
  std::vector<int> nums{0, -1, 0};

  expectSubsets(subsetsWithDup(nums),
                {{}, {-1}, {0}, {-1, 0}, {0, 0}, {-1, 0, 0}});
}
