#include "../include/types.h"

int main() {
    SudokuBoard board;

    std::cout << "Input 9 lines with 9 digits each, where 0 represents an empty cell (no spaces):\n";
    board.read();

    std::cout << "Printed Sudoku Board:\n";
    board.print();

    if (board.isValid()) {
        std::cout << "This Sudoku board is valid\n";
        Solver solver;
        if (solver.solve(board)) {
            std::cout << "\nSuccessfully solved:\n";
            board.print();
        } else {
            std::cout << "\nFailed to solve sudoku\n";
        }
    } else {
        std::cout << "This Sudoku board is invalid\n";
    }

    return 0;
}
