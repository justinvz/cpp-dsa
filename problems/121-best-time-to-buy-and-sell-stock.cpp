#include "testSuite.h"
#include <vector>

using namespace std;

/// Start time = 19-05-2026 - 22:12
/// @problem
///
/// You are given an array prices where prices[i] is the price of a given stock
/// on the ith day.
//
// You want to maximize your profit by choosing a single day to buy one stock
// and choosing a different day in the future to sell that stock.
//
// Return the maximum profit you can achieve from this transaction. If you
// cannot achieve any profit, return 0.
//
/// @solution
///
/// Obiously we need to find the biggest profit between two days, the catch is
/// that we always buy first and sell after.
///
/// Naive solution is (n^2) once you evaluate each possible buying day
/// with each possible selling day.
///
/// Another approach is to use a sliding window. We can itterate through they
/// array from left to right, and remeber the cheapest buying day, and the best
/// selling day.

int maxProfitNaive(vector<int> prices) {
  int profit{0};

  for (int buyIndex = 0; buyIndex < prices.size() - 1; buyIndex++) {
    for (int sellIndex = buyIndex + 1; sellIndex < prices.size(); sellIndex++) {
      auto dayProfit = prices[sellIndex] - prices[buyIndex];
      if (dayProfit > 0 && dayProfit > profit) {
        profit = dayProfit;
      }
    }
  }

  return profit;
}

int maxProfit(vector<int> prices) {
  int minPrice = prices[0];
  int maxProfit = 0;

  for (int price : prices) {
    minPrice = min(minPrice, price);
    maxProfit = max(maxProfit, price - minPrice);
  }

  return maxProfit;
}

int main() {
  TestTimer timer;
  ExpectEq(maxProfit({7, 1, 5, 3, 6, 4}), 5);
  ExpectEq(maxProfit({7, 6, 4, 3, 1}), 0);
  ExpectEq(maxProfit({1, 2, 3, 4, 5, 6}), 5);
}
