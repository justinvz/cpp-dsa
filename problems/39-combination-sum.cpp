#include <gtest/gtest.h>

#include <cstddef>
#include <functional>
#include <vector>

using namespace std;

/// @solution is backtracking
///
/// I think a good way to solve this problem is to first sort, when doing that
/// we can optimize.

vector<vector<int>> combinationSum(vector<int> candidates, int target) {
  vector<vector<int>> result;

  vector<int> combination;
  int sum{0};

  std::function<void(size_t)> dfs = [&](size_t i) {
    if (sum == target) {
      result.push_back(combination);
      return;
    }

    if (sum > target || i >= candidates.size()) {
      return;
    }

    combination.push_back(candidates[i]);
    sum += candidates[i];

    dfs(i);

    // go back
    combination.pop_back();
    sum -= candidates[i];

    dfs(i + 1);
  };

  dfs(0);
  return result;
}

TEST(Problem, ExistingCases) { SUCCEED(); }
