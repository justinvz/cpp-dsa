
#include "testSuite.h"
#include <stack>

/// @problem Given an array of integers temperatures represents the daily
/// temperatures, return an array answer such that answer[i] is the number of
/// days you have to wait after the ith day to get a warmer temperature. If
/// there is no future day for which this is possible, keep answer[i] == 0
/// instead.
///
/// @Solution
///
/// So we could review each temperature with each other to check if the there is
/// a warmer day, this will however be a O(n^2) solution and we are not noobs.
///
/// What we can do is go through each element, when the next element is higher,
/// we know that we the difference is only one day.
///
/// However, when that element is not higher, we should put this day into the
/// stack.
///
/// When we go to the next day, we first check if the day after that day is
/// higher, if so, we put 1 in that place, and we can check if the day in the
/// stack is lower, if lower, we put difference in index in the stack, if not we
/// continue.

using namespace std;

vector<int> DailyTemperatures(vector<int> temperatures) {
  struct Day {
    std::size_t index{0};
    int temperature{0};
  };

  stack<Day> stack;
  vector<int> result;
  result.assign(temperatures.size(), 0);

  for (std::size_t i{0}; i < temperatures.size(); i++) {
    while (!stack.empty() && stack.top().temperature < temperatures[i]) {
      result[stack.top().index] = i - stack.top().index;
      stack.pop();
    }

    stack.push({i, temperatures[i]});
  }

  return result;
}

int main() {
  TestTimer timer;

  ExpectEq(DailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}),
           {1, 1, 4, 2, 1, 1, 0, 0});

  ExpectEq(DailyTemperatures({30, 40, 50, 60}), {1, 1, 1, 0});

  ExpectEq(DailyTemperatures({30, 60, 90}), {1, 1, 0});
}
