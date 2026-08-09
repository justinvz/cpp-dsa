#include <gtest/gtest.h>

#include <limits>
#include <stack>

using namespace std;

/// @problem design a stack that supports push, pop, top and retrieving the
/// minimum element in constant time.

class MinStack {
public:
  MinStack() { min.push(std::numeric_limits<int>::max()); }

  void push(int val) {
    stack.push(val);

    if (val <= min.top()) {
      min.push(val);
    }
  }

  void pop() {
    if (stack.top() == min.top()) {
      min.pop();
    }
    stack.pop();
  }

  int top() { return stack.top(); }

  int getMin() { return min.top(); }

private:
  std::stack<int> stack;
  std::stack<int> min;
};

TEST(Problem, ExistingCases) {

  MinStack stack;
  stack.push(-2);
  stack.push(0);
  stack.push(-3);
  EXPECT_EQ(stack.getMin(), -3);
  stack.pop();
  EXPECT_EQ(stack.top(), 0);
  EXPECT_EQ(stack.getMin(), -2);
}
