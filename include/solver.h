#pragma once
#include "../include/board.h"
#include "optional"
#include "vector"

struct Move {
    int row;
    int col;
    int value;
};

class Solver {
public:
    virtual std::optional<SudokuBoard> solve(const SudokuBoard& board) const = 0;
    virtual ~Solver() = default;
};

class BacktrackingSolver : public Solver {
public:
    std::optional<SudokuBoard> solve(const SudokuBoard& board) const override;

private:
    bool isSolved(const SudokuBoard& board) const;
    std::vector<Move> getMoves(const SudokuBoard& board) const;
    SudokuBoard applyMove(const SudokuBoard& board, const Move& move) const;
};

class SimpleSolver : public Solver {
public:
    std::optional<SudokuBoard> solve(const SudokuBoard& board) const override;

private:
    std::optional<SudokuBoard> tryFilling(const SudokuBoard& board) const;
    int findSingleValidDigit(const SudokuBoard& board, int row, int col) const;
    bool isBoardFull(const SudokuBoard& board) const;
};
