#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/// @problem
///
/// Given an unsorted array of integers nums, return the length of the longest
/// consecutive elements sequence.
///
/// You must write an algorithm that runs in O(n) time.
///
/// Solution?
///
/// With O(n) we have to be smart. We are essentially trying to detect a range
/// of numbers that cannot be broken.
///
/// Because numbers can be from -10^9 and 10^9, we must be smart.
///
/// First approach will be a naive one.
///
/// We itterate through the list. for each number we encouter, we check if the
/// consecutive lower or higher number is already inside of the seen numbers.
///
/// If so, we need to link these numbers to each other.
/// Add number to set.

int LongestConsecutiveV1(vector<int> nums) {
  unordered_set<int> visited(nums.begin(), nums.end());

  int best = 0;

  for (int num : visited) {
    if (visited.contains(num - 1)) {
      int len = 1;
      int cur = num;

      while (visited.contains(cur + 1)) {
        cur++;
        len++;
      }

      best = max(best, len);
    }
  }

  return best;
}

TEST(Problem, ExistingCases) {

  int itterations = 10;
  vector<int> nums;
  for (int i = 0; i < 1'000; i++) {

    nums.push_back(rand());
  }

  {
    for (int i = 0; i < itterations; i++) {
      LongestConsecutiveV1(nums);
    }
  }

  // nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  // EXPECT_EQ(LongestConsecutive(nums), 9);
  //
  // nums = {1, 0, 1, 2};
  // EXPECT_EQ(LongestConsecutive(nums), 3);
  SUCCEED();
}
