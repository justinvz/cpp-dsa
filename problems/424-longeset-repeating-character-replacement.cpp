#include "testSuite.h"
#include <unordered_map>

using namespace std;

int characterReplacemnet(string s, int k) {
  size_t l = 0;
  size_t r = 0;

  unordered_map<char, int> freqMap;

  int result{0};
  while (r < s.size()) {
    freqMap[s[r]] = freqMap[s[r]] + 1;

    size_t length = r - l + 1;

    int highestFreq{0};
    for (auto &[key, freq] : freqMap) {
      if (freq > highestFreq) {
        highestFreq = freq;
      }
    }

    if (length - highestFreq <= k) {
      if (length > result) {
        result = length;
      }
    } else {
      freqMap[s[l]]--;
      l++;
    }

    r++;
  }

  return result;
}

int main() {
  ExpectEq(characterReplacemnet("ABAB", 2), 4);
  ExpectEq(characterReplacemnet("AABABBA", 1), 4);
}
