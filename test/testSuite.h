
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline void ExpectTrue(bool actual, const string &testName = "") {
  if (actual) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cout << "[FAIL] " << testName << " (expected true)\n";
  }
}

inline void ExpectFalse(bool actual, const string &testName = "") {
  if (!actual) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cout << "[FAIL] " << testName << " (expected false)\n";
  }
}

// ---------------------- SCALAR EXPECT EQ ----------------------

template <typename T>
inline void ExpectEq(const T &actual, const T &expected,
                     const string &testName = "") {
  if (actual == expected) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cout << "[FAIL] " << testName << "\n";
    cout << "  Expected: " << expected << "\n";
    cout << "  Actual:   " << actual << "\n";
  }
}

template <typename T>
inline void ExpectEq(const vector<T> &actual, const vector<T> &expected,
                     const string &testName = "") {

  if (actual == expected) {
    cout << "[PASS] " << testName << "\n";
    return;
  }

  cout << "[FAIL] " << testName << "\n";
  cout << "  Expected: [";
  for (size_t i = 0; i < expected.size(); i++) {
    cout << expected[i];
    if (i + 1 < expected.size())
      cout << ", ";
  }
  cout << "]\n";

  cout << "  Actual:   [";
  for (size_t i = 0; i < actual.size(); i++) {
    cout << actual[i];
    if (i + 1 < actual.size())
      cout << ", ";
  }
  cout << "]\n";
}

template <typename T, size_t N>
inline void ExpectEq(const array<T, N> &actual, const array<T, N> &expected,
                     const string &testName = "") {

  if (actual == expected) {
    cout << "[PASS] " << testName << "\n";
    return;
  }

  cout << "[FAIL] " << testName << "\n";

  cout << "  Expected: [";
  for (size_t i = 0; i < N; i++) {
    cout << expected[i];
    if (i + 1 < N)
      cout << ", ";
  }
  cout << "]\n";

  cout << "  Actual:   [";
  for (size_t i = 0; i < N; i++) {
    cout << actual[i];
    if (i + 1 < N)
      cout << ", ";
  }
  cout << "]\n";

  assert(false);
}
