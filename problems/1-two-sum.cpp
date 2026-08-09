#include <gtest/gtest.h>

#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

/// @problem
///
/// Given an array of integers nums and an integer target, return indices of the
/// two numbers such that they add up to target.
///
/// Assume each input would have exactly one solution, and you may not use the
/// same element twice
///
/// you can return the answer in any order.
///
/// @solution 1 brute force bad approach
///
/// iterate through each element and check against each other to see if it's
/// equal to the target
///
/// Time complexity = O(n^2)
///
/// @solution 2
/// You know the target value, itterate through elements and save each element
/// to a hashmap. Check if element value - target = in hasmap to find the
/// solution.
///
/// Time complexity = O(n)

vector<size_t> TwoSum(vector<int> &nums, int target) {
  unordered_map<int, size_t> hashmap;

  for (size_t i{0}; i < nums.size(); i++) {
    auto solution = hashmap.find(target - nums[i]);
    if (solution != hashmap.end()) {
      return {solution->second, i};
    }

    hashmap.insert({nums[i], i});
  }

  return {}; // Highly unlikely
}

TEST(Problem, ExistingCases) {
  auto nums = std::vector<int>{2, 7, 11, 15};
  EXPECT_EQ(TwoSum(nums, 9), (std::vector<size_t>{0, 1}));

  nums = std::vector<int>{3, 2, 4};
  EXPECT_EQ(TwoSum(nums, 6), (std::vector<size_t>{1, 2}));

  nums = std::vector<int>{3, 3};
  EXPECT_EQ(TwoSum(nums, 6), (std::vector<size_t>{0, 1}));
}
