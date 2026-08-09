#include "testSuite.h"
#include "vector.hpp"

int main() {
  jtd::vector<int> vector;

  vector.push_back(3);

  ExpectTrue(vector.empty(), "default vector is empty");
  ExpectEq(vector.capacity(), std::size_t{10}, "default vector capacity");

  return EXIT_SUCCESS;
}
