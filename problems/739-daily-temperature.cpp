
#include "testSuite.h"
#include <stack>
#include <stdexcept>

using namespace std;

/// @problem answer[i] is the number of days you have to wait afte ith day. if
/// there is no future day for which this is possible, keep answer[i] == 0
/// instead

vector<int> DailyTemperatures(vector<int> temperatures) {
  stack<int> stack;
  vector<int> awnser;
  awnser.reserve(temperatures.size());
  awnser.assign(temperatures.size(), 0);

  for (size_t i{0}; i < temperatures.size(); i++) {
    while (!stack.empty() && temperatures[stack.top()] < temperatures[i]) {
      awnser[stack.top()] = i - stack.top();
      stack.pop();
    }
    stack.push(i);
  }
  return awnser;
}

int main() {
  TestTimer timer;

  ExpectEq(DailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}),
           {1, 1, 4, 2, 1, 1, 0, 0});
}
