#include "testSuite.h"
#include <functional>

using namespace std;

/// @solution is backtracking starttime: 22:07 - 22:044
///
/// @ Solution is also backtracing. Difference between this one and the first
/// one is that we can only use a number once per combinaiton. so we have to
/// change the algorithm a bit.
///
/// So first think about the time complexity.
///
/// So what we need to to do is create a decision tree.
///
/// lets say we have [2, 5, 2, 1, 2]. we go from left to right.
///
/// 2 + 5 = 7, which is < 5. go to next.
/// 5 = 5, 5 is one of the combinations.
/// 2 + 1 + 2 = 5 is one of the combinations.
///
/// [10, 1, 2, 7, 6, 1, 5] target 8
///
/// 10 < 8. next
///
/// 1 + 10 > 8, go back.
/// 1 + 2 = 3
/// 1 + 2 + 7 = 10
/// 1 + 2 + 6 = 9
/// 1 + 2 + 1 = 5
/// 1 + 2 + 1 + 5 = 8 (v)
///
/// 2 + 10
/// 2 + 1 +
///
vector<vector<int>> combinationSum(vector<int> candidates, int target) {
  vector<vector<int>> result;

  vector<int> combination;
  int sum{0};

  std::sort(candidates.begin(), candidates.end());

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

    dfs(i + 1);

    // go back
    combination.pop_back();
    sum -= candidates[i];

    while (i + 1 < candidates.size() && candidates[i] == candidates[i + 1]) {
      i++;
    }

    dfs(i + 1);
  };

  dfs(0);
  return result;
}

int main() {}
