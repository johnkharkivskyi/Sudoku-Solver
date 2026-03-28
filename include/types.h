#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "iostream"
#include "stdexcept"

class SudokuBoard {
public:
    void read(std::istream& in = std::cin);
    void print(std::ostream& out = std::cout) const;
    bool isValid() const;

private:
    int grid[9][9] = {};

    bool isValidRow(int row) const;
    bool isValidColumn(int col) const;
    bool isValidBox(int startRow, int startCol) const;
};

#endif // TYPES_H_INCLUDED
