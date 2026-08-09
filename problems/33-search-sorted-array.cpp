#include <gtest/gtest.h>

#include <vector>

using namespace std;

int search(vector<int> nums, int target) {
  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2; // cap to bottum

    if (nums[mid] == target)
      return mid;

    // Check if left is sorted.
    if (nums[left] <= nums[mid]) {
      // Check if the target is in range.
      if (nums[left] <= target && target < nums[mid]) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }

    // If left is not sorted, right must be
    else {
      if (nums[mid] < target && target <= nums[right]) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }

  return -1;
}

TEST(Problem, ExistingCases) {
  EXPECT_EQ(search({0, 1, 2, 3, 4, 5, 6}, 0), 0);
  EXPECT_EQ(search({4, 5, 6, 7, 0, 1, 2}, 0), 4);
  EXPECT_EQ(search({6, 7, 0, 1, 2, 3}, 0), 2);
  EXPECT_EQ(search({4, 5, 6, 7, 0, 1, 2}, 3), -1);
  EXPECT_EQ(search({1}, 0), -1);
}
