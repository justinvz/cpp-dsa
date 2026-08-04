#include "testSuite.h"
#include <algorithm>
#include <stack>

using namespace std;

/// @ revisit 3
/// @ startTime = 26-07-2026 19:42
/// @ finish = 26-07-2026 20:10

struct Car {
  int startPos{0};
  float TimeOfArrival{0};
};

int CarFleet(int target, vector<int> position, vector<int> speed) {

  // Sort time of arrivles based on accending starting position.

  std::vector<Car> cars;

  for (size_t i = 0; i < position.size(); i++) {
    cars.emplace_back(
        Car{.startPos = position[i],
            .TimeOfArrival = (target - position[i]) / (float)speed[i]});
  };

  std::ranges::sort(cars,
                    [](Car &a, Car &b) { return a.startPos > b.startPos; });

  std::stack<float> fleet;

  for (auto car : cars) {
    if (fleet.empty()) {
      fleet.push(car.TimeOfArrival);
      continue;
    }

    if (car.TimeOfArrival > fleet.top()) {
      fleet.push(car.TimeOfArrival);
    }
  }

  return fleet.size();
}

int main() {
  TestTimer timer;

  ExpectEq(CarFleet(12, {10, 8, 0, 5, 4}, {2, 4, 1, 1, 3}), 3);
  ExpectEq(CarFleet(10, {3}, {3}), 1);
  ExpectEq(CarFleet(100, {0, 2, 4}, {4, 2, 1}), 1);
  ExpectEq(CarFleet(10, {0, 4, 2}, {2, 1, 3}), 1);
}
