
#include "testSuite.h"
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

/// @problem
///
/// Given an integer array nums and an integer k, return the k most frequent
/// elements. You may return the answer in any order.
///
/// @constrains
///
/// 1 <= nums.length <= 10^5
///
/// -10^4 <= nums[i] <= 10^4
///
/// k is sin range [1, the number of unique elements in the array].
///
/// it is guaranteed that the answer is unique.
///
/// @solution 1
///
/// Place each element inside of a map, where the first element is the key and
/// second element the amount of times the value has been seen. O(n)
///
/// Created binary/red black tree and fetch k highest elements.
///
/// combined is O {(n + n log n) = O(n log n)
///

vector<int> TopKFrequent(vector<int> &nums, int k) {
  unordered_map<int, int> occurrenceMap;

  for (const auto num : nums) {
    if (occurrenceMap.contains(num)) {
      occurrenceMap[num]++;
    } else {
      occurrenceMap[num] = 1;
    }
  }

  vector<pair<int, int>> vec(occurrenceMap.begin(), occurrenceMap.end());

  sort(vec.begin(), vec.end(),
       [](auto a, auto b) { return a.second > b.second; });

  for (auto [num, occ] : vec) {
    std::cout << "num: " << num << " occ: :" << occ << std::endl;
  }

  vector<int> output;

  auto it = vec.begin();
  for (size_t i{0}; i < k; i++) {
    output.emplace_back(it->first);
    it = next(it);
  }

  return output;
}

int main() {
  vector<int> nums = {1, 1, 1, 2, 2, 3};
  ExpectEq(TopKFrequent(nums, 2), {1, 2});

  nums = {1};
  ExpectEq(TopKFrequent(nums, 1), {1});

  nums = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
  ExpectEq(TopKFrequent(nums, 2), {1, 2});
}
