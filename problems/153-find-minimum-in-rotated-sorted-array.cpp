#include "testSuite.h"

using namespace std;

/// Start time: 17-5-2026 20:15

/// Binary search..
///
/// Things to remember is that we should solve in O(log n)
///
/// Because array is rotated, we can assume that everything
/// before the rotating point is  bigger the first element.
/// after the rotating point is lower than the first element.
///
/// proof:
/// [3, 4, 5, 1, 2]
/// 3 > 1 and 3 < 5
///
/// [4, 5, 6, 7, 0, 1, 2]
/// 4 > 0 and 4 < 7
///
/// What we can do is we can binary search for the element that is lower, but we
/// have to keep in mind where the rotating point is. As soon as we find the
/// rotating point, we know the lowest value.
///
/// [4, 5, 6, 7, 0, 1, 2]
/// l = 4, m = 7, r = 2
/// l < 7, so everything is bigger untill 7.
/// move m to 7
///
/// [0, 1, 2]
/// l = 0, m = 1, r = 2
/// l < 1, so we move m to 1
///
/// [1, 2]
/// l = 1,  m = 1, r=2
/// l = m, break.

int findMin(vector<int> nums) {
  int l = 0;
  int r = nums.size() - 1;

  while (l < r) {
    int m = l + (r - l) / 2;

    if (nums[m] > nums[r]) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return nums[l];
}

int main() {
  TestTimer timer;
  ExpectEq(findMin({3, 4, 5, 1, 2}), 1);
}
