#include "testSuite.h"
#include "vector.hpp"

#include <print>

int main() {
  jtd::vector<int> vector;

  ExpectTrue(vector.empty(), "default vector is empty");
  ExpectEq(vector.capacity(), jtd::defaultSize, "default vector capacity");

  constexpr int elements{100};

  for (size_t i = 0; i < elements; i++) {
    vector.push_back(i);
  }

  for (size_t i = 0; i < elements; i++) {
    // ExpectEq(vector[i], (int)i);
  }

  println("");

  // Out of bounds
  vector[elements + 1];

  return EXIT_SUCCESS;
}
