#include "../include/solver.h"

std::optional<SudokuBoard> BacktrackingSolver::solve(const SudokuBoard& board) const {
    stats = SolverStats();
    return solveRecursive(board);
}

std::optional<SudokuBoard> BacktrackingSolver::solveRecursive(const SudokuBoard& board) const {
    stats.recursiveCalls++;

    if (isSolved(board)) {
        return board;
    }

    for (const auto& move : getMoves(board)) {
        stats.branchesTried++;

        auto result = solveRecursive(applyMove(board, move));

        if (result) {
            return result;
        }
    }

    return std::nullopt;
}

bool BacktrackingSolver::isSolved(const SudokuBoard& board) const {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board.getCell(r, c) == EMPTY) {
                return false;
            }
        }
    }

    return board.isValid();
}

std::vector<Move> BacktrackingSolver::getMoves(const SudokuBoard& board) const {
    auto candidates = generateCandidates(board);

    return filterMoves(
        candidates,
        [&](const Move& move) {
            return isValidMove(board, move);
        }
    );
}

std::vector<Move> BacktrackingSolver::generateCandidates(const SudokuBoard& board) const {
    std::vector<Move> moves;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board.getCell(r, c) == EMPTY) {
                for (int v = 1; v <= MAX_SUDOKU_DIGIT; ++v) {
                    moves.push_back({r, c, v});
                }
                return moves;
            }
        }
    }

    return moves;
}

std::vector<Move> BacktrackingSolver::filterMoves(const std::vector<Move>& moves, Predicate predicate) const {
    std::vector<Move> result;

    for (const auto& move : moves) {
        if (predicate(move)) {
            result.push_back(move);
        }
    }

    return result;
}

bool BacktrackingSolver::isValidMove(const SudokuBoard& board, const Move& move) const {
    return applyMove(board, move).isValid();
}

SudokuBoard BacktrackingSolver::applyMove(const SudokuBoard& board, const Move& move) const {
    SudokuBoard next = board;
    next.setCell(move.row, move.col, move.value);
    return next;
}

SudokuBoard SimpleSolver::propagate(const SudokuBoard& board) const {
    SudokuBoard current = board;
    bool madeProgress = true;

    while (madeProgress) {
        auto nextBoard = tryFilling(current);
        if (nextBoard) {
            current = nextBoard.value();
        } else {
            madeProgress = false;
        }
    }
    return current;
}

std::optional<SudokuBoard> SimpleSolver::solve(const SudokuBoard& board) const {
    stats = SolverStats();

    SudokuBoard current = propagate(board);

    if (isBoardFull(current) && current.isValid()) {
        return current;
    }

    return std::nullopt;
}

std::optional<SudokuBoard> SimpleSolver::tryFilling(const SudokuBoard& board) const {
    SudokuBoard next = board;
    bool progress = false;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (next.getCell(row, col) == EMPTY) {
                int digit = findSingleValidDigit(next, row, col);
                if (digit != EMPTY) {
                    next.setCell(row, col, digit);
                    progress = true;
                }
            }
        }
    }

    if (progress) {
        return next;
    }
    return std::nullopt;
}

int SimpleSolver::findSingleValidDigit(const SudokuBoard& board, int row, int col) const {
    int validCount = 0;
    int lastValidDigit = EMPTY;

    for (int num = 1; num <= MAX_SUDOKU_DIGIT; ++num) {
        SudokuBoard testBoard = board;
        testBoard.setCell(row, col, num);

        if (testBoard.isValid()) {
            validCount++;
            lastValidDigit = num;
        }
    }

    if (validCount == 1) {
        return lastValidDigit;
    }

    return EMPTY;
}

bool SimpleSolver::isBoardFull(const SudokuBoard& board) const {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.getCell(row, col) == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

std::vector<Move> MRVSolver::generateCandidates(const SudokuBoard& board) const {
    int minCandidates = 10;
    int bestR = -1, bestC = -1;

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board.getCell(r, c) == EMPTY) {
                int validCount = 0;
                for (int v = 1; v <= MAX_SUDOKU_DIGIT; ++v) {
                    if (isValidMove(board, {r, c, v})) {
                        validCount++;
                    }
                }
                if (validCount < minCandidates) {
                    minCandidates = validCount;
                    bestR = r;
                    bestC = c;
                }
            }
        }
    }

    std::vector<Move> moves;
    if (bestR != -1 && bestC != -1) {
        // Validation handles invalid moves when returning to getMoves
        for (int v = 1; v <= MAX_SUDOKU_DIGIT; ++v) {
            moves.push_back({bestR, bestC, v});
        }
    }
    return moves;
}


std::optional<SudokuBoard> MRVPropagationSolver::solve(const SudokuBoard& board) const {
    stats = SolverStats();
    return solveRecursiveWithPropagation(board);
}

std::optional<SudokuBoard> MRVPropagationSolver::solveRecursiveWithPropagation(const SudokuBoard& board) const {
    stats.recursiveCalls++;

    SimpleSolver simpleSolver;
    SudokuBoard currentBoard = simpleSolver.propagate(board);

    if (isSolved(currentBoard)) {
        return currentBoard;
    }

    for (const auto& move : getMoves(currentBoard)) {
        stats.branchesTried++;

        auto result = solveRecursiveWithPropagation(applyMove(currentBoard, move));

        if (result) {
            return result;
        }
    }

    return std::nullopt;
}
