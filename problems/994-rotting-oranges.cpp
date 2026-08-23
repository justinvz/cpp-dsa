#include <gtest/gtest.h>

#include <queue>
#include <unordered_set>
#include <vector>

/// @problem 994. Rotting Oranges
/// @difficulty Medium
///
/// Each cell in an m x n grid contains one of these values:
/// - 0: empty
/// - 1: fresh orange
/// - 2: rotten orange
///
/// Every minute, a fresh orange becomes rotten if it is four-directionally
/// adjacent to a rotten orange.
///
/// Return the minimum number of minutes until no fresh orange remains. Return
/// -1 if this is impossible.
///
/// Constraints:
/// - 1 <= m, n <= 10
/// - grid[i][j] is 0, 1, or 2
///
/// @start 2026-08-23 15:11
/// @end 2026-08-23 16:08

struct Position {
  int x;
  int y;
  int time{0};
};

int orangesRotting(std::vector<std::vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }

  // First you will want to count all fresh oranges.
  int oranges{0};

  std::queue<Position> queue;

  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1) {
        oranges++;
      }
      if (grid[i][j] == 2) {
        queue.push(Position{static_cast<int>(i), static_cast<int>(j)});
        oranges++;
      }
    }
  }

  if (oranges == 0) {
    return 0;
  }

  // What you want to do is implement BFS search.

  while (!queue.empty()) {
    auto current = queue.front();
    queue.pop();

    oranges--; // Decrement oranges
    if (oranges <= 0) {
      return current.time;
    }

    if (current.x + 1 < static_cast<int>(grid.size())) {
      if (grid[current.x + 1][current.y] == 1) {
        grid[current.x + 1][current.y] = 2;
        queue.push(Position{current.x + 1, current.y, current.time + 1});
      }
    }

    if (current.x - 1 >= 0) {
      if (grid[current.x - 1][current.y] == 1) {
        grid[current.x - 1][current.y] = 2;
        queue.push(Position{current.x - 1, current.y, current.time + 1});
      }
    }

    if (current.y + 1 < static_cast<int>(grid[0].size())) {
      if (grid[current.x][current.y + 1] == 1) {
        grid[current.x][current.y + 1] = 2;
        queue.push(Position{current.x, current.y + 1, current.time + 1});
      }
    }

    if (current.y - 1 >= 0) {
      if (grid[current.x][current.y - 1] == 1) {
        grid[current.x][current.y - 1] = 2;
        queue.push(Position{current.x, current.y - 1, current.time + 1});
      }
    }
  }

  return -1;
}

TEST(RottingOranges, StandardReachableGrid) {
  std::vector<std::vector<int>> grid{
      {2, 1, 1},
      {1, 1, 0},
      {0, 1, 1},
  };

  EXPECT_EQ(orangesRotting(grid), 4);
}

TEST(RottingOranges, FreshOrangeCannotBeReached) {
  std::vector<std::vector<int>> grid{
      {2, 1, 1},
      {0, 1, 1},
      {1, 0, 1},
  };

  EXPECT_EQ(orangesRotting(grid), -1);
}

TEST(RottingOranges, NoFreshOranges) {
  std::vector<std::vector<int>> grid{{0, 2}};

  EXPECT_EQ(orangesRotting(grid), 0);
}

TEST(RottingOranges, IsolatedFreshOrange) {
  std::vector<std::vector<int>> grid{{1}};

  EXPECT_EQ(orangesRotting(grid), -1);
}

TEST(RottingOranges, MultipleSourcesInNonSquareGrid) {
  std::vector<std::vector<int>> grid{
      {2, 1, 1, 1},
      {1, 1, 1, 2},
  };

  EXPECT_EQ(orangesRotting(grid), 2);
}
