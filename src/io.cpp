#include "stdexcept"
#include "../include/types.h"

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
