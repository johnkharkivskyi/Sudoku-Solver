#include <iostream>
#include "../include/board.h"
#include "../include/solver.h"

int main() {
    SudokuBoard board;

    std::cout << "Input 9 lines with 9 digits each, where 0 represents an empty cell (no spaces):\n";
    board.read();

    std::cout << "Printed Sudoku Board:\n";
    board.print();

    if (!board.isValid()) {
        std::cout << "This Sudoku board is invalid\n";
        return 0;
    }

    std::cout << "This Sudoku board is valid\n";

    Solver* simpleSolver = new SimpleSolver();
    Solver* backtrackingSolver = new BacktrackingSolver();

    bool isSolved = simpleSolver->solve(board);
    std::cout << "\nAttempt to solve the board with Simple Solver:\n";
    board.print();

    if (isSolved) {
        std::cout << "\nThis board was successfully solved with Simple Solver!\n";
    } else {
        isSolved = backtrackingSolver->solve(board);
        std::cout << "\nAttempt to solve the board with Backtracking Solver:\n";
        board.print();

        if (isSolved) {
            std::cout << "\nThis board was solved by applying Simple Solver, then Backtracking Solver.\n";
        } else {
            std::cout << "\nFailed to solve sudoku.\n";
        }
    }

    delete simpleSolver;
    delete backtrackingSolver;

    return 0;
}
