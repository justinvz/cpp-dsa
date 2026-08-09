#include <gtest/gtest.h>

#include <cstddef>
#include <functional>
#include <vector>

using namespace std;

/// @problem first backtracking problem solved by watching a video, concept
/// seems okeyish, but still difficult, i should revisit this problem!
///

vector<vector<int>> subsets(vector<int> nums) {

  vector<vector<int>> result;
  vector<int> subset;

  std::function<void(size_t)> dfs = [&](size_t i) {
    if (i >= nums.size()) {
      result.push_back(subset);
      return;
    }

    subset.push_back(nums[i]);
    dfs(i + 1);

    subset.pop_back();
    dfs(i + 1);
  };

  dfs(0);
  return result;
}

TEST(Problem, ExistingCases) {
  subsets({1, 2, 3});
  subsets({1, 2, 3, 4});
  SUCCEED();
}
