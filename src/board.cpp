#include "../include/board.h"
#include "stdexcept"

void SudokuBoard::read(std::istream& in) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char value;
            if (!(in >> value) || value < '0' || value > '9') {
                throw std::runtime_error("Invalid input: expected integer (0-9)");
            }

            grid[i][j] = value - '0';
        }
    }
}

void SudokuBoard::print(std::ostream& out) const {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            out << grid[i][j] << ' ';
        }
        out << '\n';
    }
}

bool SudokuBoard::isValid() const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (!isValidRow(i) || !isValidColumn(i)) {
            return false;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i += BOX_SIZE) {
        for (int j = 0; j < BOARD_SIZE; j += BOX_SIZE) {
            if (!isValidBox(i, j)) {
                return false;
            }
        }
    }

    return true;
}

int SudokuBoard::getCell(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        throw std::out_of_range("Index out of bounds");
    }
    return grid[row][col];
}

void SudokuBoard::setCell(int row, int col, int value) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        throw std::out_of_range("Index out of bounds");
    }
    if (value < 0 || value > MAX_SUDOKU_DIGIT) {
        throw std::invalid_argument("Value must be from 0 to 9");
    }
    grid[row][col] = value;
}

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

