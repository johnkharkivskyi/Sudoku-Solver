#include "../include/logic.h"

bool isValidRow(const SudokuBoard& board, int row) {
    bool used[10] = {};
    for (int i = 0; i < 9; i++) {
        if (board.grid[row][i] != 0) {
            if (used[board.grid[row][i]]) return false;
            used[board.grid[row][i]] = true;
        }
    }
    return true;
}

bool isValidColumn(const SudokuBoard& board, int col) {
    bool used[10] = {};
    for (int i = 0; i < 9; i++) {
        if (board.grid[i][col] != 0) {
            if (used[board.grid[i][col]]) return false;
            used[board.grid[i][col]] = true;
        }
    }
    return true;
}

bool isValidBox(const SudokuBoard& board, int startRow, int startCol) {
    bool used[10] = {};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.grid[startRow + i][startCol + j] != 0) {
                if (used[board.grid[startRow + i][startCol + j]]) return false;
                used[board.grid[startRow + i][startCol + j]] = true;
            }
        }
    }
    return true;
}

bool isValidSudoku(SudokuBoard& board) {
    for (int i = 0; i < 9; i++) {
        if (!isValidRow(board, i) || !isValidColumn(board, i))
            return false;
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!isValidBox(board, i, j))
                return false;
        }
    }

    return true;
}
