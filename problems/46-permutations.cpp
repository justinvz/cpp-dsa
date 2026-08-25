#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <unordered_set>
#include <vector>

/// @problem 46. Permutations
/// @difficulty Medium
///
/// Given an array nums of distinct integers, return all possible permutations.
/// The answer may be returned in any order.
///
/// Constraints:
/// - 1 <= nums.size() <= 6
/// - -10 <= nums[i] <= 10
/// - All integers in nums are unique.

std::vector<std::vector<int>> permute(std::vector<int> &nums) {
  std::vector<std::vector<int>> result;
  std::vector<int> permutation;
  std::unordered_set<int> visited;

  std::function<void()> backtrack = [&] {
    if (permutation.size() == nums.size()) {
      result.push_back(permutation);
      return;
    }

    for (int num : nums) {
      if (visited.contains(num)) {
        continue;
      }

      visited.insert(num);
      permutation.push_back(num);

      backtrack();

      permutation.pop_back();
      visited.erase(num);
    }
  };

  backtrack();
  return result;
}

void expectPermutations(std::vector<std::vector<int>> actual,
                        std::vector<std::vector<int>> expected) {
  std::ranges::sort(actual);
  std::ranges::sort(expected);
  EXPECT_EQ(actual, expected);
}

TEST(Permutations, HandlesSingleton) {
  std::vector<int> nums{1};

  expectPermutations(permute(nums), {{1}});
}

TEST(Permutations, GeneratesBothOrdersForTwoElements) {
  std::vector<int> nums{0, 1};

  expectPermutations(permute(nums), {{0, 1}, {1, 0}});
}

TEST(Permutations, GeneratesAllOrdersForThreeElements) {
  std::vector<int> nums{1, 2, 3};

  expectPermutations(permute(nums),
                     {{1, 2, 3},
                      {1, 3, 2},
                      {2, 1, 3},
                      {2, 3, 1},
                      {3, 1, 2},
                      {3, 2, 1}});
}

TEST(Permutations, HandlesNegativeValues) {
  std::vector<int> nums{-2, 4};

  expectPermutations(permute(nums), {{-2, 4}, {4, -2}});
}
