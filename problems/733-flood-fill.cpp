#include <gtest/gtest.h>

#include <functional>
#include <unordered_set>
#include <vector>

using namespace std;

// @start 2026-08-05 22:47

/// @problem 733. Flood Fill
/// @difficulty Easy
///
/// Given an image represented by an m x n integer grid, a starting pixel
/// (sr, sc), and a color, perform a flood fill starting from that pixel.
///
/// A pixel belongs to the fill when it is connected four-directionally to the
/// starting pixel through pixels that have the same original color.
///
/// Return the modified image.
///
/// Constraints:
/// - 1 <= m, n <= 50
/// - 0 <= image[i][j], color < 2^16
/// - 0 <= sr < m
/// - 0 <= sc < n

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                              int color) {

  // Ok, this will be a DFS problem, can also be BFS btw. doesn't matter.
  // I will implement a recursive solution, and we change the image inplace. By
  // doing this, we can mark pixels as visited.
  // We gotta remember, to check the bounds.

  std::function<void(int, int)> dfs;

  auto startColor = image.at(sr).at(sc);

  if (startColor == color) {
    return image;
  }

  dfs = [&](int r, int c) {
    if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size()) {
      return;
    }

    // Set pixel to color
    if (image[r][c] != startColor) {
      return;
    }

    image[r][c] = color;

    // Go to next
    dfs(r + 1, c);
    dfs(r - 1, c);
    dfs(r, c + 1);
    dfs(r, c - 1);
  };

  dfs(sr, sc);

  return image;
}

TEST(Problem, ExistingCases) {

  {
    vector<vector<int>> image{
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1},
    };
    const vector<vector<int>> expected{
        {2, 2, 2},
        {2, 2, 0},
        {2, 0, 1},
    };

    EXPECT_EQ(floodFill(image, 1, 1, 2), expected) << "fills connected pixels";
  }

  {
    vector<vector<int>> image{
        {0, 0, 0},
        {0, 0, 0},
    };
    const vector<vector<int>> expected = image;

    EXPECT_EQ(floodFill(image, 0, 0, 0), expected) << "same replacement color";
  }

  {
    vector<vector<int>> image{
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1},
    };
    const vector<vector<int>> expected{
        {3, 3, 0},
        {3, 0, 1},
        {0, 1, 1},
    };

    EXPECT_EQ(floodFill(image, 0, 0, 3), expected)
        << "does not cross diagonal gaps";
  }
}
