#include "testSuite.h"
#include <unordered_map>

using namespace std;

/// I got a O(s2) = O(n) time solution with a sliding window
/// O(s1 + s2) space, because of two maps of same size max
///

// Now us a frequency map

bool checkInclusion(string s1, string s2) {
  int l = 0;
  int r = s1.size() - 1;

  array<int, 26> count;
  for (auto &c : count) {
    c = 0;
  }

  while (r < s2.size()) {
    // First char should be precent inside of the map.
    if (charCountMap.contains(s2[l])) {
      // Here we need to check if all chars are inside of the map.
      //
      // We create a copy of the map and decrement all char counts, when char
      // count is 0, remove it from the map.
      auto copyMap = charCountMap;

      int i = l;
      while (i <= r) {
        // If value is net precent in map. stop.
        if (!copyMap.contains(s2[i])) {
          break;
        }

        // Decrement char count
        copyMap[s2[i]]--;
        if (copyMap[s2[i]] == 0) {
          // Remove char
          copyMap.erase(s2[i]);
        }

        // Increment walker.
        i++;
      }

      if (copyMap.empty()) {
        return true;
      }
    }

    l++;
    r++;
  }

  return false;
}

int main() {
  ExpectEq(checkInclusion("abc", "abc"), true);
  ExpectEq(checkInclusion("abc", "jfacabb"), true);
  ExpectEq(checkInclusion("abc", "abd"), false);
}
