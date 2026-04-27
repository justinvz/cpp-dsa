#include "testSuite.h"
#include <cassert>
#include <unordered_set>
#include <vector>

using namespace std;

/// @problem
///
/// Given an integer array 'nums', return 'true' if any value appears more than
/// once in the array, otherwise return 'false'.
///
/// @example
///
/// input: nums [1, 2, 3, 3]
///
/// Output: true
///
/// input: nums [1, 2, 3, 4]
///
/// Output: false
///
/// @ Solution (1)
///
/// iterate through nums, and add values to a hash table, when hash already
/// exist, double value is found, and true is return,  return false when no
/// duplicates are found.
///
/// Time complexity: At max, you'll need to check all numbers.
///   O(nums.size()) -> O(n)
/// Space complexity: You will need to create a extra hash map.
///   O(2n), thus O(n)
///

bool HasDuplicate(vector<int> &nums) {
  std::unordered_set<int> seen;

  for (const int num : nums) {
    if (seen.contains(num)) {
      return true;
    }
    seen.insert(num);
  }

  return false;
}

int main() {
  vector<int> nums = {1, 2, 3, 3};
  ExpectTrue(HasDuplicate(nums));

  nums = {1, 2, 3, 4};
  ExpectFalse(HasDuplicate(nums));
}
