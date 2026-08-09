#include <gtest/gtest.h>

#include <array>
#include <string>
#include <unordered_map>

using namespace std;

/// I got a O(s2) = O(n) time solution with a sliding window
/// O(s1 + s2) space, because of two maps of same size max
///

// Now us a frequency map

bool checkInclusion(string s1, string s2) {
  int l = 0;

  array<int, 26> count1{};
  array<int, 26> count2{};

  for (auto &c : s1) {
    count1[c - 'a']++;
  }

  for (int r = 0; r < s2.size(); r++) {
    count2[s2[r] - 'a']++;

    if (r - l + 1 > s1.size()) {
      count2[s2[l] - 'a']--;
      l++;
    }

    if (count1 == count2) {
      return true;
    }
  }

  return false;
}
TEST(Problem, ExistingCases) {
  EXPECT_EQ(checkInclusion("abc", "abc"), true);
  EXPECT_EQ(checkInclusion("abc", "jfacabb"), true);
  EXPECT_EQ(checkInclusion("abc", "abd"), false);
}
