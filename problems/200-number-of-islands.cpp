#include <gtest/gtest.h>

#include <cstddef>
#include <functional>
#include <vector>

// @start 2026-07-22 18:10
// @solved at 2026-07-26 19:29

using namespace std;

int numIslands(vector<vector<char>> grid) {
  int maxI = grid.size();
  int maxJ = grid.front().size();

  // When we hit land, we need to explore. all land that belong to the island.
  // Obisouly we need to to this on a smart way.

  std::function<void(int, int)> explore;

  explore = [&](int i, int j) -> void {
    // Check if new land, or already visited
    if (grid[i][j] != '1') {
      return;
    }

    grid[i][j] = '2';

    if (j - 1 >= 0) {
      explore(i, j - 1);
    }

    if (i - 1 >= 0) {
      explore(i - 1, j);
    }

    if (i + 1 < maxI) {
      explore(i + 1, j);
    }

    if (j + 1 < maxJ) {
      explore(i, j + 1);
    }
  };

  int groups{0};

  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == '1') {
        groups++;
        explore(i, j);
      }
    }
  }

  return groups;
}

TEST(Problem, ExistingCases) {

  EXPECT_EQ(numIslands({
               {'1', '1', '0', '0'},
               {'1', '1', '0', '0'},
               {'0', '0', '0', '0'},
               {'0', '0', '0', '0'},
           }),
           1);

  EXPECT_EQ(numIslands({
               {'1', '1', '0', '0'},
               {'1', '1', '0', '0'},
               {'0', '0', '1', '0'},
               {'0', '0', '0', '0'},
           }),
           2);

  EXPECT_EQ(numIslands({
               {'1', '0', '1', '1', '1'},
               {'1', '0', '1', '0', '1'},
               {'1', '1', '1', '0', '1'},
           }),
           1);
}
