#include "testSuite.h"
#include "vector.hpp"

#include <print>

int main() {
  jtd::vector<int> vector;

  ExpectTrue(vector.empty(), "default vector is empty");
  ExpectEq(vector.capacity(), std::size_t{10}, "default vector capacity");

  constexpr int elements{10};

  for (size_t i = 0; i < elements; i++) {
    vector.push_back(i);
  }

  for (size_t i = 0; i < elements; i++) {
    println("Values {}", vector.at(i));
  }

  vector.push_back(1);
  vector[elements + 1];

  return EXIT_SUCCESS;
}
