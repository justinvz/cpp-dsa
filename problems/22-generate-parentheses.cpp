#include <gtest/gtest.h>

#include <algorithm>
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

  std::function<void(std::string parenthese, int opened, int closed)> backtrace;

  backtrace = [&](std::string parenthese, int opened, int closed) {
    if (parenthese.size() == n * 2) {
      if (opened == closed) { // Insert this, otherwise just return!
        result.push_back(parenthese);
      }
      return;
    }

    parenthese.push_back('('); // should either add '(' or ')'
    backtrace(parenthese, opened + 1, closed);

    if (opened > closed) { // Only close when something is open!
      parenthese.pop_back();
      parenthese.push_back(')'); // should either add '(' or ')'
      backtrace(parenthese, opened, closed + 1);
    }
  };

  backtrace({"("}, 1, 0);

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
