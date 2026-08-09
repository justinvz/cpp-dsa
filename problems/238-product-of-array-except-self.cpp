
#include <gtest/gtest.h>

#include <cstddef>
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

TEST(Problem, ExistingCases) {
  EXPECT_EQ(ProductExcpetSelf({1, 2, 4, 6}),
            (std::vector<int>{48, 24, 12, 8}));
  EXPECT_EQ(ProductExcpetSelf({-1, 0, 1, 2, 3}),
            (std::vector<int>{0, -6, 0, 0, 0}));
  EXPECT_EQ(ProductExcpetSelf({0, 0}), (std::vector<int>{0, 0}));
}
