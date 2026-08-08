#pragma once

#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TestTimer {
private:
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();

public:
  TestTimer() : start(std::chrono::high_resolution_clock::now()) {}
  ~TestTimer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    cout << "[TIME] took " << duration.count() << " us\n";
  }
};

inline void ExpectTrue(bool actual, const string &testName = "") {
  if (actual) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cerr << "[FAIL] " << testName << " (expected true)\n";
    std::exit(EXIT_FAILURE);
  }
}

inline void ExpectFalse(bool actual, const string &testName = "") {
  if (!actual) {
    cout << "[PASS] " << testName << "\n";
  } else {
    cerr << "[FAIL] " << testName << " (expected false)\n";
    std::exit(EXIT_FAILURE);
  }
}

// ---------------------- SCALAR EXPECT EQ ----------------------

template <typename T>
inline void ExpectEq(const T &actual, const T &expected,
                     const string &testName = "") {
  if (actual == expected) {
    cout << "[PASS] " << testName;
    cout << "\n  Actual:   " << actual << "\n";
    cout << "  Expected: " << expected << "\n";
  } else {
    cerr << "[FAIL] " << testName << "\n";
    cerr << "\n  Expected: " << expected << "\n";
    cerr << "  Actual:   " << actual << "\n";
    std::exit(EXIT_FAILURE);
  }
}

template <typename T>
inline void ExpectEq(const vector<T> &actual, const vector<T> &expected,
                     const string &testName = "") {

  if (actual == expected) {
    cout << "[PASS] " << testName;
    cout << "  : [";
    for (size_t i = 0; i < expected.size(); i++) {
      cout << expected[i];
      if (i + 1 < expected.size())
        cout << ", ";
    }
    cout << "]\n";

    return;
  }

  cerr << "[FAIL] " << testName << "\n";
  cerr << "  Expected: [";
  for (size_t i = 0; i < expected.size(); i++) {
    cerr << expected[i];
    if (i + 1 < expected.size())
      cerr << ", ";
  }
  cerr << "]\n";

  cerr << "  Actual:   [";
  for (size_t i = 0; i < actual.size(); i++) {
    cerr << actual[i];
    if (i + 1 < actual.size())
      cerr << ", ";
  }
  cerr << "]\n";
  std::exit(EXIT_FAILURE);
}

template <typename T, size_t N>
inline void ExpectEq(const array<T, N> &actual, const array<T, N> &expected,
                     const string &testName = "") {

  if (actual == expected) {
    cout << "[PASS] " << testName << "\n";
    return;
  }

  cerr << "[FAIL] " << testName << "\n";

  cerr << "  Expected: [";
  for (size_t i = 0; i < N; i++) {
    cerr << expected[i];
    if (i + 1 < N)
      cerr << ", ";
  }
  cerr << "]\n";

  cerr << "  Actual:   [";
  for (size_t i = 0; i < N; i++) {
    cerr << actual[i];
    if (i + 1 < N)
      cerr << ", ";
  }
  cerr << "]\n";
  std::exit(EXIT_FAILURE);
}
