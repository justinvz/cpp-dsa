
#include "testSuite.h"
#include <unordered_map>
#include <unordered_set>

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
//
// Notice that you may not slant the container.
//
/// Solution? Naive solution is O(n^2) where you check all combinations.
/// We can however be a bit smarter and use two pointers. We start left and
/// right and move inwards constantly moving the lowest pointer to optimize the
/// surface area. Each time we move inward, the width decreases by one.

int MaxArea(vector<int> height) {
  int left = 0;
  int right = height.size() - 1;
  int area = 0;

  int width = height.size() - 1;

  int largestArea{0};

  while (left < right) {

    if (height[left] < height[right]) {
      area = height[left] * width;
      left++;
    } else {
      area = height[right] * width;
      right--;
    }
    width--;

    if (area > largestArea) {
      largestArea = area;
    }
  }

  return largestArea;
}

int main() {
  TestTimer timer;
  ExpectEq(MaxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}), 49);
  ExpectEq(MaxArea({1, 1}), 1);
}
