import jtd.vector;

#include "testSuite.h"

int main() {
  jtd::vector vector;

  ExpectTrue(vector.empty(), "default vector is empty");
  ExpectEq(vector.capacity(), size_t{10}, "default vector capacity");

  return EXIT_SUCCESS;
}
