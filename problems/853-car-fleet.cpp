
#include "testSuite.h"
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

struct Car {
  int pos;
  int speed;
};

int CarFleet(int target, vector<int> position, vector<int> speed) {
  std::vector<Car> cars;

  for (size_t i{0}; i < position.size(); i++) {
    cars.emplace_back(Car{position[i], speed[i]});
  }

  std::sort(cars.begin(), cars.end(),
            [](const Car &a, const Car &b) { return a.pos < b.pos; });

  std::stack<int> fleets;
  for (int i = cars.size() - 1; i >= 0; --i) {
    double time = static_cast<double>(target - cars[i].pos) / cars[i].speed;

    std::cout << time << std::endl;

    if (fleets.empty() || time > fleets.top()) {
      fleets.push(time);
    }
  }

  return fleets.size();
}

int main() {
  TestTimer timer;

  ExpectEq(CarFleet(12, {10, 8, 0, 5, 4}, {2, 4, 1, 1, 3}), 3);
  ExpectEq(CarFleet(10, {3}, {3}), 1);
  ExpectEq(CarFleet(100, {0, 2, 4}, {4, 2, 1}), 1);
  ExpectEq(CarFleet(10, {0, 4, 2}, {2, 1, 3}), 1);
}
