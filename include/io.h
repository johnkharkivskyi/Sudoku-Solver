#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "../include/types.h"
#include "iostream"
#include "stdexcept"

void readSudoku(SudokuBoard& board, std::istream& in = std::cin);
void printSudoku(const SudokuBoard& board, std::ostream& out = std::cout);

#endif // IO_H_INCLUDED
