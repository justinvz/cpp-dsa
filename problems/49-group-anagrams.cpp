#include "testSuite.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

/// @problem
///
/// Given an array of strings strs, group the anagrams together. You can return
/// the answer in any order
///
/// @constrains
///
/// 1 <= str.length <= 10^4
/// 0 <= strs[i].length <= 100
///
/// @solution 1 brute force
///
/// itterate through strs
/// - sort each string and add to hashmap, where value is the array of string
/// indexes.
///
///
/// Time complexity
/// need to sort each string. which at max can be 10^4 strings of size 100 * n
/// O (n * k log k)
///
///
/// Space complexity = O(n * k)

vector<vector<string>> GroupedAnagram(vector<string> &strs) {
  unordered_map<string, std::vector<size_t>> anagramsMap;

  for (size_t i{0}; i < strs.size(); i++) {
    string str = strs[i];
    std::sort(str.begin(), str.end());
    if (!anagramsMap.contains(str)) {
      anagramsMap[str] = {i};
    } else {
      anagramsMap[str].emplace_back(i);
    }
  }

  vector<vector<string>> grouped;
  for (auto group : anagramsMap) {
    vector<string> newGroup;
    for (auto index : group.second) {
      newGroup.emplace_back(strs[index]);
    }
    grouped.emplace_back(newGroup);
  }

  return grouped;
}

int main() {
  // auto nums = std::vector<int>{2, 7, 11, 15};
  // ExpectEq(TwoSum(nums, 9), std::vector<int>{0, 1});
}
