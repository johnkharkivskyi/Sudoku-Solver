#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "../include/types.h"

bool isValidRow(const SudokuBoard& board, int row);
bool isValidColumn(const SudokuBoard& board, int col);
bool isValidBox(const SudokuBoard& board, int startRow, int startCol);
bool isValidSudoku(SudokuBoard& board);

#endif // LOGIC_H_INCLUDED
