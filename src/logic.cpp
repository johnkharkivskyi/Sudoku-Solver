#include "../include/types.h"

bool SudokuBoard::isValidRow(int row) const {
    bool used[BOARD_SIZE + 1] = {};
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (grid[row][i] != 0) {
            if (used[grid[row][i]]) {
                return false;
            }
            used[grid[row][i]] = true;
        }
    }
    return true;
}

bool SudokuBoard::isValidColumn(int col) const {
    bool used[BOARD_SIZE + 1] = {};
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (grid[i][col] != 0) {
            if (used[grid[i][col]]) {
                return false;
            }
            used[grid[i][col]] = true;
        }
    }
    return true;
}

bool SudokuBoard::isValidBox(int startRow, int startCol) const {
    bool used[BOARD_SIZE + 1] = {};
    for (int i = 0; i < SUBBOARDS_PER_ROW; i++) {
        for (int j = 0; j < SUBBOARDS_PER_ROW; j++) {
            if (grid[startRow + i][startCol + j] != 0) {
                if (used[grid[startRow + i][startCol + j]]) {
                    return false;
                }
                used[grid[startRow + i][startCol + j]] = true;
            }
        }
    }
    return true;
}

bool SudokuBoard::isValid() const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (!isValidRow(i) || !isValidColumn(i)) {
            return false;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i += BOARD_SIZE / SUBBOARDS_PER_ROW) {
        for (int j = 0; j < BOARD_SIZE; j += BOARD_SIZE / SUBBOARDS_PER_ROW) {
            if (!isValidBox(i, j)) {
                return false;
            }
        }
    }

    return true;
}
