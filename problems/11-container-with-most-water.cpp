
#include "testSuite.h"

using namespace std;

// Start time = 17:24

/// @problem
// You are given an integer array height of length n. There are n vertical lines
// drawn such that the two endpoints of the ith line are (i, 0) and (i,
// height[i]).
//
// Find two lines that together with the x-axis form a container, such that the
// container contains the most water.
//
// Return the maximum amount of water a container can store.

int MaxArea(vector<int> height) {
  // Solution can be done by using two pointers.
  //
  // We walk from the sides to the middle. We remember the largest container,
  // and only walk the smallest pointer inwarts.
  //
  // Once pointers meet, we returun the biggest area.

  int area = 0;
  int largestArea = area;

  int left = 0;
  int right = height.size() - 1;

  while (left != right) {
    if (height[left] > height[right]) {
      area = height[right] * (right - left);
      right--;
    } else if (height[left] <= height[right]) {
      area = height[left] * (right - left);
      left++;
    }

    if (largestArea < area)
      largestArea = area;
  };

  return largestArea;
}

int main() {
  TestTimer timer;
  ExpectEq(MaxArea({1, 7, 2, 5, 4, 7, 3, 6}), 36);
  ExpectEq(MaxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}), 49);
  ExpectEq(MaxArea({1, 1}), 1);
}
