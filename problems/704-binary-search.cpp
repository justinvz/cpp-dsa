
#include "testSuite.h"

using namespace std;

// Start (10-05-2026) (18:05) solved (18:27)
//
/// @problem
///
// Given an array of integers nums which is sorted in ascending order, and an
// integer target, write a function to search target in nums. If target exists,
// then return its index. Otherwise, return -1.  You must write an algorithm
// with O(log n) runtime complexity.
//
// @solution
//
// because the array is sorted, we can first check if the middle value of the
// input array is higher or lower than the target. If so, we jump to half of
// that half. if there is a match, return. We can only continue jumping untill
// we are not hitting the same index again.

int Search(vector<int> nums, int target) {
  if (nums.size() == 1 && target == nums[0]) {
    return 0;
  }

  int left = 0;
  int right = nums.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target)
      return mid;

    if (nums[mid] < target)
      left = mid + 1;

    if (nums[mid] > target)
      right = mid - 1;
  }

  return -1;
}

int main() {
  TestTimer timer;
  ExpectEq(Search({-1, 0, 3, 5, 9, 12}, 9), 4);
  ExpectEq(Search({-1, 0, 3, 5, 9, 12}, 12), 5);
  ExpectEq(Search({-1, 0, 3, 5, 9, 12}, 0), 1);
}
