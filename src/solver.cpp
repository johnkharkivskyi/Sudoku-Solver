#include "../include/types.h"

bool Solver::solve(SudokuBoard& board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board.getCell(row, col) == 0) {
                for (int num = 1; num <= MAX_SUDOKU_DIGIT; num++) {
                    board.setCell(row, col, num);
                    if (board.isValid()) {
                        if (solve(board)) {
                            return true;
                        }
                    }
                    board.setCell(row, col, 0);
                }
                return false;
            }
        }
    }
    return true;
}
