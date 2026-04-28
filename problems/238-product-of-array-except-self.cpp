
#include "testSuite.h"
#include <vector>

using namespace std;

/// @problem
///
/// Use prefix and suffix product array.

vector<int> ProductExcpetSelf(vector<int> nums) {
  vector<int> result;

  vector<int> prefix;
  prefix.reserve(nums.size());

  int product = 1;
  for (auto num : nums) {
    prefix.push_back(product);
    product *= num;
  }

  vector<int> sufix(nums.size());
  product = 1;

  for (int i = nums.size() - 1; i >= 0; i--) {
    sufix[i] = product;
    product *= nums[i];
  }

  for (size_t i{0}; i < nums.size(); i++) {
    result.push_back(sufix[i] * prefix[i]);
  }

  return result;
}

int main() {
  ExpectEq(ProductExcpetSelf({1, 2, 4, 6}), {48, 24, 12, 8});
  ExpectEq(ProductExcpetSelf({-1, 0, 1, 2, 3}), {0, -6, 0, 0, 0});
  ExpectEq(ProductExcpetSelf({0, 0}), {0, 0});
}
