#pragma once

#include "../include/board.h"
#include "optional"
#include "vector"
#include "functional"

struct Move {
    int row;
    int col;
    int value;
};

struct SolverStats {
    int recursiveCalls = 0;
    int branchesTried = 0;
};

using Predicate = std::function<bool(const Move&)>;

class Solver {
public:
    virtual std::optional<SudokuBoard> solve(const SudokuBoard& board) const = 0;
    virtual SolverStats getStats() const = 0;
    virtual ~Solver() = default;
};

class BacktrackingSolver : public Solver {
public:
    std::optional<SudokuBoard> solve(const SudokuBoard& board) const override;
    SolverStats getStats() const override { return stats; }

protected:
    mutable SolverStats stats;

    std::optional<SudokuBoard> solveRecursive(const SudokuBoard& board) const;

    bool isSolved(const SudokuBoard& board) const;

    virtual std::vector<Move> getMoves(const SudokuBoard& board) const;
    virtual std::vector<Move> generateCandidates(const SudokuBoard& board) const;
    std::vector<Move> filterMoves(const std::vector<Move>& moves, Predicate predicate) const;

    bool isValidMove(const SudokuBoard& board, const Move& move) const;
    SudokuBoard applyMove(const SudokuBoard& board, const Move& move) const;
};

class SimpleSolver : public Solver {
public:
    std::optional<SudokuBoard> solve(const SudokuBoard& board) const override;
    SolverStats getStats() const override { return stats; }
    SudokuBoard propagate(const SudokuBoard& board) const;

private:
    mutable SolverStats stats;
    std::optional<SudokuBoard> tryFilling(const SudokuBoard& board) const;
    int findSingleValidDigit(const SudokuBoard& board, int row, int col) const;
    bool isBoardFull(const SudokuBoard& board) const;
};

class MRVSolver : public BacktrackingSolver {
protected:
    std::vector<Move> generateCandidates(const SudokuBoard& board) const override;
};

class MRVPropagationSolver : public MRVSolver {
public:
    std::optional<SudokuBoard> solve(const SudokuBoard& board) const override;

private:
    std::optional<SudokuBoard> solveRecursiveWithPropagation(const SudokuBoard& board) const;
};
