#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

/// @problem 22. Generate Parentheses
/// @difficulty Medium
///
/// Given n pairs of parentheses, write a function to generate all combinations
/// of well-formed parentheses.
///
/// Constraints:
/// - 1 <= n <= 8
///
/// @starttime 21:46 31-08-26

std::vector<std::string> generateParenthesis(int n) {
  std::vector<std::string> result;
  std::string path;

  std::function<void(int opened, int closed)> backtrack;
  backtrack = [&](int opened, int closed) {
    if (opened == n && closed == n) {
      result.push_back(path);
      return;
    }

    if (opened < n) {
      path.push_back('(');
      backtrack(opened + 1, closed);
      path.pop_back();
    }

    if (closed < opened) {
      path.push_back(')');
      backtrack(opened, closed + 1);
      path.pop_back();
    }
  };

  backtrack(0, 0);

  return result;
}

void expectParentheses(std::vector<std::string> actual,
                       std::vector<std::string> expected) {
  std::ranges::sort(actual);
  std::ranges::sort(expected);
  EXPECT_EQ(actual, expected);
}

TEST(GenerateParentheses, HandlesOnePair) {
  expectParentheses(generateParenthesis(1), {"()"});
}

TEST(GenerateParentheses, GeneratesTwoPairs) {
  expectParentheses(generateParenthesis(2), {"(())", "()()"});
}

TEST(GenerateParentheses, GeneratesThreePairs) {
  expectParentheses(generateParenthesis(3),
                    {"((()))", "(()())", "(())()", "()(())", "()()()"});
}
