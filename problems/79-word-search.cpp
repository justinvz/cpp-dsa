#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

/// @problem 79. Word Search
/// @difficulty Medium
///
/// Given an m x n grid of characters and a string word, return true if word
/// exists in the grid. The word can be constructed from letters in
/// horizontally or vertically adjacent cells. A cell may not be used more than
/// once in the same word.
///
/// Constraints:
/// - 1 <= m, n <= 6
/// - 1 <= word.size() <= 15
/// - board and word consist of uppercase and lowercase English letters.
///
/// Visited-state rule: a cell is unavailable only while it belongs to the
/// current search path; restore it before trying another path.
///
/// @start 2026-09-01 22:49
/// @start 2026-09-01 23:33

struct point {
  std::size_t x{0};
  std::size_t y{0};
};

bool exist(std::vector<std::vector<char>> &board, const std::string &word) {
  std::array<std::size_t, 256> available{};
  for (const auto &row : board) {
    for (char letter : row) {
      ++available[static_cast<unsigned char>(letter)];
    }
  }

  for (char letter : word) {
    auto &count = available[static_cast<unsigned char>(letter)];
    if (count == 0) {
      return false;
    }
    --count;
  }

  std::vector<point> startPoints;

  for (size_t i = 0; i < board.size(); i++) {
    for (size_t j = 0; j < board[0].size(); j++) {
      if (board[i][j] == word[0]) {
        startPoints.emplace_back(i, j);
      }
    }
  }

  const auto columns = board[0].size();
  auto key = [columns](point point) { return point.x * columns + point.y; };

  std::unordered_set<std::size_t> visited;

  std::function<bool(point point, std::size_t index)> dfs;
  dfs = [&](point point, std::size_t index) {
    if (visited.contains(key(point)) ||
        word[index] != board[point.x][point.y]) {
      return false;
    }

    if (index == word.size() - 1) {
      return true;
    }

    visited.emplace(key(point));

    bool found{false};
    if (point.x + 1 < board.size()) {
      found = dfs({point.x + 1, point.y}, index + 1);
    }
    if (!found && point.y + 1 < board[0].size()) {
      found = dfs({point.x, point.y + 1}, index + 1);
    }
    if (!found && point.x > 0) {
      found = dfs({point.x - 1, point.y}, index + 1);
    }
    if (!found && point.y > 0) {
      found = dfs({point.x, point.y - 1}, index + 1);
    }

    visited.erase(key(point));
    return found;
  };

  for (point point : startPoints) {
    if (dfs(point, 0)) {
      return true;
    }
  };

  return false;
}

TEST(WordSearch, FindsSingleCellWord) {
  std::vector<std::vector<char>> board{{'A'}};

  EXPECT_TRUE(exist(board, "A"));
}

TEST(WordSearch, FindsWordAlongAdjacentCells) {
  std::vector<std::vector<char>> board{
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'},
  };

  EXPECT_TRUE(exist(board, "ABCCED"));
}

TEST(WordSearch, RejectsPathThatReusesACell) {
  std::vector<std::vector<char>> board{
      {'A', 'B'},
      {'C', 'D'},
  };

  EXPECT_FALSE(exist(board, "ABDA"));
}

TEST(WordSearch, RejectsUnavailableCharacterCount) {
  std::vector<std::vector<char>> board{{'A', 'B'}};

  EXPECT_FALSE(exist(board, "ABA"));
}

TEST(WordSearch, BacktracksToTryAnotherPath) {
  std::vector<std::vector<char>> board{
      {'A', 'A', 'B'},
      {'A', 'C', 'B'},
  };

  EXPECT_TRUE(exist(board, "AACBB"));
}

TEST(WordSearch, HandlesUnevenDimensions) {
  std::vector<std::vector<char>> board{
      {'A', 'B', 'C', 'D'},
      {'H', 'G', 'F', 'E'},
  };

  EXPECT_TRUE(exist(board, "ABCDEFGH"));
}

TEST(WordSearch, DistinguishesCoordinatesOnTallBoard) {
  std::vector<std::vector<char>> board{
      {'B', 'A'},
      {'C', 'X'},
      {'D', 'X'},
  };

  EXPECT_TRUE(exist(board, "ABCD"));
}
