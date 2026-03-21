#include "../include/io.h"
#include "../include/types.h"
#include "../include/logic.h"

int main() {
    SudokuBoard board;

    std::cout << "Input 9 lines with 9 digits each, where 0 represents an empty cell (no spaces):\n";
    readSudoku(board);

    std::cout << "Printed Sudoku Board:\n";
    printSudoku(board);

    if (isValidSudoku(board))
        std::cout << "This Sudoku board is valid\n";
    else std::cout << "This Sudoku board is invalid\n";



    return 0;
}
