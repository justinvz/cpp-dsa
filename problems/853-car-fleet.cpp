
#include "testSuite.h"
#include <map>
#include <stack>

using namespace std;

/// @problem
/// There are n cars at given miles away from the startng mile 0, travelling to
/// reach the mile target.
///
/// you are given two integer arrays 'position' and 'speed' both of length 'n',
/// where 'position[i]' is the starting mile of the 'i th' mile per hour.
///
/// A car cannot pass another car, but it can catch up and then travel nexct to
/// it at the pseed of the slower car.
///
/// a car fleet is a single car or a group of cars driving next to each other.
/// The speed of the car fleet is the minimum speed of any car in the fleet.
///
/// if a car catches up to a car fleet at the mile 'target', it will still be
/// considered as part of the car fleet.
///
/// return the number of car fleets that will arrive at the destination.
///
/// @ Solution
///
/// Create a mapping of the closest cars to the target and the time it takes to
/// get to the target:
///   - Sort cars based on the position. O(log(n))
///   - Calculate the time it takes to go to the finish. (target -
///     car.pos)/car.speed = time it takes.
///
/// Create a stack that represent the amount of fleets based on the time it
/// takes to get to the finish. Cars can't overtake eachother.
///
/// Now, itterate through this mapping. and push cars to the stack when cars
/// after the initial car is faster, this will be the solution. O(n)
///
/// o(n) + o(log n)  = o(n) time and o(n) space complexity.
///
/// @ Note: This solution is not mine, i need to revisit it

int CarFleet(int target, vector<int> position, vector<int> speed) {
  // step 1 is to order on position.
  using time = double;
  using Pos = int;

  map<Pos, time> cars;

  for (int i = 0; i < position.size(); i++) {
    double time = (double)(target - position[i]) / speed[i];
    cars.emplace(position[i], time);
  }

  stack<double> st;

  for (auto it = cars.rbegin(); it != cars.rend(); it++) {
    auto time = it->second;

    if (st.empty() || time > st.top()) {
      st.push(time);
    }
  }

  return st.size();
}

int main() {
  TestTimer timer;

  ExpectEq(CarFleet(12, {10, 8, 0, 5, 4}, {2, 4, 1, 1, 3}), 3);
  ExpectEq(CarFleet(10, {3}, {3}), 1);
  ExpectEq(CarFleet(100, {0, 2, 4}, {4, 2, 1}), 1);
}
