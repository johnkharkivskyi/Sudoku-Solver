#pragma once
#include "../include/board.h"

class Solver {
public:
    virtual bool solve(SudokuBoard& board) = 0;
    virtual ~Solver() = default;
};

class BacktrackingSolver : public Solver {
public:
    bool solve(SudokuBoard& board) override;

private:
    bool findEmptyCell(const SudokuBoard& board, int& row, int& col) const;
    bool tryPlacingDigits(SudokuBoard& board, int row, int col);
};

class SimpleSolver : public Solver {
public:
    bool solve(SudokuBoard& board) override;

private:
    bool tryFilling(SudokuBoard& board);
    int findSingleValidDigit(SudokuBoard& board, int row, int col);
    bool isBoardFull(const SudokuBoard& board) const;
};
