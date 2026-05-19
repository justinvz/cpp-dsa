#include "testSuite.h"
#include <algorithm>
#include <cmath>

using namespace std;

/// Start time: 14-5-2026 13:55

/// @problem Koko loves to eat bananas. There are n piles of bananas, the ith
/// pile has piles[i] bananas. The guards have gone and will come back in h
/// hours.
///
// Koko can decide her bananas-per-hour eating speed of k. Each hour, she
// chooses some pile of bananas and eats k bananas from that pile. If the pile
// has less than k bananas, she eats all of them instead and will not eat any
// more bananas during this hour.
//
// Koko likes to eat slowly but still wants to finish eating all the bananas
// before the guards return.
//
// Return the minimum integer k such that she can eat all the bananas within h
// hours.
///
/// @ Solution
///
/// - ith pile has piles[i] bananas.
/// - k = bananas per hour, if pile is finished, cannot start with another pile.
/// - k should be as low as possible, but still high enough to finish all piles
/// within h.
///
///
/// Solution below works, but we can optimize, for example, we can move from
/// reverse order.

int minEatingSpeed(vector<int> piles, int h) {
  auto max_it = std::max_element(piles.begin(), piles.end());

  int l = 1;
  int r = *max_it;

  int res = r;

  while (l <= r) {
    int k = l + (r - l) / 2;
    int hours = 0;

    for (int p : piles) {
      hours += std::ceil((float)p / (float)k);
    }

    if (hours <= h) {
      res = k;
      r = k - 1;
    } else {
      l = k + 1;
    }
  }

  return res;
}

int main() {
  TestTimer timer;

  ExpectEq(minEatingSpeed({3, 6, 7, 11}, 8), 4);
  ExpectEq(minEatingSpeed({30, 11, 23, 4, 20}, 5), 30);
  ExpectEq(minEatingSpeed({30, 11, 23, 4, 20}, 6), 23);
}
