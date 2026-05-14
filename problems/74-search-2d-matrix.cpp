#include "testSuite.h"

// Start (14-05-2026) (13:13) sovled at (14:44)
//
/// @problem
///
// You are given an m x n integer matrix matrix with the following two
// properties: Each row is sorted in non-decreasing order.
// The first integer of each row is greater than the last integer of the
// previous row. Given an integer target, return true if target is in matrix or
// false otherwise. You must write a solution in O(log(m * n)) time complexity
//
// @solution
//
// Basicly binary search but than on a matrix. What you can do is first find
// row, than find column. this will be log(m * n) because it takes log(m) to
// find row, and log(n) to find colum.
//
// Easy way to fnd the row is to check the first value of the middel row is ==
// than target. if smaller, than we should look at another row, if bigger, than
// it can be in this row. if bigger, we can check if it's lower than the last
// value of the row, if so, its in between and we found the row. Now this
// soluton becomes 1D binary search on that row.
//
//
// @solution 2
//
// We could also flatten the array and preform single binary saerch as if it was
// not a matrix. in practice we could do some math on the index.

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

// We need to normalize the matrix
//
// nums[n][m] where n represents the rows, and m represents the colums.
//
// so the index  i = n*size + m

bool SearchMatrix(vector<vector<int>> nums, int target) {
  std::vector<int> normalized;
  normalized.reserve(nums.size() * nums[0].size());

  for (size_t n{0}; n < nums.size(); n++) {
    for (size_t m{0}; m < nums[0].size(); m++) {
      normalized.push_back(nums[n][m]);
    }
  }

  int left = 0;
  int right = normalized.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (normalized[mid] == target) {
      return true;
    } else if (normalized[mid] < target) {
      left = mid + 1;
    } else if (normalized[mid] > target) {
      right = mid - 1;
    }
  }
  return false;
}

int main() {
  TestTimer timer;
  ExpectEq(SearchMatrix({{1, 2}, {3, 4}}, 3), true);

  ExpectEq(SearchMatrix({{1, 3, 5, 7}, {10, 11, 16, 29}, {23, 30, 34, 60}}, 7),
           true);
  ExpectEq(SearchMatrix({{1, 3, 5, 7}, {10, 11, 16, 29}, {23, 30, 34, 60}}, 13),
           false);
}
