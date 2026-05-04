#include "testSuite.h"

using namespace std;

// @problem
//
// Given a 1-indexed array of integers numbers that is already sorted in
// non-decreasing order, find two numbers such that they add up to a specific
// target number. Let these two numbers be numbers[index1] and numbers[index2]
// where 1 <= index1 < index2 <= numbers.length.
// Return the indices of the two numbers index1 and index2, each incremented by
// one, as an integer array [index1, index2] of length 2.
//
// The tests are generated such that there is exactly one solution. You may not
// use the same element twice.
//
// Your solution must use only constant extra space.
//
// Because array is sorted, the bigest number of the output is always on the
// right en the largest on the left.
//
// Don't forget to increment the indexes by 1
//
// @ solution Naive
//
// We can walk through the array, and check each element on each other. We
// cannot use a hashmap to remember a value. this solution will be O(n^2)
//
// I think that we can be smart because it's sorted. We can say that whe we
// evaluate one number to each other, and we find on the second index a higher
// value, all value's after will be higher. The reverse is true.
//
// lets say we have this. and we need
//
// [2,4,6,8,9] target = 12
//
// 2 + 9 = 11; smaller, so we need bigger number
// 4 + 9 = 13; bigger, so we need smaller numbe
// 4 + 8 = 12; hit! solution = [2, 4]
//
// [-2,5,8,10] target = 6
// index1 = -2, index2 = 10
// -2 + 10 = 8; smaller index2 - 1
// -2 + 8 = 6; hit!
//
// [-2,5,8,10] target = 13
// -2 + 10 = 8; smaller than 13, index1+++
// 5 + 10 - 15; bigger than 13, index2--;
// 5+8 = 13
//
// Worst case, it's O(n) time complexity, because you need to itterate through
// the whole array.

vector<int> TwoSum(vector<int> numbers, int target) {
  std::size_t index1 = 0;
  std::size_t index2 = numbers.size() - 1;

  while (index1 < index2) {

    int sum = numbers[index1] + numbers[index2];

    if (sum == target) {
      return {(int)index1 + 1, (int)index2 + 1};
    } else if (sum < target) {
      index1++;
    } else if (sum > target) {
      index2--;
    }
  }

  return {};
}

int main() {
  TestTimer timer;

  ExpectEq(TwoSum({2, 7, 11, 15}, 9), {1, 2});
  ExpectEq(TwoSum({2, 3, 4}, 6), {1, 3});
  ExpectEq(TwoSum({-1, 0}, -1), {1, 2});
}
