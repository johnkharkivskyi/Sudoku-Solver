#include "../include/solver.h"

bool Solver::solve(SudokuBoard& board) {
    int row, col;

    if (!findEmptyCell(board, row, col)) {
        return board.isValid();
    }

    return tryPlacingDigits(board, row, col);
}

bool Solver::findEmptyCell(const SudokuBoard& board, int& row, int& col) const {
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board.getCell(row, col) == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

bool Solver::tryPlacingDigits(SudokuBoard& board, int row, int col) {
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
