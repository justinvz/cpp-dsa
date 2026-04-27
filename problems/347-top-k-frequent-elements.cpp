
#include "testSuite.h"
#include <map>
#include <queue>
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
/// @ solution 2
///
/// instead of sorting a array, we can also use a priority queue, which
/// impelents a heap, each element is sorted on insertion.
///

struct Node {};

vector<int> TopKFrequent(vector<int> &nums, int k) {
  unordered_map<int, int> occurrenceMap;

  for (const auto num : nums) {
    occurrenceMap[num]++;
  }

  std::priority_queue<std::pair<int, int>> queue;

  for (const auto [num, accourence] : occurrenceMap) {

    pair<int, int> entry;
    entry.first = accourence;
    entry.second = num;
    queue.emplace(entry);
  }

  vector<int> output;

  while (k-- && !queue.empty()) {
    output.push_back(queue.top().second);
    queue.pop();
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
