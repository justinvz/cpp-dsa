#include "testSuite.h"
#include <algorithm>

using namespace std;

/// Output should not contain any duplicate triplets. you amy return the output
/// and the triplets in any order!
///
/// given nums, return all the triplets where num[i] + num[j] + num[k] == 0 and
/// i != j != k

vector<vector<int>> ThreeSum(vector<int> nums) {
  // Two pointer solution?

  // first, we need to sort the array
  std::sort(nums.begin(), nums.end());
  vector<vector<int>> results;

  for (int i = 0; i < nums.size() - 2; ++i) {
    if (i > 0 && nums[i] == nums[i - 1])
      continue;

    int j = i + 1;
    int k = nums.size() - 1;

    while (j < k) {
      int sum = nums[i] + nums[j] + nums[k];
      if (sum == 0) {
        results.push_back({nums[i], nums[j], nums[k]});

        ++j;
        --k;

        while (j < k && nums[j] == nums[j - 1])
          ++j;
        while (j < k && nums[k] == nums[k + 1])
          --k;
      } else if (sum < 0) {
        ++j;
      } else {
        --k;
      }
    }
  }

  return results;
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
