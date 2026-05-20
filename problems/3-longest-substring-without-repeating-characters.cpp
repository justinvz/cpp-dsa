#include "testSuite.h"
#include <unordered_map>

using namespace std;

/// @problem
///
///
/// @solution

int LengthOfLongestSubstring(string s) {
  size_t l = 0;
  int maxLength = 0;

  unordered_map<char, size_t> mapping;

  for (size_t i = 0; i < s.size(); i++) {
    if (mapping.contains(s[i]) && mapping[s[i]] >= l) {
      l = mapping[s[i]] + 1;
    }
    mapping[s[i]] = i;

    int length = i - l + 1;
    maxLength = max(maxLength, length);
  }

  return maxLength;
}

int main() {
  ExpectEq(LengthOfLongestSubstring("abcabcbb"), 3);
  ExpectEq(LengthOfLongestSubstring("bbbbb"), 1);
  ExpectEq(LengthOfLongestSubstring("pwwkew"), 3);
  ExpectEq(LengthOfLongestSubstring("abcabcbb"), 3);
}
