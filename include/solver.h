#pragma once
#include "../include/board.h"

class Solver {
public:
    bool solve(SudokuBoard& board);

private:
    bool findEmptyCell(const SudokuBoard& board, int& row, int& col) const;
    bool tryPlacingDigits(SudokuBoard& board, int row, int col);
};
