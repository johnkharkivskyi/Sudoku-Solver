#include "../include/solver.h"

bool BacktrackingSolver::solve(SudokuBoard& board) {
    int row, col;

    if (!findEmptyCell(board, row, col)) {
        return board.isValid();
    }

    return tryPlacingDigits(board, row, col);
}

bool BacktrackingSolver::findEmptyCell(const SudokuBoard& board, int& row, int& col) const {
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board.getCell(row, col) == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

bool BacktrackingSolver::tryPlacingDigits(SudokuBoard& board, int row, int col) {
    for (int num = 1; num <= MAX_SUDOKU_DIGIT; num++) {
        board.setCell(row, col, num);

        if (board.isValid()) {
            if (solve(board)) {
                return true;
            }
        }

        board.setCell(row, col, EMPTY);
    }
    return false;
}

bool SimpleSolver::solve(SudokuBoard& board) {
    bool madeProgress = true;
    while (madeProgress) {
        madeProgress = tryFilling(board);
    }

    return isBoardFull(board) && board.isValid();
}

bool SimpleSolver::tryFilling(SudokuBoard& board) {
    bool progress = false;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.getCell(row, col) == EMPTY) {
                int digit = findSingleValidDigit(board, row, col);
                if (digit != EMPTY) {
                    board.setCell(row, col, digit);
                    progress = true;
                }
            }
        }
    }

    return progress;
}

int SimpleSolver::findSingleValidDigit(SudokuBoard& board, int row, int col) {
    int validCount = 0;
    int lastValidDigit = EMPTY;

    for (int num = 1; num <= MAX_SUDOKU_DIGIT; ++num) {
        board.setCell(row, col, num);
        if (board.isValid()) {
            validCount++;
            lastValidDigit = num;
        }
    }

    board.setCell(row, col, EMPTY);

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
