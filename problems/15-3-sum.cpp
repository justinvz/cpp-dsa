#include "testSuite.h"
#include <algorithm>
#include <stack>

using namespace std;

// @problem Given an integer array nums, return all the triplets [nums[i],
// nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j]
// + nums[k] == 0. Notice that the solution set must not contain duplicate
// triplets.
//
// so the sum of num[i] + num[j] + num[k] = 0.
//
// @ Solution
//
// We have to find the sum of three elements that is equal of 0, we cannot use
// the same value twice in the same triplet.
//
// we can sort the array first, fix one number and use two pointers to check for
// value.
//
// sorted = [-4,-1,-1,0,1,2]

vector<vector<int>> ThreeSum(vector<int> nums) {
  std::sort(nums.begin(), nums.end());

  vector<vector<int>> result;

  for (size_t i{0}; i < nums.size(); i++) {
    int target = nums[i];

    // Skip if target is the same as previous number.
    if (i > 0 && target == nums[i - 1]) {
      continue;
    }

    int pointerA = i + 1;
    int pointerB = nums.size() - 1;

    while (pointerA < pointerB) {
      auto sum = nums[pointerA] + nums[pointerB];

      // A + B = -target is result
      if (sum == -target) {
        result.emplace_back(
            std::vector{nums[pointerA], nums[pointerB], nums[i]});
        pointerA++;
        pointerB--;

      } else if (sum < -target) {
        pointerA++;
      } else if (sum > -target) {
        pointerB--;
      }
    }
  }

  return result;
}

int main() {
  TestTimer timer;

  std::cout << "print" << std::endl;
  auto vect = ThreeSum({-1, 0, 1, 2, -1, -4});
  for (const auto &row : vect) {
    for (int x : row) {
      std::cout << x << ' ';
    }
    std::cout << '\n';
  }

  std::cout << "print" << std::endl;
  vect = ThreeSum({0, 1, 1});
  for (const auto &row : vect) {
    for (int x : row) {
      std::cout << x << ' ';
    }
    std::cout << '\n';
  }

  std::cout << "print" << std::endl;
  vect = ThreeSum({0, 0, 0});
  for (const auto &row : vect) {
    for (int x : row) {
      std::cout << x << ' ';
    }
    std::cout << '\n';
  }
}
