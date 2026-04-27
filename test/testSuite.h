#include <cassert>
#include <iostream>
#include <string>

using namespace std;

inline void ExpectTrue(bool actual, const string &testName = "") {

  if (actual) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cout << "[FAIL] condition is false" << testName << "\n";
    assert(false);
  }
}

inline void ExpectFalse(bool actual, const string &testName = "") {
  if (!actual) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cout << "[FAIL] condition is true" << testName << "\n";
    assert(false);
  }
}

template <typename T>
void ExpectEq(const T &actual, const T &expected, const string &testName = "") {

  if (actual == expected) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cout << "[FAIL] " << testName << "\n";
    cout << " Axpected: " << expected << "\n";
    cout << " Actual: " << actual << "\n";
    assert(false);
  }
}
