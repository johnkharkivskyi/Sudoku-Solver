#include "../include/io.h"

void readSudoku(SudokuBoard& board, std::istream& in) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char value;
            if (!(in >> value) || value < '0' || value > '9') {
                throw std::runtime_error("Invalid input: expected integer (0-9)");
            }

            board.grid[i][j] = value - '0';
        }
    }
}

void printSudoku(const SudokuBoard& board, std::ostream& out) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            out << board.grid[i][j];
        }
        out << '\n';
    }
}
