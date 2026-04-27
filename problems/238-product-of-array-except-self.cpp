
#include "testSuite.h"
#include <vector>

using namespace std;

/// @problem
/// otherwise.

vector<int> ProductExcpetSellf(vector<int> nums) {
  vector<int> result;

  int product{1};
  bool zero{false};

  for (const auto num : nums) {
    product = product * num;

    if (zero && num == 0) // When two zero's in range, return array with
    {
      result.assign(nums.size(), 0);
      return result;
    }

    if (num == 0) {
      zero = true;
    }
  }

  for (const auto num : nums) {
    if (num == 0) {
      int zeroProduct{1};
      for (const auto num : nums) {
        if (num != 0) {
          zeroProduct = zeroProduct * num;
        }
      }
      result.emplace_back(zeroProduct);
    } else {
      result.emplace_back(product / num);
    }
  }

  return result;
}

int main() {
  ExpectEq(ProductExcpetSellf({1, 2, 4, 6}), {48, 24, 12, 8});
  ExpectEq(ProductExcpetSellf({-1, 0, 1, 2, 3}), {0, -6, 0, 0, 0});
  ExpectEq(ProductExcpetSellf({0, 0}), {0, 0});
}
