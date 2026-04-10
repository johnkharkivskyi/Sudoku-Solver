#pragma once

#include "iostream"

const int BOARD_SIZE = 9;
const int SUBBOARDS_PER_ROW = 3;
const int BOX_SIZE = 3;
const int MAX_SUDOKU_DIGIT = 9;
const int EMPTY = 0;

class SudokuBoard {
public:
    void read(std::istream& in = std::cin);
    void print(std::ostream& out = std::cout) const;
    bool isValid() const;

    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);

private:
    int grid[BOARD_SIZE][BOARD_SIZE] = {};

    bool isValidRow(int row) const;
    bool isValidColumn(int col) const;
    bool isValidBox(int startRow, int startCol) const;
};
