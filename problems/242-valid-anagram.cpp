#include <gtest/gtest.h>

#include <array>
#include <string>

using namespace std;

/// @problem
///
/// Given two strings s and t, return true if t is an anagram of s, and false
/// otherwise.
///
/// @Constraints
///
/// 1 <= s.length, t.length <= 5*10^4
/// s and t contain lowercase letters
///
/// Anagram is formed by using the letters of another word, all letters should
/// be used.
///
/// @Solution (1)
/// use a hashmap to count the letters used, and check if the other word has the
/// same count.
///
/// Time complexity
/// O(n)
///
/// Space complexity
/// O(n)
///
/// @Solution (2)
/// direct indexing, instead of using a hashmap.
///
/// Time complexity
/// O(2n)
///
/// Space complexity
/// O(1)

bool IsAnagram(string s, string t) {
  array<int, 26> directIndexed;
  directIndexed.fill(0);

  if (s.length() != t.length()) {
    return false;
  }

  /// Check letters in s
  for (int c : s) {
    directIndexed[c - 97]++;
  }

  /// Check letters in t and Check if the have the same letters
  for (int c : t) {
    directIndexed[c - 97]--;
  }

  for (int index : directIndexed) {
    if (index != 0) {
      return false;
    }
  }
  return true;
}

TEST(Problem, ExistingCases) {
  EXPECT_TRUE(IsAnagram("stapel", "pastel"));
  EXPECT_TRUE(IsAnagram("spreektaal", "speelkaart"));
  EXPECT_TRUE(IsAnagram("anagram", "nagaram"));
  EXPECT_FALSE(IsAnagram("rat", "car"));
  EXPECT_FALSE(IsAnagram("poep", "goed"));
  EXPECT_FALSE(IsAnagram("kak", "pap"));
}
