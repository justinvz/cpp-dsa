#include "testSuite.h"
#include <stack>
#include <unordered_map>

using namespace std;

/// @problem
///
/// Check a string for propper opening and closng brackets. Remember that you
/// have to close a bracket in the right order.
///
///
/// @solution O(n)
///
/// Itterate through it and place the brackets in a stack. now when you encouter
/// a closing bracket. pop from the stack. if there is a bracket mismatch,
/// return false.

bool IsValid(string s) {
  std::unordered_map<char, char> mapping = {{')', '('}, {'}', '{'}, {']', '['}};
  std::stack<char> stack;

  for (char c : s) {
    if (mapping.find(c) != mapping.end()) {
      if (stack.empty() || stack.top() != mapping[c]) {
        return false;
      }
      stack.pop();
    } else {
      stack.push(c);
    }
  }
  return stack.empty();
}

int main() {
  TestTimer timer;

  ExpectTrue(IsValid("()"));
  ExpectTrue(IsValid("()[]{}"));
  ExpectFalse(IsValid("(]"));
  ExpectTrue(IsValid("([])"));
  ExpectFalse(IsValid("([)]"));
}
