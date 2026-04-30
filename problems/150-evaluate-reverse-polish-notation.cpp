#include "testSuite.h"
#include <stack>

using namespace std;

/// @problem Evaluate the expressions. Return an integer that represents the
/// value of expressions.
///
/// - The valid operators are '+', '-', '*', "/"
/// - Each operand may be an integer or another expression
/// - the devision between two integers always truncates towards zero.
/// (imporant)
/// - there wil not be any divisions by zero.
/// - the input represents a valid arithmatic exression in a revese polish
/// notation.
/// - the answer and all the intermediate calculations can be represetnted in a
/// 32-bit integer.
///
///
/// @ Reverse Polish notation
/// push numbers on a stack from left to right. when operator encountered,
/// preform action on the last two operants. push result on the stack. outcome
/// is the top of the stack!

int evalRPN(vector<string> tokens) {
  std::stack<int> stack;

  for (string token : tokens) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      int y = stack.top();
      stack.pop();
      int x = stack.top();
      stack.pop();

      if (token == "+") {
        stack.push(x + y);
      }

      if (token == "-") {
        stack.push(x - y);
      }

      if (token == "*") {
        stack.push(x * y);
      }

      if (token == "/") {
        stack.push(x / y);
      }
      continue;
    }

    int x = std::stoi(token);
    stack.push(x);
  }

  if (stack.empty()) {
    return 0;
  }

  return stack.top();
}

int main() {
  TestTimer timer;

  vector<string> tokens = {"10", "6", "9",  "3", "+", "-11", "*",
                           "/",  "*", "17", "+", "5", "+"};
  ExpectEq(evalRPN(tokens), 22);
}
