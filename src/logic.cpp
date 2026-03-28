#include "../include/types.h"

bool SudokuBoard::isValidRow(int row) const {
    bool used[10] = {};
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] != 0) {
            if (used[grid[row][i]]) return false;
            used[grid[row][i]] = true;
        }
    }
    return true;
}

bool SudokuBoard::isValidColumn(int col) const {
    bool used[10] = {};
    for (int i = 0; i < 9; i++) {
        if (grid[i][col] != 0) {
            if (used[grid[i][col]]) return false;
            used[grid[i][col]] = true;
        }
    }
    return true;
}

bool SudokuBoard::isValidBox(int startRow, int startCol) const {
    bool used[10] = {};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] != 0) {
                if (used[grid[startRow + i][startCol + j]]) return false;
                used[grid[startRow + i][startCol + j]] = true;
            }
        }
    }
    return true;
}

bool SudokuBoard::isValid() const {
    for (int i = 0; i < 9; i++) {
        if (!isValidRow(i) || !isValidColumn(i))
            return false;
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!isValidBox(i, j))
                return false;
        }
    }

    return true;
}
