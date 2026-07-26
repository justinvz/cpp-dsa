#include "testSuite.h"
#include <functional>

// @start 2026-07-22 21:57
// @solved at 2026-07-26 22:13

using namespace std;

int maxAreaOfIsland(vector<vector<int>> grid) {
  int maxI = grid.size();
  int maxJ = grid.front().size();

  std::function<void(int, int, int &)> explore;

  explore = [&](int i, int j, int &area) -> void {
    // Check if new land, or already visited
    if (grid[i][j] != 1) {
      return;
    }

    grid[i][j] = 2;
    area++;

    if (j - 1 >= 0) {
      explore(i, j - 1, area);
    }

    if (i - 1 >= 0) {
      explore(i - 1, j, area);
    }

    if (i + 1 < maxI) {
      explore(i + 1, j, area);
    }

    if (j + 1 < maxJ) {
      explore(i, j + 1, area);
    }
  };

  int maxArea{0};

  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == 1) {
        int area{0};
        explore(i, j, area);
        maxArea = std::max(area, maxArea);
      }
    }
  }

  return maxArea;
}

int main() {
  TestTimer timer;

  ExpectEq(maxAreaOfIsland({
               {1, 1, 0, 0},
               {1, 1, 0, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0},
           }),
           4);
  ExpectEq(maxAreaOfIsland({
               {1, 1, 0, 0, 0, 1, 0},
               {1, 1, 0, 0, 1, 1, 0},
               {0, 0, 0, 0, 1, 1, 0},
               {0, 1, 0, 0, 0, 0, 0},
               {1, 1, 1, 1, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 0, 0, 0},
           }),
           5);

  ExpectEq(maxAreaOfIsland({
               {1, 1, 0, 0, 0, 1, 0},
               {1, 1, 0, 0, 1, 1, 0},
               {0, 0, 0, 0, 1, 1, 0},
               {0, 1, 0, 0, 0, 0, 0},
               {1, 1, 1, 1, 0, 1, 1},
               {0, 0, 0, 0, 0, 1, 1},
               {0, 1, 0, 0, 0, 1, 1},
           }),
           6);

  ExpectEq(maxAreaOfIsland({

               {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
               {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
               {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}}),
           6);
}
