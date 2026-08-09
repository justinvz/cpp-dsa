#include <gtest/gtest.h>

#include <vector>

using namespace std;

/// @problem
///
/// Determine if a 0
///
/// Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
/// validated according to the following rules:
/// 1. Each row must contain the digits 1-9 without repetition.
/// 2, each column must contain the digits 1-9 without repetition.
/// 3. each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9
///    without repetition.
///
/// Sudoku board (partially filled) could be valid but is not necessarily
/// solvable.
/// nly the filled cells need to be validated according to the mentioned rules.
///
/// @solution 1 I think we can solve it like some kind of multiplexer. I still
/// don't knmow how, but lets think of the soluition
///
/// Obiously we could itterate through all collums and rows to check for unique
/// numbers. This will however take O(9x9*2). Than we could validate the 3x3
/// boxes, by spliting the problem up
///
/// You could make a map for each collum and row. which will result in 18 maps.
/// So you will always have to check all numbers no matter what, so minimum time
/// complexity will be o(9x9)

bool IsValidSudoku(vector<vector<char>> &board) {
  int rows[9] = {0};
  int cols[9] = {0};
  int boxes[9] = {0};

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {

      if (board[i][j] == '.')
        continue;

      int num = board[i][j] - '0'; // convert char to int 1–9
      int bit = 1 << num;

      int boxIndex = (i / 3) * 3 + (j / 3);

      // check row, col, box
      if (rows[i] & bit)
        return false;
      if (cols[j] & bit)
        return false;
      if (boxes[boxIndex] & bit)
        return false;

      // mark as seen
      rows[i] |= bit;
      cols[j] |= bit;
      boxes[boxIndex] |= bit;
    }
  }

  return true;
}

TEST(Problem, ExistingCases) {

  vector<vector<char>> board1 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  vector<vector<char>> board2 = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  EXPECT_TRUE(IsValidSudoku(board1));
  EXPECT_FALSE(IsValidSudoku(board2));
}
